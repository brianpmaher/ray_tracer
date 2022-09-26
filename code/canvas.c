#pragma warning(disable: 4996) // Unsafe function.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "./canvas.h"
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

static inline int ColorFloatToInt(float v)
{
    return (int)roundf(Clamp(Lerp(0.0f, 255.0f, v), 0.0f, 255.0f));
}

/**
 * Note: Allocates memory.
 */
static char *CanvasToPPM(Canvas canvas)
{
    const int headerSizeEst = 32;
    const int initialSizeEst = canvas.width * canvas.height * 16 + headerSizeEst;
    char scratchBuffer[32];

    int bytesWritten = 0;
    int scratchBytesWritten = 0;
    char *ppmData = malloc(initialSizeEst);

    ////////////////////////////////////////
    //            PPM header
    ////////////////////////////////////////

    strcpy(ppmData, "P3\n");
    bytesWritten += 3;
    scratchBytesWritten = sprintf(scratchBuffer, "%d %d\n", canvas.width, canvas.height);
    strcpy(&ppmData[bytesWritten], scratchBuffer);
    bytesWritten += scratchBytesWritten;
    strcpy(&ppmData[bytesWritten], "255\n");
    bytesWritten += 4;

    ////////////////////////////////////////
    //             PPM body
    ////////////////////////////////////////

    const int maxColorStrLen = 3;

    for (int y = 0; y < canvas.height; y++)
    {
        if (y > 0)
        {
            ppmData[bytesWritten++] = '\n';
        }

        for (int x = 0, lineLength = 0; x < canvas.width; x++)
        {
            Color pixel = GetPixel(canvas, x, y);
            int red = ColorFloatToInt(pixel.r);
            int green = ColorFloatToInt(pixel.g);
            int blue = ColorFloatToInt(pixel.b);

            ////////////////////////////////////////
            //                Red
            ////////////////////////////////////////

            if (lineLength > 0)
            {
                scratchBytesWritten = sprintf(scratchBuffer, " %d", red);
            }
            else
            {
                scratchBytesWritten = sprintf(scratchBuffer, "%d", red);
            }

            strcpy(&ppmData[bytesWritten], scratchBuffer);
            bytesWritten += scratchBytesWritten;
            lineLength += scratchBytesWritten;

            if (lineLength + scratchBytesWritten + 1 >= 70)
            {
                ppmData[bytesWritten++] = '\n';
                lineLength = 0;
            }

            ////////////////////////////////////////
            //               Green
            ////////////////////////////////////////

            if (lineLength > 0)
            {
                scratchBytesWritten = sprintf(scratchBuffer, " %d", green);
            }
            else
            {
                scratchBytesWritten = sprintf(scratchBuffer, "%d", green);
            }

            strcpy(&ppmData[bytesWritten], scratchBuffer);
            bytesWritten += scratchBytesWritten;
            lineLength += scratchBytesWritten;

            if (lineLength + scratchBytesWritten + 1 >= 70)
            {
                ppmData[bytesWritten++] = '\n';
                lineLength = 0;
            }

            ////////////////////////////////////////
            //               Blue
            ////////////////////////////////////////

            if (lineLength > 0)
            {
                scratchBytesWritten = sprintf(scratchBuffer, " %d", blue);
            }
            else
            {
                scratchBytesWritten = sprintf(scratchBuffer, "%d", blue);
            }

            strcpy(&ppmData[bytesWritten], scratchBuffer);
            bytesWritten += scratchBytesWritten;
            lineLength += scratchBytesWritten;

            if (lineLength + scratchBytesWritten + 1 >= 70 && x < (canvas.width - 1))
            {
                ppmData[bytesWritten++] = '\n';
                lineLength = 0;
            }
        }

        ppmData[bytesWritten++] = '\n';
    }

    ppmData[bytesWritten] = '\0';
    bytesWritten += 1;
    ppmData = realloc(ppmData, bytesWritten);

    return ppmData;
}

void WritePPM(Canvas canvas, const char *fileName)
{
    // Build file name with extension.
    const char *fileExtension = ".ppm";
    const size_t fileNameLength = strlen(fileName);
    const size_t fileExtensionLength = strlen(fileExtension);
    char *fullFileName = malloc(fileNameLength + fileExtensionLength + 1);
    strcpy(fullFileName, fileName);
    strcpy(&fullFileName[fileNameLength], fileExtension);

    DebugLog("PPM file name: %s.", fullFileName);

    // Create file.
    FILE *fp = fopen(fullFileName, "w");

    char *ppmData = CanvasToPPM(canvas);

    fprintf(fp, ppmData);

    // Cleanup.
    fclose(fp);
    free(ppmData);
    free(fullFileName);
}

////////////////////////////////////////////////////////////////////////////////
//                                  Tests
////////////////////////////////////////////////////////////////////////////////

#include "./unit_test.h"

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
    char *expectedPpm =
        "P3\n"
        "5 3\n"
        "255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
    char *ppmData = CanvasToPPM(c);
    AssertTrue(strcmp(ppmData, expectedPpm) == 0);
    free(ppmData);
    FreeCanvasMemory(c);

    c = CreateCanvas(10, 2);
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 10; x++)
            SetPixel(&c, x, y, (Color){ 1.0f, 0.8f, 0.6f });
    expectedPpm =
        "P3\n"
        "10 2\n"
        "255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
    ppmData = CanvasToPPM(c);
    AssertTrue(strcmp(ppmData, expectedPpm) == 0);
    free(ppmData);
    FreeCanvasMemory(c);

    c = CreateCanvas(20, 2);
    expectedPpm =
        "P3\n"
        "20 2\n"
        "255\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n";
    ppmData = CanvasToPPM(c);
    AssertTrue(strcmp(ppmData, expectedPpm) == 0);
    free(ppmData);
    FreeCanvasMemory(c);
}

void AddCanvasTests(void)
{
    AddUnitTest(TestCreateCanvas);
    AddUnitTest(TestGetPixel);
    AddUnitTest(TestSetPixel);
    AddUnitTest(TestCanvasToPPM);
}
