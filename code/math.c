#pragma warning(disable: 5045) // Not bounds-checking.

#include "./math.h"

float Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

#include "./unit_test.h"

static void TestFloatEquals(void)
{
    AssertTrue(FloatEquals(0.005f, 0.005f));
    AssertTrue(FloatEquals(-1.0f, -1.0f));
    AssertFalse(FloatEquals(1.0f, 1.01f));
    AssertFalse(FloatEquals(-1.0f, 1.0f));
}

static void TestClamp(void)
{
    AssertTrue(FloatEquals(Clamp(5.0f, 0.0f, 10.0f), 5.0f));
    AssertTrue(FloatEquals(Clamp(11.0f, 0.0f, 10.0f), 10.0f));
    AssertTrue(FloatEquals(Clamp(-1.0f, 0.0f, 10.0f), 0.0f));
}

static void TestLerp(void)
{
    AssertTrue(FloatEquals(Lerp(1.0f, 9.0f, 1.0f), 9.0f));
    AssertTrue(FloatEquals(Lerp(1.0f, 9.0f, 0.0f), 1.0f));
    AssertTrue(FloatEquals(Lerp(1.0f, 9.0f, 0.5f), 5.0f));
}

void AddMathTests(void)
{
    AddUnitTest(TestFloatEquals);
    AddUnitTest(TestClamp);
    AddUnitTest(TestLerp);
}
