#pragma once

typedef enum LogLevel {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
} LogLevel;

void SetTraceLogLevel(LogLevel logLevel);

void TraceLog(LogLevel logLevel, char *format, ...);

#define DebugLog(...) TraceLog(LOG_DEBUG, __VA_ARGS__);

#define InfoLog(...) TraceLog(LOG_INFO, __VA_ARGS__);

#define WarnLog(...) TraceLog(LOG_WARN, __VA_ARGS__);

#define ErrorLog(...) TraceLog(LOG_ERROR, __VA_ARGS__);
