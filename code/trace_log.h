#pragma once

typedef enum LogLevel {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
} LogLevel;

void SetTraceLogLevel(LogLevel logLevel);

void TraceLog(LogLevel logLevel, char *format, ...);
