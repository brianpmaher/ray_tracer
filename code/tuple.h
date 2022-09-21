#pragma once

#include "./math.h"

#include <stdbool.h>

#define TUPLE_POINT_W 1.0f

#define TUPLE_VECTOR_W 0.0f

typedef struct Tuple {
    float x;
    float y;
    float z;
    float w;
} Tuple;

typedef Tuple Point;

typedef Tuple Vector;

typedef struct Color {
    float r;
    float g;
    float b;
} Color;

inline bool TupleIsEqual(Tuple a, Tuple b)
{
    return IsEqual(a.x, b.x) && IsEqual(a.y, b.y) && IsEqual(a.z, b.z) && IsEqual(a.w, b.w);
}

inline bool ColorIsEqual(Color a, Color b)
{
    return IsEqual(a.r, b.r) && IsEqual(a.g, b.g) && IsEqual(a.b, b.b);
}

#define IsEqual(a, b)        \
    _Generic((a),            \
        float: IsEqual,      \
        Tuple: TupleIsEqual, \
        Color: ColorIsEqual  \
    ) (a, b)

inline bool TupleIsPoint(Tuple a)
{
    return IsEqual(a.w, TUPLE_POINT_W);
}

#define IsPoint TupleIsPoint

inline bool TupleIsVector(Tuple a)
{
    return IsEqual(a.w, TUPLE_VECTOR_W);
}

#define IsVector TupleIsVector

inline Tuple CreatePoint(float x, float y, float z)
{
    return (Tuple){ x, y, z, TUPLE_POINT_W };
}

inline Tuple CreateVector(float x, float y, float z)
{
    return (Tuple){ x, y, z, TUPLE_VECTOR_W };
}

inline Color Black(void)
{
    return (Color){ 0.0f, 0.0f, 0.0f };
}

inline Color White(void)
{
    return (Color){ 1.0f, 1.0f, 1.0f };
}

inline Tuple TupleAdd(Tuple a, Tuple b)
{
    return (Tuple){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

inline Color ColorAdd(Color a, Color b)
{
    return (Color){ a.r + b.r, a.g + b.g, a.b + b.b };
}

#define Add(a, b)        \
    _Generic((a),        \
        Tuple: TupleAdd, \
        Color: ColorAdd  \
    ) (a, b)

inline Tuple TupleSub(Tuple a, Tuple b)
{
    return (Tuple){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

inline Color ColorSub(Color a, Color b)
{
    return (Color){ a.r - b.r, a.g - b.g, a.b - b.b };
}

#define Sub(a, b)        \
    _Generic((a),        \
        Tuple: TupleSub, \
        Color: ColorSub  \
    ) (a, b)

inline Tuple PointZero(void)
{
    return CreatePoint(0.0f, 0.0f, 0.0f);
}

inline Tuple VectorZero(void)
{
    return CreateVector(0.0f, 0.0f, 0.0f);
}

inline Tuple TupleNegate(Tuple a)
{
    return (Tuple){ -a.x, -a.y, -a.z, -a.w };
}

#define Negate TupleNegate

inline Tuple TupleMulScalar(Tuple a, float scalar)
{
    return (Tuple){ a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar };
}

inline Color ColorMulScalar(Color a, float scalar)
{
    return (Color){ a.r * scalar, a.g * scalar, a.b * scalar };
}

#define MulScalar(a, scalar)   \
    _Generic((a),              \
        Tuple: TupleMulScalar, \
        Color: ColorMulScalar  \
    ) (a, scalar)

#define Scale MulScalar

inline Color ColorMul(Color a, Color b)
{
    return (Color){ a.r * b.r, a.g * b.g, a.b * b.b };
}

#define Mul ColorMul

inline Tuple TupleDivScalar(Tuple a, float scalar)
{
    return (Tuple){ a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar };
}

#define DivScalar TupleDivScalar

inline float VectorMagnitude(Tuple a)
{
    return sqrtf(a.x*a.x + a.y*a.y + a.z*a.z + a.w*a.w);
}

#define Magnitude VectorMagnitude

inline Tuple VectorNormalize(Tuple a)
{
    float magnitude = VectorMagnitude(a);
    return CreateVector(a.x / magnitude, a.y / magnitude, a.z / magnitude);
}

#define Normalize VectorNormalize

inline float VectorDot(Tuple a, Tuple b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

#define Dot VectorDot

inline Tuple VectorCross(Tuple a, Tuple b)
{
    return CreateVector(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

#define Cross VectorCross

void AddTupleTests(void);
