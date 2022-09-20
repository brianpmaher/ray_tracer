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

inline bool TupleIsEqual(Tuple a, Tuple b)
{
    return IsEqual(a.x, b.x) && IsEqual(a.y, b.y) && IsEqual(a.z, b.z) && IsEqual(a.w, b.w);
}

#define IsEqual(a, b)       \
    _Generic((a),           \
        float: IsEqual,     \
        Tuple: TupleIsEqual \
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

inline Tuple TupleAdd(Tuple a, Tuple b)
{
    return (Tuple){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

#define Add TupleAdd

inline Tuple TupleSub(Tuple a, Tuple b)
{
    return (Tuple){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

#define Sub TupleSub

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

#define MulScalar TupleMulScalar

#define Scale TupleMulScalar

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
