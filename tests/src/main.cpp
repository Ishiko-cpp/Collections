/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#include "Vector2DTests.hpp"
#include "ObservableVectorTests.hpp"
#include <Ishiko/TestFramework/Core.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoCollections");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<Vector2DTests>();
    theTests.append<ObservableVectorTests>();

    return theTestHarness.run();
}
