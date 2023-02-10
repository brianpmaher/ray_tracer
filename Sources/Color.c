#include "Color.h"

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

#include "UnitTest.h"

static void TestColorIsEqual()
{
    Color a = { 4.3f, -4.2f, 3.1f };
    Color b = { 4.3f, -4.2f, 3.1f };
    AssertTrue(ColorEquals(a, b));

    b = (Color){ 3.3f, -4.2f, 3.1f };
    AssertFalse(ColorEquals(a, b));

    b = (Color){ 4.3f, -5.2f, 3.1f };
    AssertFalse(ColorEquals(a, b));

    b = (Color){ 4.3f, -4.2f, 3.5f };
    AssertFalse(ColorEquals(a, b));
}

static void TestColorAdd()
{
    Color a = { 3.0f, -2.0f, 5.0f };
    Color b = { -2.0f, 3.0f, 1.0f };
    AssertTrue(ColorEquals(ColorAdd(a, b), (Color){ 1.0f, 1.0f, 6.0f }));
}

static void TestColorSub()
{
    Color a = { 3.0f, 2.0f, 1.0f };
    Color b = { 5.0f, 6.0f, 7.0f };
    AssertTrue(ColorEquals(ColorSub(a, b), (Color){ -2.0f, -4.0f, -6.0f }));

    a = BLACK;
    b = (Color){ 1.0f, -2.0f, 3.0f };
    AssertTrue(ColorEquals(ColorSub(a, b), (Color){ -1.0f, 2.0f, -3.0f }));
}

static void TestColorMulScalar()
{
    Color a = { 1.0f, -2.0f, 3.0f };
    float scalar = 3.5f;
    AssertTrue(ColorEquals(ColorMulScalar(a, scalar), (Color){ 3.5f, -7.0f, 10.5f }));

    scalar = 0.5f;
    AssertTrue(ColorEquals(ColorMulScalar(a, scalar), (Color){ 0.5f, -1.0f, 1.5f }));
}

static void TestColorMul()
{
    Color a = { 1.0f, 0.2f, 0.4f };
    Color b = { 0.9f, 1.0f, 0.1f };
    AssertTrue(ColorEquals(ColorMul(a, b), (Color){ 0.9f, 0.2f, 0.04f }));
}

void AddColorTests()
{
    AddUnitTest(TestColorIsEqual);
    AddUnitTest(TestColorAdd);
    AddUnitTest(TestColorSub);
    AddUnitTest(TestColorMulScalar);
    AddUnitTest(TestColorMul);
}
