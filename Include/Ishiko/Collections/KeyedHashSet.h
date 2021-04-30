/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Collections/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_COLLECTIONS_KEYEDHASHSET_H_
#define _ISHIKO_COLLECTIONS_KEYEDHASHSET_H_

namespace Ishiko
{
namespace Collections
{
   
template<class T>
class KeyedHashSet
{
public:
    size_t size() const noexcept;
};

template<class T>
size_t KeyedHashSet<T>::size() const noexcept
{
    return 0;
}

}
}

#endif
