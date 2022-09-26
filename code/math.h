#pragma once

#include <math.h>
#include <stdbool.h>

#define EPSILON 0.0001f

inline bool FloatEquals(float a, float b)
{
    return fabsf(a - b) < EPSILON;
}

float Clamp(float value, float min, float max);

inline float Lerp(float min, float max, float rate)
{
    return (max - min) * rate + min;
}

void AddMathTests(void);
