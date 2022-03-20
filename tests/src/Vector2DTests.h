/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_TESTS_VECTOR2DTESTS_H_
#define _ISHIKO_COLLECTIONS_TESTS_VECTOR2DTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class Vector2DTests : public Ishiko::TestSequence
{
public:
    Vector2DTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void GetTest1(Ishiko::Test& test);
    static void GetTest2(Ishiko::Test& test);
};

#endif
