/*
    Copyright (c) 2018-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef _ISHIKO_COLLECTIONS_TESTS_OBSERVABLEVECTORTESTS_H_
#define _ISHIKO_COLLECTIONS_TESTS_OBSERVABLEVECTORTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"
#include "Ishiko/Collections/ObservableVector.h"

class ObservableVectorTests : public Ishiko::Tests::TestSequence
{
public:
    ObservableVectorTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void CreationTest2(Ishiko::Tests::Test& test);
    static void PushBackTest1(Ishiko::Tests::Test& test);
    static void PushBackTest2(Ishiko::Tests::Test& test);
    static void PushBackTest3(Ishiko::Tests::Test& test);
    static void PushBackTest4(Ishiko::Tests::Test& test);
    static void PushBackTest5(Ishiko::Tests::Test& test);
    static void PushBackTest6(Ishiko::Tests::Test& test);
    static void EraseTest1(Ishiko::Tests::Test& test);
    static void EraseTest2(Ishiko::Tests::Test& test);
    static void EraseTest3(Ishiko::Tests::Test& test);
    static void EraseTest4(Ishiko::Tests::Test& test);
    static void EraseTest5(Ishiko::Tests::Test& test);
    static void EraseTest6(Ishiko::Tests::Test& test);
    static void TwoObserversTest1(Ishiko::Tests::Test& test);
    static void TwoObserversTest2(Ishiko::Tests::Test& test);
    static void TheSameObserverTwiceTest1(Ishiko::Tests::Test& test);
    static void TheSameObserverTwiceTest2(Ishiko::Tests::Test& test);
    static void ObserverRemovalTest1(Ishiko::Tests::Test& test);
    static void ObserverRemovalTest2(Ishiko::Tests::Test& test);
    static void ObserverRemovalTest3(Ishiko::Tests::Test& test);
    static void ObserverRemovalTest4(Ishiko::Tests::Test& test);
    static void ObserverRemovalTest5(Ishiko::Tests::Test& test);
    static void ObserverRemovalTest6(Ishiko::Tests::Test& test);
    static void ObserverDeletionTest1(Ishiko::Tests::Test& test);
    static void ObserverDeletionTest2(Ishiko::Tests::Test& test);
    static void TwoVectorsTest1(Ishiko::Tests::Test& test);
    static void TwoVectorsTest2(Ishiko::Tests::Test& test);
};

class IntVectorObserver : public Ishiko::Collections::ObservableVector<int>::Observer
{
public:
    void onElementAdded(const Ishiko::Collections::ObservableVector<int>& source, size_t pos,
        const int& value) override;
    void onElementsRemoved(const Ishiko::Collections::ObservableVector<int>& source, size_t first,
        size_t last, const std::vector<int>& removedElements) override;

    std::map<void*, std::vector<std::pair<size_t, int>>> m_additions;
    std::map<void*, std::vector<std::tuple<size_t, size_t, std::vector<int>>>> m_deletions;
};

class DerivedIntVector : public Ishiko::Collections::ObservableVector<int, DerivedIntVector>
{
public:
    static const bool sm_derived = true;
};

class DerivedIntVectorObserver : public DerivedIntVector::Observer
{
public:
    void onElementAdded(const DerivedIntVector& source, size_t pos,
        const int& value) override;
    void onElementsRemoved(const DerivedIntVector& source, size_t first,
        size_t last, const std::vector<int>& removedElements) override;

    std::map<void*, std::vector<std::pair<size_t, int>>> m_additions;
    std::map<void*, std::vector<std::tuple<size_t, size_t, std::vector<int>>>> m_deletions;
};

#endif
