#pragma once

#include <stdbool.h>

#include "./math.h"

typedef struct Matrix2 {
    float m00, m01;
    float m10, m11;
} Matrix2;

typedef struct Matrix3 {
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
} Matrix3;

typedef struct Matrix4 {
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;
} Matrix4;

inline bool Matrix2Equals(Matrix2 a, Matrix2 b)
{
    return FloatEquals(a.m00, b.m00) && FloatEquals(a.m01, b.m01) &&
           FloatEquals(a.m10, b.m10) && FloatEquals(a.m11, b.m11);
}

inline bool Matrix3Equals(Matrix3 a, Matrix3 b)
{
    // TODO: Implement
    return false;
}

inline bool Matrix4Equals(Matrix4 a, Matrix4 b)
{
    // TODO: Implement
    return false;
}

void AddMatrixTests(void);
