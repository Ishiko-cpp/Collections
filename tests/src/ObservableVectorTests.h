/*
    Copyright (c) 2018-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_TESTS_OBSERVABLEVECTORTESTS_H_
#define _ISHIKO_COLLECTIONS_TESTS_OBSERVABLEVECTORTESTS_H_

#include "Ishiko/Collections/ObservableVector.h"
#include <Ishiko/Tests/Core.h>

class ObservableVectorTests : public Ishiko::Tests::TestSequence
{
public:
    ObservableVectorTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
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
