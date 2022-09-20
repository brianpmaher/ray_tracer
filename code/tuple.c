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

Test(CreatePoint,
{
    Tuple a = CreatePoint(4.0f, -4.0f, 3.0f);
    AssertTrue(TupleIsPoint(a));

    Tuple b = { 4.0f, -4.0f, 3.0f, TUPLE_POINT_W };
    AssertTrue(TupleIsEqual(a, b));
})

Test(CreateVector,
{
    Tuple a = CreateVector(4.0f, -4.0f, 3.0f);
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
    Tuple a = CreatePoint(3.0f, 2.0f, 1.0f);
    Tuple b = CreatePoint(5.0f, 6.0f, 7.0f);
    AssertTrue(TupleIsEqual(TupleSub(a, b), CreateVector(-2.0f, -4.0f, -6.0f)));

    b = CreateVector(5.0f, 6.0f, 7.0f);
    AssertTrue(TupleIsEqual(TupleSub(a, b), CreatePoint(-2.0f, -4.0f, -6.0f)));

    a = CreateVector(3.0f, 2.0f, 1.0f);
    AssertTrue(TupleIsEqual(TupleSub(a, b), CreateVector(-2.0f, -4.0f, -6.0f)));

    a = VectorZero();
    b = CreateVector(1.0f, -2.0f, 3.0f);
    AssertTrue(TupleIsEqual(TupleSub(a, b), CreateVector(-1.0f, 2.0f, -3.0f)));
})

Test(PointZero,
{
    AssertTrue(TupleIsEqual(PointZero(), CreatePoint(0.0f, 0.0f, 0.0f)));
})

Test(VectorZero,
{
    AssertTrue(TupleIsEqual(VectorZero(), CreateVector(0.0f, 0.0f, 0.0f)));
})

Test(TupleNegate,
{
    Tuple a = { 1.0f, -2.0f, 3.0f, -4.0f };
    AssertTrue(TupleIsEqual(TupleNegate(a), (Tuple){ -1.0f, 2.0f, -3.0f, 4.0f }));
})

Test(TupleMulScalar,
{
    Tuple a = { 1.0f, -2.0f, 3.0f, -4.0f };
    float scalar = 3.5f;
    AssertTrue(TupleIsEqual(TupleMulScalar(a, scalar), (Tuple){ 3.5f, -7.0f, 10.5f, -14.0f }));

    scalar = 0.5f;
    AssertTrue(TupleIsEqual(TupleMulScalar(a, scalar), (Tuple){ 0.5f, -1.0f, 1.5f, -2.0f }));
})

Test(TupleDivScalar,
{
    Tuple a = { 1.0f, -2.0f, 3.0f, -4.0f };
    float scalar = 2;
    AssertTrue(TupleIsEqual(TupleDivScalar(a, scalar), (Tuple){ 0.5f, -1.0f, 1.5f, -2.0f }));
})

Test(VectorMagnitude,
{
    Tuple a = CreateVector(1.0f, 0.0f, 0.0f);
    AssertTrue(IsEqual(VectorMagnitude(a), 1.0f));

    a = CreateVector(0.0f, 1.0f, 0.0f);
    AssertTrue(IsEqual(VectorMagnitude(a), 1.0f));

    a = CreateVector(0.0f, 0.0f, 1.0f);
    AssertTrue(IsEqual(VectorMagnitude(a), 1.0f));

    a = CreateVector(1.0f, 2.0f, 3.0f);
    AssertTrue(IsEqual(VectorMagnitude(a), sqrtf(14)));

    a = CreateVector(-1.0f, -2.0f, -3.0f);
    AssertTrue(IsEqual(VectorMagnitude(a), sqrtf(14)));
})

Test(VectorNormalize,
{
    Tuple a = CreateVector(4.0f, 0.0f, 0.0f);
    AssertTrue(TupleIsEqual(VectorNormalize(a), CreateVector(1.0f, 0.0f, 0.0f)));

    a = CreateVector(1.0f, 2.0f, 3.0f);
    AssertTrue(TupleIsEqual(VectorNormalize(a), CreateVector(0.26726f, 0.53452f, 0.80178f)));

    AssertTrue(IsEqual(VectorMagnitude(VectorNormalize(a)), 1.0f));
})

Test(VectorDot,
{
    Tuple a = CreateVector(1.0f, 2.0f, 3.0f);
    Tuple b = CreateVector(2.0f, 3.0f, 4.0f);
    AssertTrue(IsEqual(VectorDot(a, b), 20.0f));
})

Test(VectorCross,
{
    Tuple a = CreateVector(1.0f, 2.0f, 3.0f);
    Tuple b = CreateVector(2.0f, 3.0f, 4.0f);
    AssertTrue(TupleIsEqual(VectorCross(a, b), CreateVector(-1.0f, 2.0f, -1.0f)));
    AssertTrue(TupleIsEqual(VectorCross(b, a), CreateVector(1.0f, -2.0f, 1.0f)));
})

void AddTupleTests(void)
{
    AddUnitTest(TestTupleIsEqual);
    AddUnitTest(TestTupleIsPoint);
    AddUnitTest(TestTupleIsVector);
    AddUnitTest(TestCreatePoint);
    AddUnitTest(TestCreateVector);
    AddUnitTest(TestTupleAdd);
    AddUnitTest(TestTupleSub);
    AddUnitTest(TestPointZero);
    AddUnitTest(TestVectorZero);
    AddUnitTest(TestTupleNegate);
    AddUnitTest(TestTupleMulScalar);
    AddUnitTest(TestTupleDivScalar);
    AddUnitTest(TestVectorMagnitude);
    AddUnitTest(TestVectorNormalize);
    AddUnitTest(TestVectorDot);
    AddUnitTest(TestVectorCross);
}
