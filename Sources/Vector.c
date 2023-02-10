#include "Vector.h"

#include <stdbool.h>

bool Vector3Equals(Vector3 a, Vector3 b)
{
    return FloatEquals(a.x, b.x) && FloatEquals(a.y, b.y) && FloatEquals(a.z, b.z);
}

Vector3 Vector3Add(Vector3 a, Vector3 b)
{
    return (Vector3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

Vector3 Vector3Sub(Vector3 a, Vector3 b)
{
    return (Vector3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

Vector3 Vector3Zero()
{
    return (Vector3){ 0.0f, 0.0f, 0.0f };
}

Vector3 Vector3Negate(Vector3 a)
{
    return (Vector3){ -a.x, -a.y, -a.z };
}

Vector3 Vector3MulScalar(Vector3 a, float scalar)
{
    return (Vector3){ a.x * scalar, a.y * scalar, a.z * scalar };
}

Vector3 Vector3DivScalar(Vector3 a, float scalar)
{
    return (Vector3){ a.x / scalar, a.y / scalar, a.z / scalar };
}

float Vector3Magnitude(Vector3 a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

Vector3 Vector3Normalize(Vector3 a)
{
    float magnitude = Vector3Magnitude(a);

    return (Vector3){ a.x / magnitude, a.y / magnitude, a.z / magnitude };
}

float Vector3Dot(Vector3 a, Vector3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3Cross(Vector3 a, Vector3 b)
{
    return (Vector3){ a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
}

bool Vector4Equals(Vector4 a, Vector4 b)
{
    return FloatEquals(a.x, b.x) && FloatEquals(a.y, b.y) && FloatEquals(a.z, b.z) && FloatEquals(a.w, b.w);
}

Vector4 Vector4MulMatrix4(Vector4 a, Matrix4 b)
{
    return (Vector4){
        a.x * b.m00 + a.y * b.m01 + a.z * b.m02 + a.w * b.m03,
        a.x * b.m10 + a.y * b.m11 + a.z * b.m12 + a.w * b.m13,
        a.x * b.m20 + a.y * b.m21 + a.z * b.m22 + a.w * b.m23,
        a.x * b.m30 + a.y * b.m31 + a.z * b.m32 + a.w * b.m33,
    };
}

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

    a = VECTOR3_ZERO;
    b = (Vector3){ 1.0f, -2.0f, 3.0f };
    AssertTrue(Vector3Equals(Vector3Sub(a, b), (Vector3){ -1.0f, 2.0f, -3.0f }));
}

static void TestVector3Zero()
{
    AssertTrue(Vector3Equals(VECTOR3_ZERO, (Vector3){ 0.0f, 0.0f, 0.0f }));
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

static void TestVector4Equals()
{
    Vector4 a = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vector4 b = { 1.0f, 2.0f, 3.0f, 4.0f };
    AssertTrue(Vector4Equals(a, b));

    b = (Vector4){ 1.0f, 2.0f, 3.0f, 5.0f };
    AssertFalse(Vector4Equals(a, b));
}

static void TestVector4MulMatrix4()
{
    Vector4 a = (Vector4){ 1.0f, 2.0f, 3.0f, 1.0f };
    Matrix4 b = (Matrix4){
        1.0f, 2.0f, 3.0f, 4.0f,
        2.0f, 4.0f, 4.0f, 2.0f,
        8.0f, 6.0f, 4.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    Vector4 result = Vector4MulMatrix4(a, b);
    Vector4 expected = { 18.0f, 24.0f, 33.0f, 1.0f };
    AssertTrue(Vector4Equals(result, expected));
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
    AddUnitTest(TestVector4Equals);
    AddUnitTest(TestVector4MulMatrix4);
}
