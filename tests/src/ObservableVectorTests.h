/*
    Copyright (c) 2018-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_COLLECTIONS_TESTS_OBSERVABLEVECTORTESTS_H_
#define _ISHIKO_CPP_COLLECTIONS_TESTS_OBSERVABLEVECTORTESTS_H_

#include "Ishiko/Collections/ObservableVector.hpp"
#include <Ishiko/TestFramework/Core.hpp>

class ObservableVectorTests : public Ishiko::TestSequence
{
public:
    ObservableVectorTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void PushBackTest1(Ishiko::Test& test);
    static void PushBackTest2(Ishiko::Test& test);
    static void PushBackTest3(Ishiko::Test& test);
    static void PushBackTest4(Ishiko::Test& test);
    static void PushBackTest5(Ishiko::Test& test);
    static void PushBackTest6(Ishiko::Test& test);
    static void EraseTest1(Ishiko::Test& test);
    static void EraseTest2(Ishiko::Test& test);
    static void EraseTest3(Ishiko::Test& test);
    static void EraseTest4(Ishiko::Test& test);
    static void EraseTest5(Ishiko::Test& test);
    static void EraseTest6(Ishiko::Test& test);
    static void TwoObserversTest1(Ishiko::Test& test);
    static void TwoObserversTest2(Ishiko::Test& test);
    static void TheSameObserverTwiceTest1(Ishiko::Test& test);
    static void TheSameObserverTwiceTest2(Ishiko::Test& test);
    static void ObserverRemovalTest1(Ishiko::Test& test);
    static void ObserverRemovalTest2(Ishiko::Test& test);
    static void ObserverRemovalTest3(Ishiko::Test& test);
    static void ObserverRemovalTest4(Ishiko::Test& test);
    static void ObserverRemovalTest5(Ishiko::Test& test);
    static void ObserverRemovalTest6(Ishiko::Test& test);
    static void ObserverDeletionTest1(Ishiko::Test& test);
    static void ObserverDeletionTest2(Ishiko::Test& test);
    static void TwoVectorsTest1(Ishiko::Test& test);
    static void TwoVectorsTest2(Ishiko::Test& test);
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
