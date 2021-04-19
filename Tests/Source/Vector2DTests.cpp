/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#include "Vector2DTests.h"
#include "Ishiko/Collections/Vector2D.h"

using namespace Ishiko::Collections;
using namespace Ishiko::Tests;

Vector2DTests::Vector2DTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Vector2D tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void Vector2DTests::ConstructorTest1(Test& test)
{
    Vector2D<int> vector;

    ISHTF_FAIL_IF_NEQ(vector.size(), 0);
    ISHTF_PASS();
}
