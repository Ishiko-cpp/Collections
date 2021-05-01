/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_KEYEDHASHSET_H_
#define _ISHIKO_COLLECTIONS_KEYEDHASHSET_H_

#include <functional>
#include <iterator>
#include <utility>

namespace Ishiko
{
namespace Collections
{
   
template<class T, class Hash = std::hash<T>>
class KeyedHashSet
{
public:
    typedef T value_type;
    class iterator
    {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef size_t difference_type;
        typedef value_type& reference;
        typedef value_type* pointer;

        iterator(T* ptr) noexcept;

        reference operator*() const noexcept;
        iterator& operator++() noexcept;

        bool operator==(const iterator& other)
        {
            return (m_ptr == other.m_ptr);
        }
        
        bool operator!=(const iterator& other)
        {
            return (m_ptr != other.m_ptr);
        }

    private:
        T* m_ptr;
    };

    size_t size() const noexcept;

    std::pair<iterator, bool> insert(const value_type& value);

private:
    std::vector<T> m_buckets;
};

template<class T, class Hash>
KeyedHashSet<T, Hash>::iterator::iterator(T* ptr) noexcept
    : m_ptr(ptr)
{
}

template<class T, class Hash>
typename KeyedHashSet<T, Hash>::iterator::reference KeyedHashSet<T, Hash>::iterator::operator*() const noexcept
{
    return *m_ptr;
}

template<class T, class Hash>
typename KeyedHashSet<T, Hash>::iterator& KeyedHashSet<T, Hash>::iterator::operator++() noexcept
{
    ++m_ptr;
    return *this;
}

template<class T, class Hash>
size_t KeyedHashSet<T, Hash>::size() const noexcept
{
    return m_buckets.size();
}

template<class T, class Hash>
std::pair<typename KeyedHashSet<T, Hash>::iterator, bool> KeyedHashSet<T, Hash>::insert(const value_type& value)
{
    m_buckets.reserve(100);
    m_buckets.push_back(value);
    return std::pair<typename KeyedHashSet<T>::iterator, bool>(iterator(m_buckets.data() + m_buckets.size() - 1), true);
}

}
}

#endif
