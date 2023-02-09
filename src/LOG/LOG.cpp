#include <stdarg.h>
#include <string.h>
#include <QString>
#include <QDateTime>
#include <QFileInfo>
#include "LOG.h"

#ifdef __WIN32
#include "windows.h"
#endif

char * filename = NULL;
FILE * logFile;

int LOG_Init()
{
#ifdef __WIN32

	char pBuf[512];
	size_t len = sizeof(pBuf);
	int bytes = GetModuleFileName(NULL, pBuf, len);

	QString newFilename;
	QFileInfo File {QString(pBuf)};
	newFilename = File.canonicalPath()+"\\Xpeccy.log";

//	LOG_OutputMisc("Path=%s\n",(QCoreApplication::applicationFilePath()).toStdString().c_str());

	if(filename)
		delete [] filename;

	filename=new char[newFilename.length()+1];

	if(!filename)
		return 0;

	strcpy_s(filename, newFilename.length()+1, newFilename.toStdString().c_str());

	if ((logFile = fopen(filename, "wb")) == NULL)
		return 0;

	fclose(logFile);
//	logFile = NULL;
	logFile = fopen(filename, "a+");

	QString formattedTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	LOG_OutputMisc("Start logging at %s ... \n\n", formattedTime.toStdString().c_str());
#endif
	return 1;
}

#ifdef __WIN32
int LOG_OutputMisc(const char * text, ...)
{
	va_list argList;
	va_start(argList, text);
	if (filename==NULL) return -1;

	if (logFile == NULL) {
		va_end(argList);
		return 0;
	}

	QString formattedTime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");

	fprintf(logFile, "%s : ", formattedTime.toStdString().c_str());
	vfprintf(logFile, text, argList);
//	fclose(logFile);
	fflush(logFile);
//	logFile = NULL;
	va_end(argList);
	return 1;
}

#endif
