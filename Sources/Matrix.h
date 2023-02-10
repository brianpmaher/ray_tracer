#pragma once

#include "Math.h"

#include <stdbool.h>

typedef struct Matrix2 Matrix2;
typedef struct Matrix3 Matrix3;
typedef struct Matrix4 Matrix4;

struct Matrix2
{
    float m00, m01;
    float m10, m11;
};

struct Matrix3
{
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
};

struct Matrix4
{
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
};

inline bool Matrix2Equals(Matrix2 a, Matrix2 b)
{
    return FloatEquals(a.m00, b.m00) && FloatEquals(a.m01, b.m01) &&
           FloatEquals(a.m10, b.m10) && FloatEquals(a.m11, b.m11);
}

inline bool Matrix3Equals(Matrix3 a, Matrix3 b)
{
    return FloatEquals(a.m00, b.m00) && FloatEquals(a.m01, b.m01) && FloatEquals(a.m02, b.m02) &&
           FloatEquals(a.m10, b.m10) && FloatEquals(a.m11, b.m11) && FloatEquals(a.m12, b.m12) &&
           FloatEquals(a.m20, b.m20) && FloatEquals(a.m21, b.m21) && FloatEquals(a.m22, b.m22);
}

inline bool Matrix4Equals(Matrix4 a, Matrix4 b)
{
    return FloatEquals(a.m00, b.m00) && FloatEquals(a.m01, b.m01) && FloatEquals(a.m02, b.m02) && FloatEquals(a.m03, b.m03) &&
           FloatEquals(a.m10, b.m10) && FloatEquals(a.m11, b.m11) && FloatEquals(a.m12, b.m12) && FloatEquals(a.m13, b.m13) &&
           FloatEquals(a.m20, b.m20) && FloatEquals(a.m21, b.m21) && FloatEquals(a.m22, b.m22) && FloatEquals(a.m23, b.m23) &&
           FloatEquals(a.m30, b.m30) && FloatEquals(a.m31, b.m31) && FloatEquals(a.m32, b.m32) && FloatEquals(a.m33, b.m33);
}

void AddMatrixTests();
