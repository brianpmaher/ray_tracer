#pragma once

#include <stdbool.h>

typedef struct Tuple {
    float x;
    float y;
    float z;
    float w;
} Tuple;

bool TupleIsEqual(Tuple a, Tuple b);

bool TupleIsPoint(Tuple a);

void AddTupleTests(void);
