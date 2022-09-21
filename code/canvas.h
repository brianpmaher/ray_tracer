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

inline Color GetPixel(Canvas canvas, int x, int y)
{
    return canvas.pixels[x + y * canvas.width];
}

inline void SetPixel(Canvas *canvas, int x, int y, Color pixel)
{
    canvas->pixels[x + y * canvas->width] = pixel;
}

void WritePPM(Canvas canvas);

void AddCanvasTests(void);
