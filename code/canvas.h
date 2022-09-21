#pragma once

#include <stdlib.h>

#include "./tuple.h"

typedef struct Canvas {
    int width;
    int height;
    Color *pixels;
} Canvas;

Canvas CreateCanvas(int width, int height);

inline void FreeCanvasMemory(Canvas canvas)
{
    free(canvas.pixels);
}

void AddCanvasTests(void);
