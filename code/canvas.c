#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./canvas.h"
#include "./unit_test.h"

////////////////////////////////////////////////////////////////////////////////
//                                 Functions
////////////////////////////////////////////////////////////////////////////////

Canvas CreateCanvas(int width, int height)
{
    Canvas canvas;

    canvas.width = width;
    canvas.height = height;

    canvas.pixels = malloc(sizeof(Color) * width * height);

    for (int i = 0; i < width * height; i++)
        canvas.pixels[i] = Black();

    return canvas;
}

// TODO: Handle lines longer than 70
static char *CanvasToPPM(Canvas canvas)
{
    const int headerSizeEst = 32;
    const int initialSizeEst = canvas.width * canvas.height * 16 + headerSizeEst;
    char scratchBuffer[32];

    char *ppmData = malloc(sizeof(initialSizeEst));

    // Build header.
    strcat(ppmData, "P3\n");
    sprintf(scratchBuffer, "%d %d\n", canvas.width, canvas.height);
    strcat(ppmData, scratchBuffer);
    strcat(ppmData, "255\n");

    // Build body.
    for (int y = 0; y < canvas.height; y++)
    {
        for (int x = 0; x < canvas.width; x++)
        {
            Color pixel = GetPixel(canvas, x, y);
            // TODO: map rgb from 0-1 to 0-255
            sprintf(scratchBuffer, "%d %d %d", pixel.r, pixel.g, pixel.b);
            strcat(ppmData, scratchBuffer);

            if (x % canvas.width == 0)
                strcat(ppmData, "\n");
        }

        strcat(ppmData, "\n");
    }

    return ppmData;
}

// TODO: Implement
void WritePPM(Canvas canvas)
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

Test(CreateCanvas,
{
    Canvas c = CreateCanvas(10, 20);
    AssertTrue(c.width == 10);
    AssertTrue(c.height == 20);

    for (int i = 0; i < c.width * c.height; i++)
        AssertTrue(IsEqual(c.pixels[i], Black()));

    FreeCanvasMemory(c);
})

Test(GetPixel,
{
    Canvas c = CreateCanvas(10, 20);
    Color red = { 1.0f, 0.0f, 0.0f };
    AssertTrue(IsEqual(GetPixel(c, 0, 1), Black()));

    c.pixels[10] = red;
    AssertTrue(IsEqual(GetPixel(c, 0, 1), red));
})

Test(SetPixel,
{
    Canvas c = CreateCanvas(10, 20);
    Color red = { 1.0f, 0.0f, 0.0f };
    SetPixel(&c, 2, 3, red);
    AssertTrue(IsEqual(GetPixel(c, 2, 3), red));
})

Test(CanvasToPPM,
{
    Canvas c = CreateCanvas(5, 3);
    SetPixel(&c, 0, 0, (Color){  1.5f, 0.0f, 0.0f });
    SetPixel(&c, 2, 1, (Color){  0.0f, 0.5f, 0.0f });
    SetPixel(&c, 4, 2, (Color){ -0.5f, 0.0f, 1.0f });
    const char *expectedPpm =
        "P3\n"                              \
        "5 3\n"                             \
        "255\n"                             \
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n" \
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n" \
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    char *ppmData = CanvasToPPM(c);
    AssertTrue(strcmp(ppmData, expectedPpm) == 0);
    free(ppmData);

    // TODO: Handle wrap at 70 lines
})

void AddCanvasTests(void)
{
    AddUnitTest(TestCreateCanvas);
    AddUnitTest(TestGetPixel);
    AddUnitTest(TestSetPixel);
    AddUnitTest(TestCanvasToPPM);
}
