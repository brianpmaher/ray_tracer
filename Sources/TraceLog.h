#pragma once

typedef enum LogLevel LogLevel;

enum LogLevel
{
    LogLevel_Debug,
    LogLevel_Info,
    LogLevel_Warn,
    LogLevel_Error,
};

void SetTraceLogLevel(LogLevel logLevel);

void TraceLog(LogLevel logLevel, char *format, ...);

#define DebugLog(...) TraceLog(LogLevel_Debug, __VA_ARGS__);

#define InfoLog(...) TraceLog(LogLevel_Info, __VA_ARGS__);

#define WarnLog(...) TraceLog(LogLevel_Info, __VA_ARGS__);

#define ErrorLog(...) TraceLog(LogLevel_Error, __VA_ARGS__);
