#include <stdio.h>

#include "./math.h"
#include "./unit_test.h"
#include "./vector.h"
#include "./trace_log.h"
#include "./canvas.h"

static void RunAllUnitTests(void);
static void RunRayTracer(void);

int main(void)
{
#ifdef RUN_UNIT_TESTS
    RunAllUnitTests();
#endif

#ifdef RUN_RAY_TRACER
    RunRayTracer();
#endif

    return 0;
}

static void RunAllUnitTests(void)
{
    AddMathTests();
    AddVectorTests();
    AddColorTests();
    AddCanvasTests();
    RunUnitTests();
}

typedef struct Projectile {
    Vector3 position;
    Vector3 velocity;
} Projectile;

typedef struct Environment {
    Vector3 gravity;
    Vector3 wind;
} Environment;

static Projectile Tick(Environment environment, Projectile projectile)
{
    projectile.position = Vector3Add(projectile.position, projectile.velocity);
    projectile.velocity = Vector3Add(Vector3Add(projectile.velocity, environment.gravity), environment.wind);
    return projectile;
}

static void RunCannonSim(void)
{
    SetTraceLogLevel(LOG_DEBUG);

    Projectile projectile = {
        .position = (Vector3){ 0.0f, 1.0f, 0.0f },
        .velocity = Vector3Normalize(Vector3MulScalar((Vector3){ 1.0f, 1.8f, 0.0f }, 11.25f)),
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

static void RunRayTracer(void)
{
    RunCannonSim();
}
