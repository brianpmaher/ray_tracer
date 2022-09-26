#include <stdio.h>

#include "./math.h"
#include "./unit_test.h"
#include "./vector.h"
#include "./trace_log.h"
#include "./canvas.h"

static void RunAllUnitTests(void);
static void RunCannonSim(void);

int main(void)
{
#ifdef RUN_UNIT_TESTS
    RunAllUnitTests();
#endif

    RunCannonSim();

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
    Projectile projectile = {
        .position = (Vector3){ 0.0f, 1.0f, 0.0f },
        .velocity = Vector3Normalize((Vector3){ 1.0f, 1.0f, 0.0f }),
    };

    Environment environment = {
        .gravity = (Vector3){ 0.0f, -0.1f, 0.0f },
        .wind = (Vector3){ -0.01f, 0.0f, 0.0f },
    };

    InfoLog("Running cannon simulation.");
    InfoLog("Projectile position: (%.2lf, %.2lf, %.2lf)", projectile.position.x, projectile.position.y, projectile.position.z);
    int numTicks = 0;
    while (projectile.position.y > 0.0f)
    {
        projectile = Tick(environment, projectile); numTicks++;
        InfoLog("Projectile position: (%.2lf, %.2lf, %.2lf)", projectile.position.x, projectile.position.y, projectile.position.z);
    }
    InfoLog("Num ticks: %d", numTicks);
}
