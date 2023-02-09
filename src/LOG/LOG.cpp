#include <stdarg.h>
#include <string.h>
#include <QString>
#include <QDateTime>
#include "LOG.h"

char * filename;
FILE * logFile;

int LOG_Init(const char * newFilename)
{
#ifdef __WIN32
	if(filename)
		delete [] filename;

	filename=new char[strlen(newFilename)+1];
	if(!filename)
		return 0;

	strcpy_s(filename, strlen(newFilename)+1, newFilename);

	if ((logFile = fopen(filename, "wb")) == NULL)
		return 0;

	fclose(logFile);
	logFile = NULL;

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

	if ((logFile = fopen(filename, "a+")) == NULL) {
		va_end(argList);
		return 0;
	}

	QString formattedTime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");

	fprintf(logFile, "%s : ", formattedTime.toStdString().c_str());
	vfprintf(logFile, text, argList);
	fclose(logFile);
	logFile = NULL;
	va_end(argList);
	return 1;
}

#endif
