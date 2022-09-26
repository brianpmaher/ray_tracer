#pragma once

#include <stdbool.h>

typedef void (*TestFunction)(void);

void RunUnitTests(void);

void AddUnitTest(TestFunction testFunction);

void _AssertTrue(char *file, int line, bool value);

#define AssertTrue(value) _AssertTrue(__FILE__, __LINE__, value)

void _AssertFalse(char *file, int line, bool value);

#define AssertFalse(value) _AssertFalse(__FILE__, __LINE__, value)
