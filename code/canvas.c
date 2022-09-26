#pragma warning(disable: 4996) // Unsafe function.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./canvas.h"
#include "./unit_test.h"
#include "./trace_log.h"

Canvas CreateCanvas(int width, int height)
{
    Canvas canvas;

    canvas.width = width;
    canvas.height = height;

    canvas.pixels = malloc(sizeof(Color) * width * height);

    for (int i = 0; i < width * height; i++)
        canvas.pixels[i] = BLACK;

    return canvas;
}

// TODO: Handle lines longer than 70
static char *CanvasToPPM(Canvas canvas)
{
    const int headerSizeEst = 32;
    const int initialSizeEst = canvas.width * canvas.height * 16 + headerSizeEst;
    char scratchBuffer[32];

    int bytesWritten = 0;
    int scratchBytesWritten = 0;
    char *ppmData = malloc(sizeof(initialSizeEst));

    // Build PPM header.
    ppmData[0] = "P3\n";
    bytesWritten += 3;
    scratchBytesWritten = sprintf(scratchBuffer, "%d %d\n", canvas.width, canvas.height);
    ppmData[bytesWritten] = scratchBuffer;
    bytesWritten += scratchBytesWritten;
    ppmData[bytesWritten] = "255\n";
    bytesWritten += 4;

    // Build PPM body.
    for (int y = 0; y < canvas.height; y++)
    {
        for (int x = 0; x < canvas.width; x++)
        {
            Color pixel = GetPixel(canvas, x, y);
            int red = (int)Clamp(Lerp(0.0f, 255.0f, pixel.r), 0.0f, 255.0f);
            int green = (int)Clamp(Lerp(0.0f, 255.0f, pixel.g), 0.0f, 255.0f);
            int blue = (int)Clamp(Lerp(0.0f, 255.0f, pixel.b), 0.0f, 255.0f);

            scratchBytesWritten = sprintf(scratchBuffer, "%d %d %d", red, green, blue);
            ppmData[bytesWritten] = scratchBuffer;
            bytesWritten += scratchBytesWritten;
            ppmData[bytesWritten] = x % canvas.width == 0 ? "\n" : " ";
            bytesWritten += 1;
        }

        ppmData[bytesWritten] = "\n";
        bytesWritten += 1;
    }

    ppmData[bytesWritten] = '\0';
    bytesWritten += 1;
    ppmData = realloc(ppmData, bytesWritten);

    return ppmData;
}

// TODO: Implement
void WritePPM(Canvas canvas)
{
}

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

static void TestCreateCanvas(void)
{
    Canvas c = CreateCanvas(10, 20);
    AssertTrue(c.width == 10);
    AssertTrue(c.height == 20);

    for (int i = 0; i < c.width * c.height; i++)
        AssertTrue(ColorEquals(c.pixels[i], BLACK));

    FreeCanvasMemory(c);
}

static void TestGetPixel(void)
{
    Canvas c = CreateCanvas(10, 20);
    Color red = { 1.0f, 0.0f, 0.0f };
    AssertTrue(ColorEquals(GetPixel(c, 0, 1), BLACK));

    c.pixels[10] = red;
    AssertTrue(ColorEquals(GetPixel(c, 0, 1), red));
}

static void TestSetPixel(void)
{
    Canvas c = CreateCanvas(10, 20);
    Color red = { 1.0f, 0.0f, 0.0f };
    SetPixel(&c, 2, 3, red);
    AssertTrue(ColorEquals(GetPixel(c, 2, 3), red));
}

static void TestCanvasToPPM(void)
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
}

void AddCanvasTests(void)
{
    AddUnitTest(TestCreateCanvas);
    AddUnitTest(TestGetPixel);
    AddUnitTest(TestSetPixel);
    // AddUnitTest(TestCanvasToPPM);
}
