#include <stdlib.h>

#include "./canvas.h"
#include "./unit_test.h"

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

Test(CreateCanvas,
{
    Canvas canvas = CreateCanvas(10, 20);
    AssertTrue(canvas.width == 10);
    AssertTrue(canvas.height == 20);

    for (int i = 0; i < canvas.width * canvas.height; i++)
        AssertTrue(IsEqual(canvas.pixels[i], Black()));

    FreeCanvasMemory(canvas);
})

void AddCanvasTests(void)
{
    AddUnitTest(TestCreateCanvas);
}
