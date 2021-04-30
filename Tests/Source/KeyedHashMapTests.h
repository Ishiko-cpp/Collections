/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_TESTS_KEYEDHASHMAPTESTS_H_
#define _ISHIKO_COLLECTIONS_TESTS_KEYEDHASHMAPTESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class KeyedHashMapTests : public Ishiko::Tests::TestSequence
{
public:
    KeyedHashMapTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
