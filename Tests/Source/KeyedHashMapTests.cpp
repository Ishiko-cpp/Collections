/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#include "KeyedHashMapTests.h"
#include "Ishiko/Collections/KeyedHashMap.h"

using namespace Ishiko::Collections;
using namespace Ishiko::Tests;

KeyedHashMapTests::KeyedHashMapTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "KeyedHashMap tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void KeyedHashMapTests::ConstructorTest1(Test& test)
{
}
