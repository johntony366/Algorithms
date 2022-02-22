#pragma once

//This is just to show how to create template friend functions 
#include <iostream>
#include <cassert>

template <typename T>
class ArrayList;

template <typename T>
std::ostream& operator<<(std::ostream& out, const ArrayList<T>& array);

template <typename T>
class ArrayList
{
private:
    int m_size;
    int m_capacity;
    T* m_data;

    void deepCopy(const ArrayList& source)
    {
        delete[] m_data;

        m_size = source.m_size;
        if (source.m_data)
        {
            m_data = new T[m_size];

            for (int i = 0; i < m_size; ++i)
            {
                m_data[i] = source.m_data[i];
            }
        }
        else
        {
            m_data = nullptr;
        }
    }

    void doubleCapacity()
    {
        int oldCapacity = m_capacity;
        T* oldData = m_data;

        m_capacity = 2*oldCapacity;
        m_data = new T[m_capacity]{ };

        for (int i = 0; i < m_size; ++i)
        {
            m_data[i] = oldData[i];
        }

        delete[] oldData;
    }

public:
    ArrayList(int length): m_size{ length }, m_capacity{ length }
    {
        assert(length >= 0);
        m_data = new T[m_capacity]{ };
    }

    ArrayList(): m_size{ 0 }, m_capacity{ 0 }
    {
        m_data = new T[m_capacity]{ };
    }

    ArrayList(const ArrayList& source)
    {
        deepCopy(source);
    }

    ArrayList& operator=(const ArrayList& source)
    {
        if (this != &source)
        {
            deepCopy(source);
        }
        else
        {
            return *this;
        }
    }

    ~ArrayList()
    {
        delete[] m_data;
    }

    T& operator[](int index)
    {
        assert(index >= 0 && index < m_size);
        return m_data[index];
    }

    T operator[](int index) const
    {
        assert(index >= 0 && index < m_size);
        return m_data[index];
    }

    void insert(T element, int index)
    {
        assert(index >= 0 && index <= m_size);
        if (m_size == m_capacity)
        {
            if (m_capacity == 0)
            {
                ++m_capacity;
            }
            doubleCapacity();
        }

        if (index == m_size)
        {
            m_data[index] = element;
        }
        else
        {
            //[1, 5, 2, 3] insert(3, 2)
            for (int i = m_size; i > index; --i)
            {
                m_data[i] = m_data[i-1];
            }
            m_data[index] = element;
        }
        ++m_size;
    }

    void add(T element)
    {
        insert(element, m_size);
    }

    int find(T element)
    {
        for (int i = 0; i < m_size; ++i)
        {
            if (m_data[i] == element)
            {
                return i;
            }
        }
        return -1;
    }

    int getSize() const
    {
        return m_size;
    }

    int getCapacity() const
    {
        return m_capacity;
    }

    friend std::ostream& operator<<<T>(std::ostream& out, const ArrayList<T>& array);  // <-----
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const ArrayList<T>& array)
{
    for (int i = 0; i < array.m_size; ++i)
    {
        out << array.m_data[i] << ' ';
    }
    return out << '\n';
}