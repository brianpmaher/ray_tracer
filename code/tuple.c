#include <stdbool.h>

#include "./tuple.h"
#include "./unit_test.h"

Test(TupleIsEqual,
{
    Tuple a = { 4.3f, -4.2f, 3.1f, 1.0f };
    Tuple b = { 4.3f, -4.2f, 3.1f, 1.0f };
    AssertTrue(TupleIsEqual(a, b));

    b = (Tuple){ 3.3f, -4.2f, 3.1f, 1.0f };
    AssertFalse(TupleIsEqual(a, b));

    b = (Tuple){ 4.3f, -5.2f, 3.1f, 1.0f };
    AssertFalse(TupleIsEqual(a, b));

    b = (Tuple){ 4.3f, -4.2f, 3.5f, 1.0f };
    AssertFalse(TupleIsEqual(a, b));

    b = (Tuple){ 4.3f, -4.2f, 3.1f, 0.0f };
    AssertFalse(TupleIsEqual(a, b));
})

Test(TupleIsPoint,
{
    Tuple a = { 4.3f, -4.2f, 3.1f, 1.0f };
    AssertTrue(TupleIsPoint(a));

    a = (Tuple){ 4.3f, -4.2f, 3.1f, 0.0f };
    AssertFalse(TupleIsPoint(a));
})

Test(TupleIsVector,
{
    Tuple a = { 4.3f, -4.2f, 3.1f, 0.0f };
    AssertTrue(TupleIsVector(a));

    a = (Tuple){ 4.3f, -4.2f, 3.1f, 1.0f };
    AssertFalse(TupleIsVector(a));
})

Test(Point,
{
    Tuple a = Point(4.0f, -4.0f, 3.0f);
    AssertTrue(TupleIsPoint(a));

    Tuple b = { 4.0f, -4.0f, 3.0f, TUPLE_POINT_W };
    AssertTrue(TupleIsEqual(a, b));
})

Test(Vector,
{
    Tuple a = Vector(4.0f, -4.0f, 3.0f);
    AssertTrue(TupleIsVector(a));

    Tuple b = { 4.0f, -4.0f, 3.0f, TUPLE_VECTOR_W };
    AssertTrue(TupleIsEqual(a, b));
})

Test(TupleAdd,
{
    Tuple a = { 3.0f, -2.0f, 5.0f, 1.0f };
    Tuple b = { -2.0f, 3.0f, 1.0f, 0.0f };
    AssertTrue(TupleIsEqual(TupleAdd(a, b), (Tuple){ 1.0f, 1.0f, 6.0f, 1.0f }));
})

Test(TupleSub,
{
    Tuple a = Point(3.0f, 2.0f, 1.0f);
    Tuple b = Point(5.0f, 6.0f, 7.0f);
    AssertTrue(TupleIsEqual(TupleSub(a, b), Vector(-2.0f, -4.0f, -6.0f)));
})

void AddTupleTests(void)
{
    AddUnitTest(TestTupleIsEqual);
    AddUnitTest(TestTupleIsPoint);
    AddUnitTest(TestTupleIsVector);
    AddUnitTest(TestPoint);
    AddUnitTest(TestVector);
    AddUnitTest(TestTupleAdd);
    AddUnitTest(TestTupleSub);
}
