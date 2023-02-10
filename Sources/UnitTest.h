#pragma once

#include <stdbool.h>

typedef void (*TestFunction)();

void RunUnitTests(void);

void AddUnitTest(TestFunction testFunction);

void AssertTrue_(char *file, int line, bool value);

#define AssertTrue(value) AssertTrue_(__FILE__, __LINE__, value)

void AssertFalse_(char *file, int line, bool value);

#define AssertFalse(value) AssertFalse_(__FILE__, __LINE__, value)
