#include <math.h>

#include "./math.h"

#define EPSILON 0.0001f

bool IsEqual(float a, float b)
{
    return fabsf(a - b) < EPSILON;
}
