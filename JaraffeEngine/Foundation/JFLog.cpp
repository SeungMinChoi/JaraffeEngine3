#include "JFLog.h"

#include <stdio.h>
#include <stdarg.h>

void JFFoundation::JFLog(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	printf(fmt, ap);
	va_end(ap);
}

void JFFoundation::JFLog(const wchar_t* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	wprintf(fmt, ap);
	va_end(ap);
}