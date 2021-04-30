/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#include "KeyedHashSetTests.h"
#include "Ishiko/Collections/KeyedHashSet.h"
#include <string>

using namespace Ishiko::Collections;
using namespace Ishiko::Tests;

KeyedHashSetTests::KeyedHashSetTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "KeyedHashSet tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void KeyedHashSetTests::ConstructorTest1(Test& test)
{
    KeyedHashSet<std::string> set;

    ISHTF_FAIL_IF_NEQ(set.size(), 0);
    ISHTF_PASS();
}
