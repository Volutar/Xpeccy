#include "emulwin.h"
#include "filer.h"
#include "version.h"

#define STR_EXPAND(tok) #tok
#define	STR(tok) STR_EXPAND(tok)
#ifdef USEOPENGL
#define	XPTITLE	STR(Xpeccy VERSION (OpenGL))
#else
#define	XPTITLE	STR(Xpeccy VERSION)
#endif
#include "LOG/LOG.h"

// socket

#ifdef USENETWORK

void MainWin::openServer() {
	int i = 0;
	while (!srv.listen(QHostAddress::LocalHost, (conf.port + i) & 0xffff) && (i < 0x10000)) {
		i++;
	}
	if (!srv.isListening()) {
//		shitHappens("Listen server can't start");
		printf("ERROR: Listening cannot start at port %i\n",conf.port);
	} else {
		printf("Listening port %i\n", (conf.port + i) & 0xffff);
	}
}

void MainWin::closeServer() {
	if (srv.isListening()) {
		foreach(QTcpSocket* sock, clients) {
			sock->close();
			sock->deleteLater();
		}
		srv.close();
	}
}

void MainWin::connected() {
	QTcpSocket* sock = srv.nextPendingConnection();
	clients.append(sock);
//	sock->write("Who's there?\n> ");
	sock->write("hello, it's Xpeccy " STR(VERSION) "\n> ");
	connect(sock,SIGNAL(destroyed()),this,SLOT(disconnected()));
	connect(sock,SIGNAL(readyRead()),this,SLOT(socketRead()));
}

void MainWin::disconnected() {
	QTcpSocket* sock = (QTcpSocket*)sender();
	disconnect(sock);
	clients.removeAll(sock);
	sock->deleteLater();
}

static char dasmbuf[256];
extern int dasmrd(int adr, void* ptr);
extern int str_to_adr(Computer* comp, QString str);
extern void dasmwr(Computer* comp, int adr, int bt);

void MainWin::socketRead() {
	QTcpSocket* sock = (QTcpSocket*)sender();
	QByteArray arr = sock->readAll();
	QString com(arr);
	QString str;
	com = com.remove("\n");
	com = com.remove("\r");
	QStringList prm = com.split(" ",X_SkipEmptyParts);
	xMnem mnm;
	int adr, cnt, val;
	// and do something with this
	if ((com == "debug") || (com == "dbg")) {
		doDebug();
	} else if (com == "closedbg") {
		emit s_debug_off();
	} else if (com == "quit") {
		close();
	} else if (com == "exit") {
		sock->close();
	} else if (com == "pause") {
		pause(true, PR_PAUSE);
	} else if (com == "cont") {
		pause(false, PR_PAUSE);
	} else if (com == "step") {
		emit s_step();
	} else if (com == "reset") {
		compReset(comp, RES_DEFAULT);
	} else if (com == "cpu") {
		sock->write(getCoreName(comp->cpu->type));
		sock->write("\n");
	} else if (com == "cpuregs") {
		xRegBunch rb = cpuGetRegs(comp->cpu);
		xRegister reg;
		for (cnt = 0; cnt < 32; cnt++) {
			reg = rb.regs[cnt];
			if (reg.id != REG_NONE) {
				sock->write(reg.name);
				sock->write(" : ");
				switch(reg.type & REG_TMASK) {
					case REG_BIT: sock->write(reg.value ? "1" : "0"); break;
					case REG_BYTE: sock->write(gethexbyte(reg.value).toUtf8()); break;
					case REG_WORD: sock->write(gethexword(reg.value).toUtf8()); break;
					case REG_24: sock->write(gethex6(reg.value).toUtf8()); break;
					default: sock->write("??"); break;
				}
				sock->write("\r\n");
			}
		}

	} else if (com.startsWith("load ")) {
		str = com.mid(5);
		load_file(comp, str.toLocal8Bit().data(), FG_ALL, 0);
	} else if (com.startsWith("poke ") || com.startsWith("memwr ")) {
		if (prm.size() > 2) {
			adr = str_to_adr(comp, prm[1]);
			val = str_to_adr(comp, prm[2]);
			comp->hw->mwr(comp, adr, val & 0xff);
		}
	} else if (com.startsWith("pokew ") || com.startsWith("memwrw ")) {
		if (prm.size() > 2) {
			adr = str_to_adr(comp, prm[1]);
			val = str_to_adr(comp, prm[2]);
			comp->hw->mwr(comp, adr, val & 0xff);
			comp->hw->mwr(comp, adr+1, (val >> 8) & 0xff);
		}
	} else if (com.startsWith("memfill ")) {
		if (prm.size() > 3) {
			adr = str_to_adr(comp, prm[1]);
			cnt = str_to_adr(comp, prm[2]);
			val = str_to_adr(comp, prm[3]);
			while (cnt > 0) {
				comp->hw->mwr(comp, adr, val);
				adr++;
				cnt--;
			}
		}
	} else if (com.startsWith("memcopy ")) {
		if (prm.size() > 3) {
			adr = str_to_adr(comp, prm[1]);
			cnt = str_to_adr(comp, prm[2]);
			val = str_to_adr(comp, prm[3]);
			qDebug() << adr << cnt << val;
			while (cnt > 0) {
				if (adr > val) {
					comp->hw->mwr(comp, val, comp->hw->mrd(comp, adr, 0));		// dst < src
					adr++;
					val++;
				} else {								// dst >= src
					comp->hw->mwr(comp, val+cnt-1, comp->hw->mrd(comp, adr+cnt-1, 0));
				}
				cnt--;
			}
		}
	} else if (com.startsWith("disasm ")) {
		if (prm.size() > 1) {
			adr = str_to_adr(comp, prm[1]);
			cnt = (prm.size() > 2) ? prm[2].toInt() : 1;
			// qDebug() << cnt;
			while (cnt > 0) {
				sprintf(dasmbuf, "%.6X : ", adr);
				sock->write(dasmbuf);
				mnm = cpuDisasm(comp->cpu, comp->cpu->cs.base + adr, dasmbuf, dasmrd, comp);
				sock->write(dasmbuf);
				sock->write("\r\n");
				adr += mnm.len;
				cnt--;
			}
		}
	} else if (com.startsWith("dump ")) {
		if (prm.size() > 1) {
			adr = str_to_adr(comp, prm[1]);
			if (prm.size() > 2) {
				cnt = prm[2].toInt();
				if (cnt < 1) {
					cnt = 16;
				} else {
					cnt <<= 4;
				}
			} else {
				cnt = 16;
			}
			while (cnt > 0) {
				sprintf(dasmbuf, "%.6X : ", adr);
				sock->write(dasmbuf);
				dasmbuf[0] = 0x00;
				do {
					sprintf(dasmbuf, "%.2X ", dasmrd(comp->cpu->cs.base + adr, comp));
					sock->write(dasmbuf);
					adr++;
					cnt--;
				} while (cnt & 15);
				sock->write("\r\n");
			}
		}
	} else if (com.startsWith("dumpraw ")) {
		int adr=0, size=8;
		if (!prm[1].isEmpty()) adr = str_to_adr(comp, prm[1]);
		if (!prm[2].isEmpty()) size = str_to_adr(comp, prm[2]);
//		LOG_Misc("Dump: %i %i\n", adr, size);
		if (size>0x10000) size=0x10000;
		for(int i = adr; i < adr + size; i++)
		{
			dasmbuf[0] = 0x00;
			sprintf(dasmbuf,"%.2X",dasmrd(comp->cpu->cs.base + i,comp));
			sock->write(dasmbuf);
		}
		sock->write("\r\n");
	} else if (com == "exit" || com == "\x03") {
		sock->abort();
		return;
	} else {
		if (com.size()>0) sock->write("Unrecognized command\r\n");
	}
	if (com != "quit")
		sock->write("> ");
	prm.clear();
}

#else

void MainWin::connected() {}
void MainWin::disconnected() {}
void MainWin::socketRead() {}

#endif
