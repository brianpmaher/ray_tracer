#pragma once

#include "Math.h"

#include <stdbool.h>

typedef struct Color Color;

struct Color
{
    float r;
    float g;
    float b;
};

#define BLACK (Color){ 0.0f, 0.0f, 0.0f }
#define WHITE (Color){ 1.0f, 1.0f, 1.0f }

inline bool ColorEquals(Color a, Color b)
{
    return FloatEquals(a.r, b.r) && FloatEquals(a.g, b.g) && FloatEquals(a.b, b.b);
}

inline Color ColorAdd(Color a, Color b)
{
    return (Color){ a.r + b.r, a.g + b.g, a.b + b.b };
}

inline Color ColorSub(Color a, Color b)
{
    return (Color){ a.r - b.r, a.g - b.g, a.b - b.b };
}

inline Color ColorMulScalar(Color a, float scalar)
{
    return (Color){ a.r * scalar, a.g * scalar, a.b * scalar };
}

inline Color ColorMul(Color a, Color b)
{
    return (Color){ a.r * b.r, a.g * b.g, a.b * b.b };
}

void AddColorTests();
