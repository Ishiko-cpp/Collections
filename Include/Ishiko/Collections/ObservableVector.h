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

namespace Ishiko
{
namespace Collections
{

template<class T>
class ObservableVector
{
public:
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    size_t size() const noexcept;

    void pushBack(T&& value);

private:
    std::vector<T> m_vector;
};

}
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
void Ishiko::Collections::ObservableVector<T>::pushBack(T&& value)
{
    m_vector.push_back(value);
}

#endif
