#include "./trace_log.h"
#include "./unit_test.h"

#pragma warning(disable: 5045)

#define MAX_UNIT_TESTS 1024

static TestFunction unitTests[MAX_UNIT_TESTS];
static int unitTestsCount = 0;
static int numAssertions = 0;

void RunUnitTests(void)
{
    int numTestsPassed = 0;
    numAssertions = 0;

    for (int i = 0; i < unitTestsCount; i++)
    {
        bool testResult = unitTests[i]();

        if (testResult == true)
            numTestsPassed++;
    }

    SetTraceLogLevel(LOG_DEBUG);

    TraceLog(LOG_DEBUG, "%d / %d tests passed.", numTestsPassed, unitTestsCount);
    TraceLog(LOG_DEBUG, "%d assertions executed.", numAssertions);
}

void AddUnitTest(TestFunction testFunction)
{
    if (unitTestsCount == MAX_UNIT_TESTS)
    {
        TraceLog(LOG_ERROR, "Maximum number of unit tests reached. Increase unitTests array size.");
        return;
    }

    unitTests[unitTestsCount++] = testFunction;
}

bool _AssertTrue(char *file, int line, bool value)
{
    numAssertions++;

    if (value == false)
    {
        TraceLog(LOG_ERROR, "Expected false to be true (%s::%d)", file, line);
        return false;
    }

    return true;
}

bool _AssertFalse(char *file, int line, bool value)
{
    numAssertions++;

    if (value == true)
    {
        TraceLog(LOG_ERROR, "Expected true to be false (%s::%d)", file, line);
        return false;
    }

    return true;
}
