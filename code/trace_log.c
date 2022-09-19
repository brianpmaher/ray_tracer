#include <stdio.h>
#include <stdarg.h>

#include "./trace_log.h"

static LogLevel logLevel = LOG_INFO;

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
    case LOG_DEBUG:
        printf("DEBUG: ");
        break;
    case LOG_INFO:
        printf("INFO: ");
        break;
    case LOG_WARN:
        printf("WARN: ");
        break;
    case LOG_ERROR:
        printf("ERROR: ");
        break;
    }

    vprintf(format, args);
    printf("\n");

    va_end(args);
}
