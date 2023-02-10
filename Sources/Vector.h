#pragma once

#include "Math.h"
#include "Matrix.h"

#include <stdbool.h>

typedef struct Vector3 Vector3;

typedef struct Vector4 Vector4;

struct Vector3
{
    float x;
    float y;
    float z;
};

struct Vector4
{
    float x;
    float y;
    float z;
    float w;
};

#define VECTOR3_ZERO (Vector3){ 0.0f, 0.0f, 0.0f }

bool Vector3Equals(Vector3 a, Vector3 b);

Vector3 Vector3Add(Vector3 a, Vector3 b);

Vector3 Vector3Sub(Vector3 a, Vector3 b);

Vector3 Vector3Negate(Vector3 a);

Vector3 Vector3MulScalar(Vector3 a, float scalar);

Vector3 Vector3DivScalar(Vector3 a, float scalar);

float Vector3Magnitude(Vector3 a);

Vector3 Vector3Normalize(Vector3 a);

float Vector3Dot(Vector3 a, Vector3 b);

Vector3 Vector3Cross(Vector3 a, Vector3 b);

bool Vector4Equals(Vector4 a, Vector4 b);

Vector4 Vector4MulMatrix4(Vector4 a, Matrix4 b);

void AddVectorTests();
