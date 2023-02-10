#include "TraceLog.h"
#include "UnitTest.h"
#include "Math.h"
#include "Vector.h"
#include "Matrix.h"
#include "Canvas.h"

#include <stdio.h>

static void RunAllUnitTests();
static void RunRayTracer();

int main()
{
#ifdef RUN_UNIT_TESTS
    RunAllUnitTests();
#endif

#ifdef RUN_RAY_TRACER
    RunRayTracer();
#endif

    return 0;
}

static void RunAllUnitTests()
{
    AddMathTests();
    AddVectorTests();
    AddMatrixTests();
    AddColorTests();
    AddCanvasTests();
    RunUnitTests();
}

typedef struct Projectile Projectile;
typedef struct Environment Environment;

struct Projectile
{
    Vector3 position;
    Vector3 velocity;
};

struct Environment
{
    Vector3 gravity;
    Vector3 wind;
};

static Projectile Tick(Environment environment, Projectile projectile)
{
    projectile.position = Vector3Add(projectile.position, projectile.velocity);
    projectile.velocity = Vector3Add(Vector3Add(projectile.velocity, environment.gravity), environment.wind);
    return projectile;
}

static void RunCannonSim()
{
    SetTraceLogLevel(LogLevel_Debug);

    Projectile projectile = {
        .position = (Vector3){ 0.0f, 1.0f, 0.0f },
        .velocity = Vector3MulScalar(Vector3Normalize((Vector3){ 1.0f, 1.8f, 0.0f }), 11.25f),
    };

    Environment environment = {
        .gravity = (Vector3){ 0.0f, -0.1f, 0.0f },
        .wind = (Vector3){ -0.01f, 0.0f, 0.0f },
    };

    Canvas canvas = CreateCanvas(900, 550);

    InfoLog("Running cannon simulation.");

    DebugLog("Projectile position: (%.2lf, %.2lf, %.2lf)", projectile.position.x, projectile.position.y, projectile.position.z);

    const Color pixelColor = { 1.0f, 0.0f, 0.0f };

    while (projectile.position.y > 0.0f)
    {
        SetPixel(&canvas, (int)projectile.position.x, canvas.height - (int)projectile.position.y, pixelColor);

        projectile = Tick(environment, projectile);

        DebugLog("Projectile position: (%.2lf, %.2lf, %.2lf)", projectile.position.x, projectile.position.y, projectile.position.z);
    }

    InfoLog("Writing PPM file.");

    const char *ppmFileName = "canvas";
    WritePPM(canvas, ppmFileName);

    InfoLog("PPM file saved: %s.ppm.", ppmFileName);

    // Cleanup.
    FreeCanvasMemory(canvas);
}

static void RunRayTracer()
{
    RunCannonSim();
}
