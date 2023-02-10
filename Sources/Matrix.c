#include "Matrix.h"

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

#include "UnitTest.h"

static void TestMatrix2()
{
    Matrix2 matrix = {
        -3.0f, 5.0f,
        1.0f, -2.0f,
    };

    AssertTrue(FloatEquals(matrix.m00, -3.0f));
    AssertTrue(FloatEquals(matrix.m01, 5.0f));
    AssertTrue(FloatEquals(matrix.m10, 1.0f));
    AssertTrue(FloatEquals(matrix.m11, -2.0f));
}

static void TestMatrix3()
{
    Matrix3 matrix = {
        -3.0f,  5.0f,  0.0f,
         1.0f, -2.0f, -7.0f,
         0.0f,  1.0f,  1.0f,
    };

    AssertTrue(FloatEquals(matrix.m00, -3.0f));
    AssertTrue(FloatEquals(matrix.m11, -2.0f));
    AssertTrue(FloatEquals(matrix.m22, 1.0f));
}

static void TestMatrix4()
{
    Matrix4 matrix = {
        1.0f,  2.0f,  3.0f,  4.0f,
        5.5f,  6.5f,  7.5f,  8.5f,
        9.0f,  10.0f, 11.0f, 12.0f,
        13.5f, 14.5f, 15.5f, 16.5f,
    };

    AssertTrue(FloatEquals(matrix.m00, 1.0f));
    AssertTrue(FloatEquals(matrix.m03, 4.0f));
    AssertTrue(FloatEquals(matrix.m10, 5.5f));
    AssertTrue(FloatEquals(matrix.m12, 7.5f));
    AssertTrue(FloatEquals(matrix.m22, 11.0f));
    AssertTrue(FloatEquals(matrix.m30, 13.5f));
    AssertTrue(FloatEquals(matrix.m32, 15.5f));
}

static void TestMatrix2Equals()
{
    Matrix2 a = {
        1.0f, 2.0f,
        5.0f, 6.0f
    };
    Matrix2 b = {
        1.0f, 2.0f,
        5.0f, 6.0f
    };
    AssertTrue(Matrix2Equals(a, b));
    b = (Matrix2){
        5.0f, 2.0f,
        5.0f, 6.0f
    };
    AssertFalse(Matrix2Equals(a, b));
}

void AddMatrixTests()
{
    AddUnitTest(TestMatrix2);
    AddUnitTest(TestMatrix3);
    AddUnitTest(TestMatrix4);
    AddUnitTest(TestMatrix2Equals);
}
