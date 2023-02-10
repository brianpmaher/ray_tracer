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

#define MATRIX4_IDENTITY \
    (Matrix4)            \
    {                    \
        1, 0, 0, 0,      \
        0, 1, 0, 0,      \
        0, 0, 1, 0,      \
        0, 0, 0, 1       \
    }

bool Matrix2Equals(Matrix2 a, Matrix2 b);

// TODO: Implement
float Matrix2Determinant(Matrix2 a);

bool Matrix3Equals(Matrix3 a, Matrix3 b);

// TODO: Implement
float Matrix3Determinant(Matrix3 a);

// TODO: Implement
Matrix2 Matrix3Submatrix(Matrix3 a, int row, int column);

// TODO: Implement
float Matrix3Minor(Matrix3 a, int row, int column);

// TODO: Implement
float Matrix3Cofactor(Matrix3 a, int row, int column);

bool Matrix4Equals(Matrix4 a, Matrix4 b);

Matrix4 Matrix4Multiply(Matrix4 a, Matrix4 b);

Matrix4 Matrix4Transpose(Matrix4 a);

// TODO: Implement
Matrix4 Matrix4Invert(Matrix4 a);

// TODO: Implement
float Matrix4Determinant(Matrix4 a);

// TODO: Implement
Matrix3 Matrix4Submatrix(Matrix4 a, int row, int column);

// TODO: Implement
float Matrix4Minor(Matrix4 a, int row, int column);

// TODO: Implement
float Matrix4Cofactor(Matrix4 a, int row, int column);

void AddMatrixTests();
