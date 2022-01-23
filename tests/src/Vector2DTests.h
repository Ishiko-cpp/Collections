/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_TESTS_VECTOR2DTESTS_H_
#define _ISHIKO_COLLECTIONS_TESTS_VECTOR2DTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class Vector2DTests : public Ishiko::Tests::TestSequence
{
public:
    Vector2DTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void GetTest1(Ishiko::Tests::Test& test);
    static void GetTest2(Ishiko::Tests::Test& test);
};

#endif
