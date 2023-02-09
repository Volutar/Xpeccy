// #include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QFontDatabase>
#include <QStyleFactory>
#include <QUrl>

#include <locale.h>

#include "xcore/xcore.h"
#include "xcore/sound.h"
#include "xgui/xgui.h"
#include "libxpeccy/spectrum.h"

#include "xapp.h"
#include "emulwin.h"
#include "xgui/debuga/debuger.h"
#include "xgui/options/setupwin.h"
#include "filer.h"

#include "LOG/LOG.h"

#include <SDL.h>
#undef main

#if defined(__WIN32)
#include <windows.h>
#include <conio.h>
#endif

void help() {
	printf("Xpeccy command line arguments:\n");
	printf("-h | --help\t\tshow this help\n");
	printf("-d | --debug\t\tstart debugging immediately\n");
	printf("-s | --size {1..6}\tset window size x1..x6.\n");
	printf("-n | --noflick {0..100}\tset noflick level\n");
	printf("-r | --ratio {0|1}\tset 'keep aspect ratio' property\n");
	printf("-p | --profile NAME\tset current profile\n");
	printf("-b | --bank NUM\t\tset rampage NUM to #c000 memory window\n");
	printf("-a | --adr ADR\t\tset loading address (see -f below)\n");
	printf("-f | --file NAME\tload binary file to address defined by -a (see above)\n");
	printf("-l | --labels NAME\tload labels list generated by LABELSLIST in SJASM+\n");
	printf("-c | --console\tWindows only: attach to console\n");
	printf("--fullscreen {0|1}\tfullscreen mode\n");
	printf("--pc ADR\t\tset PC\n");
	printf("--sp ADR\t\tset SP\n");
	printf("--bp ADR\t\tset fetch brakepoint to address ADR\n");
	printf("--bp NAME\t\tset fetch brakepoint to label NAME (see -l key)\n");
	printf("--disk X\t\tselect drive to loading file (0..3 | a..d | A..D)\n");
	printf("--style\t\t\tMacOSX only: use native qt style, else 'fusion' will be forced\n");
	printf("--xmap FILE\t\tLoad *.xmap file\n");
	printf("--confdir DIR\t\tChange config directory\n");
}

void xApp::d_frame() {
	postEvent(this, new QEvent(QEvent::User));
}

// for apple users
bool xApp::event(QEvent* ev) {
	QFileOpenEvent* fev;
	QString path;
	switch(ev->type()) {
		case QEvent::FileOpen:
			fev = static_cast<QFileOpenEvent*>(ev);
			path = fev->url().path();
			if (conf.prof.cur) {
				load_file(conf.prof.cur->zx, path.toLocal8Bit().data(), FG_ALL, 0);
			}
			break;
		case QEvent::User:
			emit s_frame();
			break;
		default:
			break;
	}
	return QApplication::event(ev);
}

int main(int ac,char** av) {
	LOG_Init();
	tClock = clock();
// NOTE:SDL_INIT_VIDEO must be here for SDL_Joystick event processing. Joystick doesn't works without video init
#if USE_QT_GAMEPAD && 0
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER);
#else
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER);
#endif
	atexit(SDL_Quit);
	SDL_version sdlver;
	SDL_VERSION(&sdlver)
	printf("Using SDL ver %u.%u.%u\n", sdlver.major, sdlver.minor, sdlver.patch);

#ifdef HAVEZLIB
	printf("Using ZLIB ver %s\n",ZLIB_VERSION);
#endif
	printf("Using Qt ver %s\n",qVersion());

// this works since Qt5.6 (must be set before QCoreApplication is created). Set by default in Qt6
	#if (QT_VERSION >= QT_VERSION_CHECK(5,6,0)) && (QT_VERSION < QT_VERSION_CHECK(6,0,0))
		QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
		QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	#endif
	xApp app(ac,av,true);

#ifdef _WIN32
	app.addLibraryPath(".\\");
#endif
	sndInit();
	conf_init(av[0], NULL);
	shortcut_init();
	loadConfig();

	MainWin mwin;
	xThread ethread;
	DebugWin dbgw(&mwin);
	SetupWin optw(&mwin);
	TapeWin tapw(&mwin);
	RZXWin rzxw(&mwin);
	xWatcher wutw(&mwin);
	keyWindow keyw(&mwin);

	int id = QFontDatabase::addApplicationFont(":/DejaVuSansMono.ttf");
	if (id > -1) {
		dbgw.setFont(QFont(QFontDatabase::applicationFontFamilies(id).first(), 10));
	}

	mwin.onPrfChange();
	dbgw.onPrfChange();
	dbgw.setFont(conf.dbg.font);
//	mwin.loadShader();
	mwin.fillUserMenu();
	if ((conf.xpos >= 0) && (conf.ypos >= 0))
		mwin.move(conf.xpos, conf.ypos);

//	app.connect(&ethread, SIGNAL(s_frame()), &mwin, SLOT(d_frame()));	// don't use connection between threads
	app.connect(&ethread, SIGNAL(s_frame()), &app, SLOT(d_frame()));	// double connection xThread->xApp->MainWin to be thread-safe
	app.connect(&app, SIGNAL(s_frame()), &mwin, SLOT(d_frame()));

	app.connect(&ethread, SIGNAL(dbgRequest()), &mwin, SLOT(doDebug()));	// same shit?
	app.connect(&ethread, SIGNAL(tapeSignal(int,int)), &mwin,SLOT(tapStateChanged(int,int)));
	app.connect(&mwin, SIGNAL(s_emulwin_close()), &ethread, SLOT(stop()));

	app.connect(&dbgw, SIGNAL(closed()), &mwin, SLOT(dbgReturn()));
	app.connect(&dbgw, SIGNAL(wannaKeys()), &keyw, SLOT(show()));
	app.connect(&dbgw, SIGNAL(wannaWutch()), &wutw, SLOT(show()));
	app.connect(&dbgw, SIGNAL(wannaOptions()), &optw, SLOT(start()));

	app.connect(&mwin, SIGNAL(s_debug()), &dbgw, SLOT(start()));
	app.connect(&mwin, SIGNAL(s_debug_off()), &dbgw, SLOT(close()));
//	app.connect(&mwin, SIGNAL(s_prf_change(xProfile*)), &dbgw, SLOT(onPrfChange(xProfile*)));
	app.connect(&mwin, SIGNAL(s_step()), &dbgw, SLOT(doStep()));
	app.connect(&mwin, SIGNAL(s_scradr(int,int)), &dbgw, SLOT(setScrAtr(int,int)));

	app.connect(&mwin, SIGNAL(s_options()), &optw, SLOT(start()));
	app.connect(&mwin, SIGNAL(s_gamepad_plug()), &optw, SLOT(setPadName()));
	app.connect(&optw, SIGNAL(closed()), &mwin, SLOT(optApply()));
	app.connect(&optw, SIGNAL(s_apply()), &dbgw, SLOT(updateStyle()));
	app.connect(&optw, SIGNAL(s_prf_changed()), &mwin, SLOT(onPrfChange()));
	app.connect(&optw, SIGNAL(s_prf_changed()), &dbgw, SLOT(onPrfChange()));

	app.connect(&mwin, SIGNAL(s_tape_upd(Tape*)), &tapw, SLOT(upd(Tape*)));
	app.connect(&mwin, SIGNAL(s_tape_blk(Tape*)), &tapw, SLOT(updList(Tape*)));
	app.connect(&mwin, SIGNAL(s_tape_progress(Tape*)), &tapw, SLOT(updProgress(Tape*)));
	app.connect(&mwin, SIGNAL(s_tape_show()), &tapw, SLOT(show()));

	app.connect(&rzxw, SIGNAL(stateChanged(int)), &mwin, SLOT(rzxStateChanged(int)));
	app.connect(&mwin, SIGNAL(s_rzx_start()), &rzxw, SLOT(startPlay()));
	app.connect(&mwin, SIGNAL(s_rzx_stop()), &rzxw, SLOT(stop()));
	app.connect(&mwin, SIGNAL(s_rzx_upd(Computer*)), &rzxw, SLOT(upd(Computer*)));
	app.connect(&mwin, SIGNAL(s_rzx_show()), &rzxw, SLOT(show()));

	app.connect(&mwin, SIGNAL(s_watch_upd(Computer*)), &wutw, SLOT(fillFields(Computer*)));
	app.connect(&mwin, SIGNAL(s_watch_show()), &wutw, SLOT(show()));

	app.connect(&mwin, SIGNAL(s_keywin_shide()), &keyw, SLOT(switcher()));
	app.connect(&mwin, SIGNAL(s_keywin_upd(Keyboard*)), &keyw, SLOT(upd(Keyboard*)));
	app.connect(&mwin, SIGNAL(s_keywin_close()), &keyw, SLOT(close()));
	app.connect(&mwin, SIGNAL(s_keywin_rall(Keyboard*)), &keyw, SLOT(rall(Keyboard*)));
	app.connect(&keyw, SIGNAL(s_key_press(QKeyEvent*)), &mwin, SLOT(kPress(QKeyEvent*)));
	app.connect(&keyw, SIGNAL(s_key_release(QKeyEvent*)), &mwin, SLOT(kRelease(QKeyEvent*)));

	int i = 1;
	char* parg;
	int adr = 0x4000;

	int dbg = 0;
	int hlp = 0;
	int drv = 0;
	int lab = 1;
	xAdr xadr;
	int tmpi;
#ifdef __APPLE__
	int style = 0;
#endif
	while (i < ac) {
		parg = av[i++];
		if (!strcmp(parg,"-d") || !strcmp(parg,"--debug")) {
			dbg = 1;
		} else if (!strcmp(parg,"-h") || !strcmp(parg,"--help")) {
			help();
			hlp = 1;
#ifdef __WIN32
		} else if (!strcmp(parg,"-c") || !strcmp(parg,"--console")) {
			AllocConsole();
			int res = AttachConsole(ATTACH_PARENT_PROCESS);
			if (res == 0) {
				freopen("CONOUT$", "w", stdout);
				freopen("CONOUT$", "w", stderr);
			} else {

			}
#endif
#ifdef __APPLE__
		} else if (!strcmp(parg, "--style")) {
			style = 1;
#endif
		} else if (i < ac) {
			if (!strcmp(parg,"-p") || !strcmp(parg,"--profile")) {
				prfSetCurrent(av[i]);
				mwin.onPrfChange();
				dbgw.onPrfChange();
				//mwin.setProfile(std::string(av[i]));
				i++;
			} else if (!strcmp(parg,"--pc")) {
				conf.prof.cur->zx->cpu->pc = strtol(av[i],NULL,0) & 0xffff;
				i++;
			} else if (!strcmp(parg,"--sp")) {
				conf.prof.cur->zx->cpu->sp = strtol(av[i],NULL,0) & 0xffff;
				i++;
			} else if (!strcmp(parg,"-b") || !strcmp(parg,"--bank")) {
				memSetBank(conf.prof.cur->zx->mem, 0xc0, MEM_RAM, strtol(av[i],NULL,0), MEM_16K, NULL, NULL, NULL);
				i++;
			} else if (!strcmp(parg,"-a") || !strcmp(parg,"--adr")) {
				adr = strtol(av[i],NULL,0) & 0xffff;
				i++;
			} else if (!strcmp(parg,"-f") || !strcmp(parg,"--file")) {
				loadDUMP(conf.prof.cur->zx, av[i], adr);
				i++;
			} else if (!strcmp(parg,"--bp")) {
				if (conf.prof.cur->labels.contains(av[i])) {
					xadr = conf.prof.cur->labels[av[i]];
					if (xadr.adr >= 0) {
						brkSet(BRK_CPUADR, MEM_BRK_FETCH, xadr.adr & 0xffff, -1);
					}
				} else {
					brkSet(BRK_CPUADR, MEM_BRK_FETCH, strtol(av[i],NULL,0) & 0xffff, -1);
				}
				i++;
			} else if (!strcmp(parg,"-l") || !strcmp(parg,"--labels")) {
				lab = loadLabels(av[i]);
				i++;
			} else if (!strcmp(parg,"-s") || !strcmp(parg, "--size")) {
				tmpi = atoi(av[i]);
				if ((tmpi > 0) && (tmpi <= 6))
					conf.vid.scale = tmpi;
				i++;
			} else if (!strcmp(parg, "-n") || !strcmp(parg, "--noflick")) {
				tmpi = atoi(av[i]);
				if ((tmpi >= 0) && (tmpi <= 100))
					noflic = tmpi / 2;
				i++;
			} else if (!strcmp(parg, "-r") || !strcmp(parg, "--ratio")) {
				conf.vid.keepRatio = atoi(av[i]) ? 1 : 0;
				i++;
			} else if (!strcmp(parg,"--fullscreen")) {
				conf.vid.fullScreen = atoi(av[i]) ? 1 : 0;
				i++;
			} else if (!strcmp(parg, "--disk")) {
				parg = av[i];
				if (strlen(parg) == 1) {
					switch(parg[0]) {
						case '0': case 'a': case 'A': drv = 0; break;
						case '1': case 'b': case 'B': drv = 1; break;
						case '2': case 'c': case 'C': drv = 2; break;
						case '3': case 'd': case 'D': drv = 3; break;
					}
				}
				i++;
			} else if (!strcmp(parg, "--xmap")) {
				load_xmap(av[i]);
				i++;
			} else if (!strcmp(parg, "--confdir")) {
				conf_init(av[0], av[i]);
				i++;
				loadConfig();
			} else if (strlen(parg) > 0) {
				load_file(conf.prof.cur->zx, parg, FG_ALL, drv);
			}
		} else if (strlen(parg) > 0) {
			load_file(conf.prof.cur->zx, parg, FG_ALL, drv);
		}
	}
	dbgw.move(conf.dbg.pos);
	dbgw.resize(conf.dbg.siz);
#ifdef __APPLE__
	if (!style) {
		app.setStyle(QStyleFactory::create("Fusion"));
	}
#endif
	if (!hlp) {
//		mwin.blockSignals(true);
		mwin.show();		// causes an exception on resizeEvent -> emit resized()
		mwin.raise();
		mwin.activateWindow();
		mwin.updateWindow();
		mwin.checkState();
		if (dbg) mwin.doDebug();
		conf.running = 1;
		ethread.start();
		if (!lab) shitHappens("Can't open labels file");
//		mwin.blockSignals(false);
		app.exec();
		ethread.stop();
		ethread.wait();
	}
	conf.running = 0;
	sndClose();
#if defined(__WIN32)
	getch();
	FreeConsole();
#endif
	printf("exit\n");
	return 0;
}
