#include <stdbool.h>

#include "./tuple.h"
#include "./math.h"
#include "./unit_test.h"

#define TUPLE_POINT_W 1.0f
#define TUPLE_VECTOR_W 0.0f

bool TupleIsPoint(Tuple a)
{
    return IsEqual(a.w, TUPLE_POINT_W);
}

bool TupleIsVector(Tuple a)
{
    return IsEqual(a.w, TUPLE_VECTOR_W);
}

bool TupleIsEqual(Tuple a, Tuple b)
{
    return IsEqual(a.x, b.x) && IsEqual(a.y, b.y) && IsEqual(a.z, b.z) && IsEqual(a.w, b.w);
}

static bool TestTupleIsEqual(void)
{
    bool testResult = true;

    Tuple a = { 4.3f, -4.2f, 3.1f, 1.0f };
    Tuple b = { 4.3f, -4.2f, 3.1f, 1.0f };

    testResult &= AssertTrue(TupleIsEqual(a, b));

    b = (Tuple){ 3.3f, -4.2f, 3.1f, 1.0f };

    testResult &= AssertFalse(TupleIsEqual(a, b));

    b = (Tuple){ 4.3f, -5.2f, 3.1f, 1.0f };

    testResult &= AssertFalse(TupleIsEqual(a, b));

    b = (Tuple){ 4.3f, -4.2f, 3.5f, 1.0f };

    testResult &= AssertFalse(TupleIsEqual(a, b));

    b = (Tuple){ 4.3f, -4.2f, 3.1f, 0.0f };

    testResult &= AssertFalse(TupleIsEqual(a, b));

    return testResult;
}

static bool TestTupleIsPoint(void)
{
    bool testResult = true;

    Tuple a = { 4.3f, -4.2f, 3.1f, 1.0f };

    testResult &= AssertTrue(TupleIsPoint(a));
    testResult &= AssertFalse(TupleIsVector(a));

    return testResult;
}

void AddTupleTests(void)
{
    AddUnitTest(TestTupleIsEqual);
    AddUnitTest(TestTupleIsPoint);
}
