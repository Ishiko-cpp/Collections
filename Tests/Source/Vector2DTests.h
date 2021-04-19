/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_TESTS_VECTOR2DTESTS_H_
#define _ISHIKO_COLLECTIONS_TESTS_VECTOR2DTESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class Vector2DTests : public Ishiko::Tests::TestSequence
{
public:
    Vector2DTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
