/*
    Copyright (c) 2018 Xavier Leclercq

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

#ifndef _ISHIKO_COLLECTIONS_OBSERVABLEVECTOR_H_
#define _ISHIKO_COLLECTIONS_OBSERVABLEVECTOR_H_

#include <vector>
#include <memory>

namespace Ishiko
{
namespace Collections
{

template<class T>
class ObservableVector
{
public:
    class Observer
    {
    public:
        virtual void onElementAdded(size_t pos, const T& value);
    };

    class Observers
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notifyElementAdded(size_t pos, const T& value);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    T& back();
    const T& back() const;

    size_t size() const noexcept;

    void pushBack(const T& value);
    void pushBack(T&& value);

    Observers& observers();

private:
    std::vector<T> m_vector;
    Observers m_observers;
};

}
}

template<class T>
void Ishiko::Collections::ObservableVector<T>::Observer::onElementAdded(size_t pos, const T& value)
{
}

template<class T>
void Ishiko::Collections::ObservableVector<T>::Observers::add(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<ObservableVector<T>::Observer>, size_t>& o)
        {
            return (o.first.lock() == observer);
        }
    );
    if (it != m_observers.end())
    {
        ++it->second;
    }
    else
    {
        m_observers.push_back(std::pair<std::weak_ptr<Observer>, size_t>(observer, 1));
    }
}

template<class T>
void Ishiko::Collections::ObservableVector<T>::Observers::remove(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<ObservableVector<T>::Observer>, size_t>& o)
        {
            return (o.first.lock() == observer);
        }
    );
    if (it != m_observers.end())
    {
        --it->second;
        if (it->second == 0)
        {
            m_observers.erase(it);
        }
    }
}

template<class T>
void Ishiko::Collections::ObservableVector<T>::Observers::notifyElementAdded(size_t pos, const T& value)
{
    for (std::pair<std::weak_ptr<ObservableVector<T>::Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<ObservableVector<T>::Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onElementAdded(pos, value);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

template<class T>
void Ishiko::Collections::ObservableVector<T>::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<ObservableVector<T>::Observer>, size_t>& o)
        {
            return o.first.expired();
        }
    );
    m_observers.erase(it, m_observers.end());
}

template<class T>
T& Ishiko::Collections::ObservableVector<T>::operator[](size_t pos)
{
    return m_vector[pos];
}

template<class T>
const T& Ishiko::Collections::ObservableVector<T>::operator[](size_t pos) const
{
    return m_vector[pos];
}

template<class T>
size_t Ishiko::Collections::ObservableVector<T>::size() const noexcept
{
    return m_vector.size();
}

template<class T>
T& Ishiko::Collections::ObservableVector<T>::back()
{
    return m_vector.back();
}

template<class T>
const T& Ishiko::Collections::ObservableVector<T>::back() const
{
    return m_vector.back();
}

template<class T>
void Ishiko::Collections::ObservableVector<T>::pushBack(const T& value)
{
    size_t pos = m_vector.size();
    m_vector.push_back(value);
    m_observers.notifyElementAdded(pos, value);
}

template<class T>
void Ishiko::Collections::ObservableVector<T>::pushBack(T&& value)
{
    size_t pos = m_vector.size();
    m_vector.push_back(value);
    m_observers.notifyElementAdded(pos, value);
}

template<class T>
typename Ishiko::Collections::ObservableVector<T>::Observers& Ishiko::Collections::ObservableVector<T>::observers()
{
    return m_observers;
}

#endif
