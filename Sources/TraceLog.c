#include "TraceLog.h"

#include <stdio.h>
#include <stdarg.h>

static LogLevel logLevel = LogLevel_Info;

void SetTraceLogLevel(LogLevel logLevel_)
{
    logLevel = logLevel_;
}

void TraceLog(LogLevel logLevel_, char *format, ...)
{
    if (logLevel_ < logLevel)
        return;

    va_list args;
    va_start(args, format);

    switch (logLevel_)
    {
    case LogLevel_Debug:
        printf("DEBUG: ");
        break;
    case LogLevel_Info:
        printf("INFO: ");
        break;
    case LogLevel_Warn:
        printf("WARN: ");
        break;
    case LogLevel_Error:
        printf("ERROR: ");
        break;
    }

    vprintf(format, args);
    printf("\n");

    va_end(args);
}
