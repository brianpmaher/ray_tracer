#pragma warning(disable: 5045) // Not bounds-checking.

#include "Math.h"

float Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

#include "UnitTest.h"

static void TestFloatEquals()
{
    AssertTrue(FloatEquals(0.005f, 0.005f));
    AssertTrue(FloatEquals(-1.0f, -1.0f));
    AssertFalse(FloatEquals(1.0f, 1.01f));
    AssertFalse(FloatEquals(-1.0f, 1.0f));
}

static void TestClamp()
{
    AssertTrue(FloatEquals(Clamp(5.0f, 0.0f, 10.0f), 5.0f));
    AssertTrue(FloatEquals(Clamp(11.0f, 0.0f, 10.0f), 10.0f));
    AssertTrue(FloatEquals(Clamp(-1.0f, 0.0f, 10.0f), 0.0f));
}

static void TestLerp()
{
    AssertTrue(FloatEquals(Lerp(1.0f, 9.0f, 1.0f), 9.0f));
    AssertTrue(FloatEquals(Lerp(1.0f, 9.0f, 0.0f), 1.0f));
    AssertTrue(FloatEquals(Lerp(1.0f, 9.0f, 0.5f), 5.0f));
}

void AddMathTests()
{
    AddUnitTest(TestFloatEquals);
    AddUnitTest(TestClamp);
    AddUnitTest(TestLerp);
}
