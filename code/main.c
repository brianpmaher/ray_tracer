#include <stdio.h>

#include "./math.h"
#include "./unit_test.h"
#include "./tuple.h"
#include "./trace_log.h"

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
    AddTupleTests();
    RunUnitTests();
}

typedef struct Projectile {
    Point position;
    Vector velocity;
} Projectile;

typedef struct Environment {
    Vector gravity;
    Vector wind;
} Environment;

static Projectile Tick(Environment environment, Projectile projectile)
{
    projectile.position = Add(projectile.position, projectile.velocity);
    projectile.velocity = Add(Add(projectile.velocity, environment.gravity), environment.wind);
    return projectile;
}

static void RunCannonSim(void)
{
    Projectile projectile = {
        .position = CreatePoint(0.0f, 1.0f, 0.0f),
        .velocity = Normalize(CreateVector(1.0f, 1.0f, 0.0f)),
    };

    Environment environment = {
        .gravity = CreateVector(0.0f, -0.1f, 0.0f),
        .wind = CreateVector(-0.01f, 0.0f, 0.0f),
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
