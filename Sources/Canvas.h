#pragma once

#include "Color.h"

#include <stdlib.h>

typedef struct Canvas Canvas;

struct Canvas
{
    int width;
    int height;
    Color *pixels;
};

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

void WritePPM(Canvas canvas, const char *fileName);

void AddCanvasTests(void);
