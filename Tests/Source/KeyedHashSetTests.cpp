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
    append<HeapAllocationErrorsTest>("insert test 1", InsertTest1);
    append<HeapAllocationErrorsTest>("IteratorAdvance test 1", IteratorAdvanceTest1);
}

void KeyedHashSetTests::ConstructorTest1(Test& test)
{
    KeyedHashSet<std::string> set;

    ISHTF_FAIL_IF_NEQ(set.size(), 0);
    ISHTF_PASS();
}

void KeyedHashSetTests::InsertTest1(Test& test)
{
    KeyedHashSet<std::string> set;

    std::pair<KeyedHashSet<std::string>::iterator, bool> p = set.insert("a");
    
    ISHTF_FAIL_IF_NEQ(*p.first, "a");
    ISHTF_FAIL_IF_NOT(p.second);
    ISHTF_FAIL_IF_NEQ(set.size(), 1);
    ISHTF_PASS();
}

void KeyedHashSetTests::IteratorAdvanceTest1(Test& test)
{
    KeyedHashSet<std::string> set;

    std::pair<KeyedHashSet<std::string>::iterator, bool> p1 = set.insert("a");
    std::pair<KeyedHashSet<std::string>::iterator, bool> p2 = set.insert("b");

    std::advance(p1.first, 1);

    ISHTF_FAIL_IF_NEQ(p1.first, p2.first);
    ISHTF_PASS();
}
