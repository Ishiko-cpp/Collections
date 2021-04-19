/*
    Copyright (c) 2018-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#include "Vector2DTests.h"
#include "ObservableVectorTests.h"
#include <Ishiko/TestFramework/TestFrameworkCore.h>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoCollections");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<Vector2DTests>();
    theTests.append<ObservableVectorTests>();

    return theTestHarness.run();
}
