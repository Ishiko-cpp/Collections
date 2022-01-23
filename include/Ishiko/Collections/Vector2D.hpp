/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_COLLECTIONS_VECTOR2D_HPP_
#define _ISHIKO_CPP_COLLECTIONS_VECTOR2D_HPP_

#include <vector>
#include <memory>

namespace Ishiko
{
namespace Collections
{
    
template<class T, class Allocator = std::allocator<T>>
class Vector2D
{
public:
    Vector2D(size_t rows, size_t columns);

    const T& get(size_t row, size_t column) const noexcept;
    T& get(size_t row, size_t column) noexcept;

    size_t size() const noexcept;
    std::pair<size_t, size_t> dimensions() const noexcept;

private:
    size_t m_rows;
    size_t m_columns;
    std::vector<T, Allocator> m_vector;
};

template<class T, class Allocator>
Vector2D<T, Allocator>::Vector2D(size_t rows, size_t columns)
    : m_rows(rows), m_columns(columns)
{
    m_vector.resize(m_rows * m_columns);
}

template<class T, class Allocator>
const T& Vector2D<T, Allocator>::get(size_t row, size_t column) const noexcept
{
    return m_vector[row * m_columns + column];
}

template<class T, class Allocator>
T& Vector2D<T, Allocator>::get(size_t row, size_t column) noexcept
{
    return m_vector[row * m_columns + column];
}

template<class T, class Allocator>
size_t Vector2D<T, Allocator>::size() const noexcept
{
    return m_vector.size();
}

template<class T, class Allocator>
std::pair<size_t, size_t>  Vector2D<T, Allocator>::dimensions() const noexcept
{
    return std::pair<size_t, size_t>(m_rows, m_columns);
}

}
}

#endif
