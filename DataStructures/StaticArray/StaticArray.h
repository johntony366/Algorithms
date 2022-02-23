#pragma once

#include <iostream>
#include <cassert>

template <typename T, int size>
class StaticArray
{
private:
    T m_array[size]{ };

public:
    T& operator[](int index)
    {
        assert(index >= 0 && index < size);
        return m_array[index];
    }

    T operator[](int index) const
    {
        assert(index >= 0 && index < size);
        return m_array[index];
    }

    friend std::ostream& operator<<(std::ostream& out, const StaticArray& array)
    {
        for (int i = 0; i < size; ++i)
        {
            out << array[i] << ' ';
        }
        return out;
    }

    T* getArray();
    int getSize();
};

template <typename T, int size>
inline T* StaticArray<T, size>::getArray()
{
    return m_array;
}

template<typename T, int size>
inline int StaticArray<T, size>::getSize()
{
    return size;
}