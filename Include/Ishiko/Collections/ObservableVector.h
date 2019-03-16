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

#ifndef _ISHIKO_COLLECTIONS_OBSERVABLEVECTOR_H_
#define _ISHIKO_COLLECTIONS_OBSERVABLEVECTOR_H_

#include <vector>
#include <memory>

namespace Ishiko
{
namespace Collections
{

template<class T, class EventSource = void, class Allocator = std::allocator<T>>
class ObservableVector
{
public:
    class Observer
    {
    public:
        virtual ~Observer() = default;

        virtual void onElementAdded(const EventSource& source, size_t pos, const T& value);
        virtual void onElementsRemoved(const EventSource& source, size_t first, size_t last,
            const std::vector<T, Allocator>& removedElements);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notifyElementAdded(const EventSource& source, size_t pos, const T& value);
        void notifyElementsRemoved(const EventSource& source, size_t first, size_t last,
            const std::vector<T, Allocator>& removedElements);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    T& back();
    const T& back() const;

    typename std::vector<T, Allocator>::iterator begin() noexcept;
    typename std::vector<T, Allocator>::const_iterator begin() const noexcept;
    typename std::vector<T, Allocator>::iterator end() noexcept;
    typename std::vector<T, Allocator>::const_iterator end() const noexcept;

    size_t size() const noexcept;

    typename std::vector<T, Allocator>::iterator erase(typename std::vector<T, Allocator>::const_iterator pos);
    typename std::vector<T, Allocator>::iterator erase(typename std::vector<T, Allocator>::const_iterator first,
        typename std::vector<T, Allocator>::const_iterator last);
    void pushBack(const T& value);
    void pushBack(T&& value);

    Observers& observers();

private:
    std::vector<T, Allocator> m_vector;
    Observers m_observers;
};

template<class T, class Allocator>
class ObservableVector<T, void, Allocator>
{
public:
    class Observer
    {
    public:
        virtual ~Observer() = default;

        virtual void onElementAdded(const ObservableVector<T, void, Allocator>& source, size_t pos, const T& value);
        virtual void onElementsRemoved(const ObservableVector<T, void, Allocator>& source, size_t first, size_t last,
            const std::vector<T, Allocator>& removedElements);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notifyElementAdded(const ObservableVector<T, void, Allocator>& source, size_t pos, const T& value);
        void notifyElementsRemoved(const ObservableVector<T, void, Allocator>& source, size_t first, size_t last,
            const std::vector<T, Allocator>& removedElements);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;
    T& back();
    const T& back() const;

    typename std::vector<T, Allocator>::iterator begin() noexcept;
    typename std::vector<T, Allocator>::const_iterator begin() const noexcept;
    typename std::vector<T, Allocator>::iterator end() noexcept;
    typename std::vector<T, Allocator>::const_iterator end() const noexcept;

    size_t size() const noexcept;

    typename std::vector<T, Allocator>::iterator erase(typename std::vector<T, Allocator>::const_iterator pos);
    typename std::vector<T, Allocator>::iterator erase(typename std::vector<T, Allocator>::const_iterator first,
        typename std::vector<T, Allocator>::const_iterator last);
    void pushBack(const T& value);
    void pushBack(T&& value);

    Observers& observers();

private:
    std::vector<T, Allocator> m_vector;
    Observers m_observers;
};

}
}

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observer::onElementAdded(
    const EventSource& source, size_t pos, const T& value)
{
}

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observer::onElementsRemoved(
    const EventSource& source, size_t first, size_t last, const std::vector<T, Allocator>& removedElements)
{
}

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observers::add(
    std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<ObservableVector<T, EventSource, Allocator>::Observer>, size_t>& o)
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

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observers::remove(
    std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<ObservableVector<T, EventSource, Allocator>::Observer>, size_t>& o)
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

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observers::notifyElementAdded(
    const EventSource& source, size_t pos, const T& value)
{
    for (std::pair<std::weak_ptr<ObservableVector<T, EventSource, Allocator>::Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<ObservableVector<T, EventSource, Allocator>::Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onElementAdded(source, pos, value);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observers::notifyElementsRemoved(
    const EventSource& source, size_t first, size_t last,
    const std::vector<T, Allocator>& removedElements)
{
    for (std::pair<std::weak_ptr<ObservableVector<T, EventSource, Allocator>::Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<ObservableVector<T, EventSource, Allocator>::Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onElementsRemoved(source, first, last, removedElements);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<ObservableVector<T, EventSource, Allocator>::Observer>, size_t>& o)
        {
            return o.first.expired();
        }
    );
    m_observers.erase(it, m_observers.end());
}

template<class T, class EventSource, class Allocator>
T& Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::operator[](size_t pos)
{
    return m_vector[pos];
}

template<class T, class EventSource, class Allocator>
const T& Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::operator[](size_t pos) const
{
    return m_vector[pos];
}

template<class T, class EventSource, class Allocator>
T& Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::back()
{
    return m_vector.back();
}

template<class T, class EventSource, class Allocator>
const T& Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::back() const
{
    return m_vector.back();
}

template<class T, class EventSource, class Allocator>
typename std::vector<T, Allocator>::iterator
    Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::begin() noexcept
{
    return m_vector.begin();
}

template<class T, class EventSource, class Allocator>
typename std::vector<T, Allocator>::const_iterator
    Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::begin() const noexcept
{
    return m_vector.begin();
}

template<class T, class EventSource, class Allocator>
typename std::vector<T, Allocator>::iterator
    Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::end() noexcept
{
    return m_vector.end();
}

template<class T, class EventSource, class Allocator>
typename std::vector<T, Allocator>::const_iterator
    Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::end() const noexcept
{
    return m_vector.end();
}

template<class T, class EventSource, class Allocator>
size_t Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::size() const noexcept
{
    return m_vector.size();
}

template<class T, class EventSource, class Allocator>
typename std::vector<T, Allocator>::iterator Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::erase(
    typename std::vector<T, Allocator>::const_iterator pos)
{
    size_t firstPos = pos - m_vector.cbegin();
    std::vector<T, Allocator> removedElements;
    removedElements.push_back(*pos);
    typename std::vector<T, Allocator>::iterator result =  m_vector.erase(pos);
    m_observers.notifyElementsRemoved(*(static_cast<EventSource*>(this)), firstPos, firstPos + 1, removedElements);
    return result;
}

template<class T, class EventSource, class Allocator>
typename std::vector<T, Allocator>::iterator Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::erase(
    typename std::vector<T, Allocator>::const_iterator first, typename std::vector<T, Allocator>::const_iterator last)
{
    size_t firstPos = first - m_vector.cbegin();
    size_t lastPos = last - m_vector.cbegin();
    std::vector<T, Allocator> removedElements;
    removedElements.insert(removedElements.end(), first, last);
    typename std::vector<T, Allocator>::iterator result = m_vector.erase(first, last);
    m_observers.notifyElementsRemoved(*(static_cast<EventSource*>(this)), firstPos, lastPos, removedElements);
    return result;
}

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::pushBack(const T& value)
{
    size_t pos = m_vector.size();
    m_vector.push_back(value);
    m_observers.notifyElementAdded(*(static_cast<EventSource*>(this)), pos, value);
}

template<class T, class EventSource, class Allocator>
void Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::pushBack(T&& value)
{
    size_t pos = m_vector.size();
    m_vector.push_back(value);
    m_observers.notifyElementAdded(*(static_cast<EventSource*>(this)), pos, value);
}

template<class T, class EventSource, class Allocator>
typename Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::Observers&
    Ishiko::Collections::ObservableVector<T, EventSource, Allocator>::observers()
{
    return m_observers;
}

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::Observer::onElementAdded(
    const Ishiko::Collections::ObservableVector<T, void, Allocator>& source, size_t pos, const T& value)
{
}

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::Observer::onElementsRemoved(
    const Ishiko::Collections::ObservableVector<T, void, Allocator>& source, size_t first, size_t last,
    const std::vector<T, Allocator>& removedElements)
{
}

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::Observers::add(
    std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<ObservableVector<T, void, Allocator>::Observer>, size_t>& o)
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

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::Observers::remove(
    std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<ObservableVector<T, void, Allocator>::Observer>, size_t>& o)
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

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::Observers::notifyElementAdded(
    const Ishiko::Collections::ObservableVector<T, void, Allocator>& source, size_t pos, const T& value)
{
    for (std::pair<std::weak_ptr<ObservableVector<T, void, Allocator>::Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<ObservableVector<T, void, Allocator>::Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onElementAdded(source, pos, value);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::Observers::notifyElementsRemoved(
    const Ishiko::Collections::ObservableVector<T, void, Allocator>& source, size_t first, size_t last,
    const std::vector<T, Allocator>& removedElements)
{
    for (std::pair<std::weak_ptr<ObservableVector<T, void, Allocator>::Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<ObservableVector<T, void, Allocator>::Observer> observer = o.first.lock();
        if (observer)
        {
            observer->onElementsRemoved(source, first, last, removedElements);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<ObservableVector<T, void, Allocator>::Observer>, size_t>& o)
    {
        return o.first.expired();
    }
    );
    m_observers.erase(it, m_observers.end());
}

template<class T, class Allocator>
T& Ishiko::Collections::ObservableVector<T, void, Allocator>::operator[](size_t pos)
{
    return m_vector[pos];
}

template<class T, class Allocator>
const T& Ishiko::Collections::ObservableVector<T, void, Allocator>::operator[](size_t pos) const
{
    return m_vector[pos];
}

template<class T, class Allocator>
T& Ishiko::Collections::ObservableVector<T, void, Allocator>::back()
{
    return m_vector.back();
}

template<class T, class Allocator>
const T& Ishiko::Collections::ObservableVector<T, void, Allocator>::back() const
{
    return m_vector.back();
}

template<class T, class Allocator>
typename std::vector<T, Allocator>::iterator
Ishiko::Collections::ObservableVector<T, void, Allocator>::begin() noexcept
{
    return m_vector.begin();
}

template<class T, class Allocator>
typename std::vector<T, Allocator>::const_iterator
Ishiko::Collections::ObservableVector<T, void, Allocator>::begin() const noexcept
{
    return m_vector.begin();
}

template<class T, class Allocator>
typename std::vector<T, Allocator>::iterator
Ishiko::Collections::ObservableVector<T, void, Allocator>::end() noexcept
{
    return m_vector.end();
}

template<class T, class Allocator>
typename std::vector<T, Allocator>::const_iterator
Ishiko::Collections::ObservableVector<T, void, Allocator>::end() const noexcept
{
    return m_vector.end();
}

template<class T, class Allocator>
size_t Ishiko::Collections::ObservableVector<T, void, Allocator>::size() const noexcept
{
    return m_vector.size();
}

template<class T, class Allocator>
typename std::vector<T, Allocator>::iterator Ishiko::Collections::ObservableVector<T, void, Allocator>::erase(
    typename std::vector<T, Allocator>::const_iterator pos)
{
    size_t firstPos = pos - m_vector.cbegin();
    std::vector<T, Allocator> removedElements;
    removedElements.push_back(*pos);
    typename std::vector<T, Allocator>::iterator result = m_vector.erase(pos);
    m_observers.notifyElementsRemoved(*this, firstPos, firstPos + 1, removedElements);
    return result;
}

template<class T, class Allocator>
typename std::vector<T, Allocator>::iterator Ishiko::Collections::ObservableVector<T, void, Allocator>::erase(
    typename std::vector<T, Allocator>::const_iterator first, typename std::vector<T, Allocator>::const_iterator last)
{
    size_t firstPos = first - m_vector.cbegin();
    size_t lastPos = last - m_vector.cbegin();
    std::vector<T, Allocator> removedElements;
    removedElements.insert(removedElements.end(), first, last);
    typename std::vector<T, Allocator>::iterator result = m_vector.erase(first, last);
    m_observers.notifyElementsRemoved(*this, firstPos, lastPos, removedElements);
    return result;
}

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::pushBack(const T& value)
{
    size_t pos = m_vector.size();
    m_vector.push_back(value);
    m_observers.notifyElementAdded(*this, pos, value);
}

template<class T, class Allocator>
void Ishiko::Collections::ObservableVector<T, void, Allocator>::pushBack(T&& value)
{
    size_t pos = m_vector.size();
    m_vector.push_back(value);
    m_observers.notifyElementAdded(*this, pos, value);
}

template<class T, class Allocator>
typename Ishiko::Collections::ObservableVector<T, void, Allocator>::Observers&
    Ishiko::Collections::ObservableVector<T, void, Allocator>::observers()
{
    return m_observers;
}

#endif
