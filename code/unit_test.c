#include "./trace_log.h"
#include "./unit_test.h"

#pragma warning(disable: 5045) // Spectre mitigation.

#define MAX_UNIT_TESTS 1024

static TestFunction unitTests[MAX_UNIT_TESTS];
static int unitTestsCount = 0;
static int numAssertions = 0;
static bool testResult;

void RunUnitTests(void)
{
    int numTestsPassed = 0;
    numAssertions = 0;

    DebugLog("Running Unit tests");
    for (int i = 0; i < unitTestsCount; i++)
    {
        testResult = true;
        unitTests[i]();

        if (testResult == true)
            numTestsPassed++;
    }

    SetTraceLogLevel(LOG_DEBUG);

    DebugLog("%d / %d tests passed.", numTestsPassed, unitTestsCount);
    DebugLog("%d assertions executed.", numAssertions);
}

void AddUnitTest(TestFunction testFunction)
{
    if (unitTestsCount == MAX_UNIT_TESTS)
    {
        ErrorLog("Maximum number of unit tests reached. Increase unitTests array size.");
        return;
    }

    unitTests[unitTestsCount++] = testFunction;
}

void _AssertTrue(char *file, int line, bool value)
{
    numAssertions++;

    if (value == false)
    {
        ErrorLog("Expected false to be true (%s::%d)", file, line);
        testResult = false;
    }
}

void _AssertFalse(char *file, int line, bool value)
{
    numAssertions++;

    if (value == true)
    {
        ErrorLog("Expected true to be false (%s::%d)", file, line);
        testResult = false;
    }
}
