/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#include "Vector2DTests.h"
#include "Ishiko/Collections/Vector2D.hpp"

using namespace Ishiko;
using namespace Ishiko::Collections;

Vector2DTests::Vector2DTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Vector2D tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("get test 1", GetTest1);
    append<HeapAllocationErrorsTest>("get test 2", GetTest2);
}

void Vector2DTests::ConstructorTest1(Test& test)
{
    Vector2D<int> vector(1, 2);

    ISHIKO_TEST_FAIL_IF_NEQ(vector.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.dimensions(), (std::pair<size_t, size_t>(1, 2)));
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 0), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 1), 0);
    ISHIKO_TEST_PASS();
}

void Vector2DTests::ConstructorTest2(Test& test)
{
    Vector2D<int> vector(3, 2);

    ISHIKO_TEST_FAIL_IF_NEQ(vector.size(), 6);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.dimensions(), (std::pair<size_t, size_t>(3, 2)));
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 0), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 1), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(1, 0), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(1, 1), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(2, 0), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(2, 1), 0);
    ISHIKO_TEST_PASS();
}

void Vector2DTests::GetTest1(Test& test)
{
    Vector2D<int> vector(1, 2);

    vector.get(0, 0) = 5;

    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 0), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 1), 0);
    ISHIKO_TEST_PASS();
}

void Vector2DTests::GetTest2(Test& test)
{
    Vector2D<int> vector(3, 2);

    vector.get(1, 0) = 5;
    vector.get(2, 1) = 6;

    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 0), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(0, 1), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(1, 0), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(1, 1), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(2, 0), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(vector.get(2, 1), 6);
    ISHIKO_TEST_PASS();
}
