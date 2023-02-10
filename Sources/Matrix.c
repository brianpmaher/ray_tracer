#include "Matrix.h"

bool Matrix2Equals(Matrix2 a, Matrix2 b)
{
    return FloatEquals(a.m00, b.m00) && FloatEquals(a.m01, b.m01) &&
           FloatEquals(a.m10, b.m10) && FloatEquals(a.m11, b.m11);
}

float Matrix2Determinant(Matrix2 a)
{
    return a.m00 * a.m11 - a.m01 * a.m10;
}

bool Matrix3Equals(Matrix3 a, Matrix3 b)
{
    return FloatEquals(a.m00, b.m00) && FloatEquals(a.m01, b.m01) && FloatEquals(a.m02, b.m02) &&
           FloatEquals(a.m10, b.m10) && FloatEquals(a.m11, b.m11) && FloatEquals(a.m12, b.m12) &&
           FloatEquals(a.m20, b.m20) && FloatEquals(a.m21, b.m21) && FloatEquals(a.m22, b.m22);
}

bool Matrix4Equals(Matrix4 a, Matrix4 b)
{
    return FloatEquals(a.m00, b.m00) && FloatEquals(a.m01, b.m01) && FloatEquals(a.m02, b.m02) && FloatEquals(a.m03, b.m03) &&
           FloatEquals(a.m10, b.m10) && FloatEquals(a.m11, b.m11) && FloatEquals(a.m12, b.m12) && FloatEquals(a.m13, b.m13) &&
           FloatEquals(a.m20, b.m20) && FloatEquals(a.m21, b.m21) && FloatEquals(a.m22, b.m22) && FloatEquals(a.m23, b.m23) &&
           FloatEquals(a.m30, b.m30) && FloatEquals(a.m31, b.m31) && FloatEquals(a.m32, b.m32) && FloatEquals(a.m33, b.m33);
}

Matrix4 Matrix4Multiply(Matrix4 a, Matrix4 b)
{
    return (Matrix4){
        a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30,
        a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31,
        a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32,
        a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,

        a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30,
        a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
        a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
        a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,

        a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30,
        a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
        a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
        a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,

        a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30,
        a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
        a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
        a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33,
    };
}

Matrix4 Matrix4Transpose(Matrix4 a)
{
    return (Matrix4){
        a.m00, a.m10, a.m20, a.m30,
        a.m01, a.m11, a.m21, a.m31,
        a.m02, a.m12, a.m22, a.m32,
        a.m03, a.m13, a.m23, a.m33,
    };
}

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

static void TestMatrix2Determinant()
{
    Matrix2 a = {
        1.0f, 5.0f,
        -3.0f, 2.0f
    };
    AssertTrue(FloatEquals(Matrix2Determinant(a), 17.0f));
}

static void TestMatrix3Equals()
{
    Matrix3 a = {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        9.0f, 10.0f, 11.0f
    };
    Matrix3 b = {
        1.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        9.0f, 10.0f, 11.0f
    };
    AssertTrue(Matrix3Equals(a, b));
    b = (Matrix3){
        5.0f, 2.0f, 3.0f,
        5.0f, 6.0f, 7.0f,
        9.0f, 10.0f, 11.0f
    };
    AssertFalse(Matrix3Equals(a, b));
}

static void TestMatrix4Equals()
{
    Matrix4 a = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    Matrix4 b = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    AssertTrue(Matrix4Equals(a, b));
    b = (Matrix4){
        5.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };
    AssertFalse(Matrix4Equals(a, b));
}

static void TestMatrix4Multiply()
{
    Matrix4 a = {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 8.0f, 7.0f, 6.0f,
        5.0f, 4.0f, 3.0f, 2.0f
    };
    Matrix4 b = {
        -2.0f, 1.0f, 2.0f, 3.0f,
        3.0f, 2.0f, 1.0f, -1.0f,
        4.0f, 3.0f, 6.0f, 5.0f,
        1.0f, 2.0f, 7.0f, 8.0f
    };
    Matrix4 c = Matrix4Multiply(a, b);
    Matrix4 expected = {
        20.0f, 22.0f, 50.0f, 48.0f,
        44.0f, 54.0f, 114.0f, 108.0f,
        40.0f, 58.0f, 110.0f, 102.0f,
        16.0f, 26.0f, 46.0f, 42.0f
    };
    AssertTrue(Matrix4Equals(c, expected));

    Matrix4 identity = MATRIX4_IDENTITY;
    AssertTrue(Matrix4Equals(Matrix4Multiply(identity, a), a));
}

static void TestMatrix4Transpose()
{
    Matrix4 a = {
        0, 9, 3, 0,
        9, 8, 0, 8,
        1, 8, 5, 3,
        0, 0, 5, 8 };
    Matrix4 b = Matrix4Transpose(a);
    Matrix4 expected = {
        0, 9, 1, 0,
        9, 8, 8, 0,
        3, 0, 5, 5,
        0, 8, 3, 8 };
    AssertTrue(Matrix4Equals(b, expected));
    AssertTrue(Matrix4Equals(Matrix4Transpose(MATRIX4_IDENTITY), MATRIX4_IDENTITY));
}

void AddMatrixTests()
{
    AddUnitTest(TestMatrix2);
    AddUnitTest(TestMatrix3);
    AddUnitTest(TestMatrix4);
    AddUnitTest(TestMatrix2Equals);
    AddUnitTest(TestMatrix2Determinant);
    AddUnitTest(TestMatrix3Equals);
    AddUnitTest(TestMatrix4Equals);
    AddUnitTest(TestMatrix4Multiply);
    AddUnitTest(TestMatrix4Transpose);
}
