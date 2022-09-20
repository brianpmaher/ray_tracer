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

inline bool TupleIsEqual(Tuple a, Tuple b)
{
    return IsEqual(a.x, b.x) && IsEqual(a.y, b.y) && IsEqual(a.z, b.z) && IsEqual(a.w, b.w);
}

inline bool TupleIsPoint(Tuple a)
{
    return IsEqual(a.w, TUPLE_POINT_W);
}

inline bool TupleIsVector(Tuple a)
{
    return IsEqual(a.w, TUPLE_VECTOR_W);
}

inline Tuple Point(float x, float y, float z)
{
    return (Tuple){ x, y, z, TUPLE_POINT_W };
}

inline Tuple Vector(float x, float y, float z)
{
    return (Tuple){ x, y, z, TUPLE_VECTOR_W };
}

inline Tuple TupleAdd(Tuple a, Tuple b)
{
    return (Tuple){ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

inline Tuple TupleSub(Tuple a, Tuple b)
{
    return (Tuple){ a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
}

void AddTupleTests(void);
