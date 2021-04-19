/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_VECTOR2D_H_
#define _ISHIKO_COLLECTIONS_VECTOR2D_H_

#include <memory>

namespace Ishiko
{
namespace Collections
{
    
template<class T, class Allocator = std::allocator<T>>
class Vector2D
{
public:
    size_t size() const noexcept;

private:
    std::vector<T, Allocator> m_vector;
};

template<class T, class Allocator>
size_t Vector2D<T, Allocator>::size() const noexcept
{
    return m_vector.size();
}

}
}

#endif
