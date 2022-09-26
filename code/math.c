#pragma warning(disable: 5045) // Not bounds-checking.

#include "./unit_test.h"
#include "./math.h"

float Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

Test(IsEqual,
{
    AssertTrue(IsEqual(0.005f, 0.005f));
    AssertTrue(IsEqual(-1.0f, -1.0f));
    AssertFalse(IsEqual(1.0f, 1.01f));
    AssertFalse(IsEqual(-1.0f, 1.0f));
})

Test(Clamp,
{
    AssertTrue(IsEqual(Clamp(5.0f, 0.0f, 10.0f), 5.0f));
    AssertTrue(IsEqual(Clamp(11.0f, 0.0f, 10.0f), 10.0f));
    AssertTrue(IsEqual(Clamp(-1.0f, 0.0f, 10.0f), 0.0f));
})

Test(Lerp,
{
    AssertTrue(IsEqual(Lerp(1.0f, 9.0f, 1.0f), 9.0f));
    AssertTrue(IsEqual(Lerp(1.0f, 9.0f, 0.0f), 1.0f));
    AssertTrue(IsEqual(Lerp(1.0f, 9.0f, 0.5f), 5.0f));
})

void AddMathTests(void)
{
    AddUnitTest(TestIsEqual);
    AddUnitTest(TestClamp);
    AddUnitTest(TestLerp);
}
