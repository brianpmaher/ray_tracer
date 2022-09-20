#pragma once

#include <math.h>
#include <stdbool.h>

#define EPSILON 0.0001f

inline bool IsEqual(float a, float b)
{
    return fabsf(a - b) < EPSILON;
}