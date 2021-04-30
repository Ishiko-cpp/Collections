/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_TESTS_KEYEDHASHSETTESTS_H_
#define _ISHIKO_COLLECTIONS_TESTS_KEYEDHASHSETTESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class KeyedHashSetTests : public Ishiko::Tests::TestSequence
{
public:
    KeyedHashSetTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
