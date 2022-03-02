#pragma once

#include <iostream>

template <typename T>
class CircularArray
{
private:
   T* array;
   int length;
   int capacity;
   int head;
   int tail;

public:
    CircularArray();
    ~CircularArray();
    void doubleCapacity();
    void insertFront(T element);
    void insertBack(T element);
    void removeFront();
    void removeBack();
    int getLength() const;
    int getCapacity() const;
    T& operator[](int index);
    T operator[](int index) const;
    void print() const;
};

template <typename T>
CircularArray<T>::CircularArray(): array{ nullptr }, length{ 0 }, capacity{ 0 }, head{ 0 }, tail{ 0 }
{

}

template <typename T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <typename T>
void CircularArray<T>::doubleCapacity()
{
    int oldCapacity = capacity;
    capacity *= 2;
    T* newArray = new T[capacity];

    for (int i = 0; i < length; ++i)
    {
        newArray[i] = array[(head+i)%oldCapacity];
    }
    array = newArray;
    head = 0;
    tail = length - 1;
}

template <typename T>
void CircularArray<T>::insertFront(T element)
{
    if (!array)
    {
        array = new T[1]; ++length; ++capacity;
        array[0] = element;
        return;
    }
    if (length == capacity)
    {
        doubleCapacity();
    }

    --head;
    if (head == -1)
    {
        head = capacity - 1;
    }
    array[head] = element;
    ++length;
}

template <typename T>
void CircularArray<T>::insertBack(T element)
{
    if (!array)
    {
        array = new T[1]; ++length; ++capacity;
        array[0] = element;
        return;
    }
    if (length == capacity)
    {
        doubleCapacity();
    }
    ++tail;
    if (tail == capacity)
    {
        tail = 0;
    }
    array[tail] = element;
    ++length;
}

template <typename T>
void CircularArray<T>::removeFront()
{
    ++head; --length;
    if (head == capacity)
    {
        head = 0;
    }
}

template <typename T>
void CircularArray<T>::removeBack()
{
    --tail; --length;
    if (tail == -1)
    {
        tail = capacity;
    }
}

template <typename T>
int CircularArray<T>::getLength() const
{
    return length;
}

template <typename T>
int CircularArray<T>::getCapacity() const
{
    return capacity;
}

template <typename T>
T& CircularArray<T>::operator[](int index)
{
    return array[(head + index)%capacity];
}

template <typename T>
T CircularArray<T>::operator[](int index) const
{
    return array[(head + index)%capacity];
}

template <typename T>
void CircularArray<T>::print() const
{
    if (!array) return;
    for (int i = 0; i < length; ++i)
    {
        std::cout << array[(head + i)%capacity] << ' ';
    }
    std::cout << '\n';
}