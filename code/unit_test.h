#pragma once

#include <stdbool.h>

typedef bool (*TestFunction)(void);

void RunUnitTests(void);

void AddUnitTest(TestFunction testFunction);

#define Test(function, ...)          \
    static bool Test##function(void) \
    {                                \
        bool _testResult = true;     \
        __VA_ARGS__                  \
        return _testResult;          \
    }

bool _AssertTrue(char *file, int line, bool value);

#define AssertTrue(value) _testResult &= _AssertTrue(__FILE__, __LINE__, value)

bool _AssertFalse(char *file, int line, bool value);

#define AssertFalse(value) _testResult &= _AssertFalse(__FILE__, __LINE__, value)
