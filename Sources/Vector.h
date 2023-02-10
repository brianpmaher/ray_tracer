#pragma once

#include "Math.h"

#include <stdbool.h>

typedef struct Vector3 Vector3;

struct Vector3
{
    float x;
    float y;
    float z;
};

inline bool Vector3Equals(Vector3 a, Vector3 b)
{
    return FloatEquals(a.x, b.x) && FloatEquals(a.y, b.y) && FloatEquals(a.z, b.z);
}

inline Vector3 Vector3Add(Vector3 a, Vector3 b)
{
    return (Vector3){ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline Vector3 Vector3Sub(Vector3 a, Vector3 b)
{
    return (Vector3){ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vector3 Vector3Zero()
{
    return (Vector3){ 0.0f, 0.0f, 0.0f };
}

inline Vector3 Vector3Negate(Vector3 a)
{
    return (Vector3){ -a.x, -a.y, -a.z };
}

inline Vector3 Vector3MulScalar(Vector3 a, float scalar)
{
    return (Vector3){ a.x * scalar, a.y * scalar, a.z * scalar };
}

inline Vector3 Vector3DivScalar(Vector3 a, float scalar)
{
    return (Vector3){ a.x / scalar, a.y / scalar, a.z / scalar };
}

inline float Vector3Magnitude(Vector3 a)
{
    return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

inline Vector3 Vector3Normalize(Vector3 a)
{
    float magnitude = Vector3Magnitude(a);

    return (Vector3){ a.x / magnitude, a.y / magnitude, a.z / magnitude };
}

inline float Vector3Dot(Vector3 a, Vector3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3 Vector3Cross(Vector3 a, Vector3 b)
{
    return (Vector3){ a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x };
}

void AddVectorTests();
