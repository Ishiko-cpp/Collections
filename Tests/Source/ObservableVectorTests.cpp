/*
    Copyright (c) 2018-2020 Xavier Leclercq

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

#include "ObservableVectorTests.h"

using namespace Ishiko::Tests;

ObservableVectorTests::ObservableVectorTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ObservableVector tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<HeapAllocationErrorsTest>("pushBack test 1", PushBackTest1);
    append<HeapAllocationErrorsTest>("pushBack test 2", PushBackTest2);
    append<HeapAllocationErrorsTest>("pushBack test 3", PushBackTest3);
    append<HeapAllocationErrorsTest>("pushBack test 4", PushBackTest4);
    append<HeapAllocationErrorsTest>("pushBack test 5", PushBackTest5);
    append<HeapAllocationErrorsTest>("pushBack test 6", PushBackTest6);
    append<HeapAllocationErrorsTest>("erase test 1", EraseTest1);
    append<HeapAllocationErrorsTest>("erase test 2", EraseTest2);
    append<HeapAllocationErrorsTest>("erase test 3", EraseTest3);
    append<HeapAllocationErrorsTest>("erase test 4", EraseTest4);
    append<HeapAllocationErrorsTest>("erase test 5", EraseTest5);
    append<HeapAllocationErrorsTest>("erase test 6", EraseTest6);
    append<HeapAllocationErrorsTest>("Two observers test 1", TwoObserversTest1);
    append<HeapAllocationErrorsTest>("Two observers test 2", TwoObserversTest2);
    append<HeapAllocationErrorsTest>("The same observer twice test 1", TheSameObserverTwiceTest1);
    append<HeapAllocationErrorsTest>("The same observer twice test 2", TheSameObserverTwiceTest2);
    append<HeapAllocationErrorsTest>("Observer removal test 1", ObserverRemovalTest1);
    append<HeapAllocationErrorsTest>("Observer removal test 2", ObserverRemovalTest2);
    append<HeapAllocationErrorsTest>("Observer removal test 3", ObserverRemovalTest3);
    append<HeapAllocationErrorsTest>("Observer removal test 4", ObserverRemovalTest4);
    append<HeapAllocationErrorsTest>("Observer removal test 5", ObserverRemovalTest5);
    append<HeapAllocationErrorsTest>("Observer removal test 6", ObserverRemovalTest6);
    append<HeapAllocationErrorsTest>("Observer deletion test 1", ObserverDeletionTest1);
    append<HeapAllocationErrorsTest>("Observer deletion test 2", ObserverDeletionTest2);
    append<HeapAllocationErrorsTest>("Two vectors sharing an observer test 1", TwoVectorsTest1);
    append<HeapAllocationErrorsTest>("Two vectors sharing an observer test 2", TwoVectorsTest2);
}

void ObservableVectorTests::CreationTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    ISHTF_FAIL_IF_NEQ(vector.size(), 0);
    ISHTF_PASS();
}

void ObservableVectorTests::CreationTest2(Test& test)
{
    DerivedIntVector vector;
    
    ISHTF_FAIL_IF_NEQ(vector.size(), 0);
    ISHTF_PASS();
}

void ObservableVectorTests::PushBackTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;
    vector.pushBack(123);

    ISHTF_FAIL_IF_NEQ(vector.size(), 1);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_PASS();
}

void ObservableVectorTests::PushBackTest2(Test& test)
{
    DerivedIntVector vector;
    vector.pushBack(123);
    
    ISHTF_FAIL_IF_NEQ(vector.size(), 1);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_PASS();
}

void ObservableVectorTests::PushBackTest3(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);

    ISHTF_FAIL_IF_NEQ(vector.size(), 1);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::PushBackTest4(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);
    
    ISHTF_FAIL_IF_NEQ(vector.size(), 1);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::PushBackTest5(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_PASS();
}

void ObservableVectorTests::PushBackTest6(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);
    
    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_PASS();
}

void ObservableVectorTests::EraseTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;
    vector.pushBack(123);
    vector.erase(vector.begin());

    ISHTF_FAIL_IF_NEQ(vector.size(), 0);
    ISHTF_PASS();
}

void ObservableVectorTests::EraseTest2(Test& test)
{
    DerivedIntVector vector;
    vector.pushBack(123);
    vector.erase(vector.begin());
    
    ISHTF_FAIL_IF_NEQ(vector.size(), 0);
    ISHTF_PASS();
}

void ObservableVectorTests::EraseTest3(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.erase(vector.begin());

    ISHTF_FAIL_IF_NEQ(vector.size(), 0);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions.size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions[&vector][0],
        (std::tuple<size_t, size_t, std::vector<int>>(0, 1, { 123 })));
    ISHTF_PASS();
}

void ObservableVectorTests::EraseTest4(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.erase(vector.begin());

    ISHTF_FAIL_IF_NEQ(vector.size(), 0);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions.size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions[&vector][0],
        (std::tuple<size_t, size_t, std::vector<int>>(0, 1, { 123 })));
    ISHTF_PASS();
}

void ObservableVectorTests::EraseTest5(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);
    vector.erase(vector.begin() + 1, vector.end());

    ISHTF_FAIL_IF_NEQ(vector.size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions.size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions[&vector][0],
        (std::tuple<size_t, size_t, std::vector<int>>(1, 3, { 456, 789 })));
    ISHTF_PASS();
}

void ObservableVectorTests::EraseTest6(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);
    vector.erase(vector.begin() + 1, vector.end());

    ISHTF_FAIL_IF_NEQ(vector.size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions.size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_deletions[&vector][0],
        (std::tuple<size_t, size_t, std::vector<int>>(1, 3, { 456, 789 })));
    ISHTF_PASS();
}

void ObservableVectorTests::TwoObserversTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer1 = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer1);
    std::shared_ptr<IntVectorObserver> observer2 = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer2);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_PASS();
}

void ObservableVectorTests::TwoObserversTest2(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer1 = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer1);
    std::shared_ptr<DerivedIntVectorObserver> observer2 = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer2);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_PASS();
}

void ObservableVectorTests::TheSameObserverTwiceTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_PASS();
}

void ObservableVectorTests::TheSameObserverTwiceTest2(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);
    vector.observers().add(observer);

    vector.pushBack(123);
    vector.pushBack(456);
    vector.pushBack(789);
    
    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverRemovalTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer1 = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer1);
    std::shared_ptr<IntVectorObserver> observer2 = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer2);

    vector.pushBack(123);

    vector.observers().remove(observer2);

    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverRemovalTest2(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer1 = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer1);
    std::shared_ptr<DerivedIntVectorObserver> observer2 = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer2);

    vector.pushBack(123);

    vector.observers().remove(observer2);

    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector].size(), 3);
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_FAIL_IF_NEQ(observer1->m_additions[&vector][2], (std::pair<size_t, int>(2, 789)));
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer2->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverRemovalTest3(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);
    vector.observers().add(observer);

    vector.pushBack(123);

    vector.observers().remove(observer);

    vector.pushBack(456);

    vector.observers().remove(observer);

    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 2);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverRemovalTest4(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);
    vector.observers().add(observer);

    vector.pushBack(123);

    vector.observers().remove(observer);

    vector.pushBack(456);

    vector.observers().remove(observer);

    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 2);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][1], (std::pair<size_t, int>(1, 456)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverRemovalTest5(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);
    
    vector.pushBack(123);

    vector.observers().remove(observer);
    vector.observers().remove(observer);

    vector.pushBack(456);

    ISHTF_FAIL_IF_NEQ(vector.size(), 2);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverRemovalTest6(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);

    vector.observers().remove(observer);
    vector.observers().remove(observer);

    vector.pushBack(456);

    ISHTF_FAIL_IF_NEQ(vector.size(), 2);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverDeletionTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);

    std::vector<std::pair<size_t, int>> additions(observer->m_additions[&vector]);

    observer.reset();

    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(additions.size(), 1);
    ISHTF_FAIL_IF_NEQ(additions[0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::ObserverDeletionTest2(Test& test)
{
    DerivedIntVector vector;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector.observers().add(observer);

    vector.pushBack(123);

    std::vector<std::pair<size_t, int>> additions(observer->m_additions[&vector]);

    observer.reset();

    vector.pushBack(456);
    vector.pushBack(789);

    ISHTF_FAIL_IF_NEQ(vector.size(), 3);
    ISHTF_FAIL_IF_NEQ(vector[0], 123);
    ISHTF_FAIL_IF_NEQ(vector[1], 456);
    ISHTF_FAIL_IF_NEQ(vector[2], 789);
    ISHTF_FAIL_IF_NEQ(additions.size(), 1);
    ISHTF_FAIL_IF_NEQ(additions[0], (std::pair<size_t, int>(0, 123)));
    ISHTF_PASS();
}

void ObservableVectorTests::TwoVectorsTest1(Test& test)
{
    Ishiko::Collections::ObservableVector<int> vector1;
    Ishiko::Collections::ObservableVector<int> vector2;

    std::shared_ptr<IntVectorObserver> observer = std::make_shared<IntVectorObserver>();
    vector1.observers().add(observer);
    vector2.observers().add(observer);

    vector1.pushBack(123);
    vector2.pushBack(456);

    ISHTF_FAIL_IF_NEQ(vector1.size(), 1);
    ISHTF_FAIL_IF_NEQ(vector1[0], 123);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector1].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector1][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector2].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector2][0], (std::pair<size_t, int>(0, 456)));
    ISHTF_PASS();
}

void ObservableVectorTests::TwoVectorsTest2(Test& test)
{
    DerivedIntVector vector1;
    DerivedIntVector vector2;

    std::shared_ptr<DerivedIntVectorObserver> observer = std::make_shared<DerivedIntVectorObserver>();
    vector1.observers().add(observer);
    vector2.observers().add(observer);

    vector1.pushBack(123);
    vector2.pushBack(456);

    ISHTF_FAIL_IF_NEQ(vector1.size(), 1);
    ISHTF_FAIL_IF_NEQ(vector1[0], 123);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector1].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector1][0], (std::pair<size_t, int>(0, 123)));
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector2].size(), 1);
    ISHTF_FAIL_IF_NEQ(observer->m_additions[&vector2][0], (std::pair<size_t, int>(0, 456)));
    ISHTF_PASS();
}

void IntVectorObserver::onElementAdded(const Ishiko::Collections::ObservableVector<int>& source, size_t pos,
    const int& value)
{
    m_additions[(void*)&source].push_back(std::pair<size_t, int>(pos, value));
}

void IntVectorObserver::onElementsRemoved(const Ishiko::Collections::ObservableVector<int>& source, size_t first,
    size_t last, const std::vector<int>& removedElements)
{
    m_deletions[(void*)&source].push_back(std::tuple<size_t, size_t, std::vector<int>>(first, last, removedElements));
}

void DerivedIntVectorObserver::onElementAdded(const DerivedIntVector& source, size_t pos,
    const int& value)
{
    if (source.sm_derived)
    {
        m_additions[(void*)&source].push_back(std::pair<size_t, int>(pos, value));
    }
}

void DerivedIntVectorObserver::onElementsRemoved(const DerivedIntVector& source, size_t first,
    size_t last, const std::vector<int>& removedElements)
{
    if (source.sm_derived)
    {
        m_deletions[(void*)&source].push_back(std::tuple<size_t, size_t, std::vector<int>>(first, last, removedElements));
    }
}
