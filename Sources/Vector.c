#include "Vector.h"

#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

#include "UnitTest.h"

static void TestVector3Equals()
{
    Vector3 a = { 4.3f, -4.2f, 3.1f };
    Vector3 b = { 4.3f, -4.2f, 3.1f };
    AssertTrue(Vector3Equals(a, b));

    b = (Vector3){ 4.3f, -5.2f, 3.1f };
    AssertFalse(Vector3Equals(a, b));

    b = (Vector3){ 4.3f, -4.2f, 3.5f };
    AssertFalse(Vector3Equals(a, b));
}

static void TestVector3Add()
{
    Vector3 a = { 3.0f, -2.0f, 5.0f };
    Vector3 b = { -2.0f, 3.0f, 1.0f };
    AssertTrue(Vector3Equals(Vector3Add(a, b), (Vector3){ 1.0f, 1.0f, 6.0f }));
}

static void TestVector3Sub()
{
    Vector3 a = { 3.0f, 2.0f, 1.0f };
    Vector3 b = { 5.0f, 6.0f, 7.0f };
    AssertTrue(Vector3Equals(Vector3Sub(a, b), (Vector3){ -2.0f, -4.0f, -6.0f }));

    a = Vector3Zero();
    b = (Vector3){ 1.0f, -2.0f, 3.0f };
    AssertTrue(Vector3Equals(Vector3Sub(a, b), (Vector3){ -1.0f, 2.0f, -3.0f }));
}

static void TestVector3Zero()
{
    AssertTrue(Vector3Equals(Vector3Zero(), (Vector3){ 0.0f, 0.0f, 0.0f }));
}

static void TestVector3Negate()
{
    Vector3 a = { 1.0f, -2.0f, 3.0f };
    AssertTrue(Vector3Equals(Vector3Negate(a), (Vector3){ -1.0f, 2.0f, -3.0f }));
}

static void TestVector3MulScalar()
{
    Vector3 a = { 1.0f, -2.0f, 3.0f };
    float scalar = 3.5f;
    AssertTrue(Vector3Equals(Vector3MulScalar(a, scalar), (Vector3){ 3.5f, -7.0f, 10.5f }));

    scalar = 0.5f;
    AssertTrue(Vector3Equals(Vector3MulScalar(a, scalar), (Vector3){ 0.5f, -1.0f, 1.5f }));
}

static void TestVector3DivScalar()
{
    Vector3 a = { 1.0f, -2.0f, 3.0f };
    float scalar = 2;
    AssertTrue(Vector3Equals(Vector3DivScalar(a, scalar), (Vector3){ 0.5f, -1.0f, 1.5f }));
}

static void TestVector3Magnitude()
{
    Vector3 a = { 1.0f, 0.0f, 0.0f };
    AssertTrue(FloatEquals(Vector3Magnitude(a), 1.0f));

    a = (Vector3){ 0.0f, 1.0f, 0.0f };
    AssertTrue(FloatEquals(Vector3Magnitude(a), 1.0f));

    a = (Vector3){ 0.0f, 0.0f, 1.0f };
    AssertTrue(FloatEquals(Vector3Magnitude(a), 1.0f));

    a = (Vector3){ 1.0f, 2.0f, 3.0f };
    AssertTrue(FloatEquals(Vector3Magnitude(a), sqrtf(14)));

    a = (Vector3){ -1.0f, -2.0f, -3.0f };
    AssertTrue(FloatEquals(Vector3Magnitude(a), sqrtf(14)));
}

static void TestVector3Normalize()
{
    Vector3 a = { 4.0f, 0.0f, 0.0f };
    AssertTrue(Vector3Equals(Vector3Normalize(a), (Vector3){ 1.0f, 0.0f, 0.0f }));

    a = (Vector3){ 1.0f, 2.0f, 3.0f };
    AssertTrue(Vector3Equals(Vector3Normalize(a), (Vector3){ 0.26726f, 0.53452f, 0.80178f }));

    AssertTrue(FloatEquals(Vector3Magnitude(Vector3Normalize(a)), 1.0f));
}

static void TestVector3Dot()
{
    Vector3 a = (Vector3){ 1.0f, 2.0f, 3.0f };
    Vector3 b = (Vector3){ 2.0f, 3.0f, 4.0f };
    AssertTrue(FloatEquals(Vector3Dot(a, b), 20.0f));
}

static void TestVector3Cross()
{
    Vector3 a = (Vector3){ 1.0f, 2.0f, 3.0f };
    Vector3 b = (Vector3){ 2.0f, 3.0f, 4.0f };
    AssertTrue(Vector3Equals(Vector3Cross(a, b), (Vector3){ -1.0f, 2.0f, -1.0f }));
    AssertTrue(Vector3Equals(Vector3Cross(b, a), (Vector3){ 1.0f, -2.0f, 1.0f }));
}

void AddVectorTests()
{
    AddUnitTest(TestVector3Equals);
    AddUnitTest(TestVector3Add);
    AddUnitTest(TestVector3Sub);
    AddUnitTest(TestVector3Zero);
    AddUnitTest(TestVector3Negate);
    AddUnitTest(TestVector3MulScalar);
    AddUnitTest(TestVector3DivScalar);
    AddUnitTest(TestVector3Magnitude);
    AddUnitTest(TestVector3Normalize);
    AddUnitTest(TestVector3Dot);
    AddUnitTest(TestVector3Cross);
}
