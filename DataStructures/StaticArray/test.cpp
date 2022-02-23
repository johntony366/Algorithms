#include "StaticArray.h"
#include <iostream>

int main()
{
    // declare an integer array with room for 12 integers
    StaticArray<int, 12> intArray;

    // Fill it up in order, then print it backwards
    for (int count { 0 }; count < 12; ++count)
        intArray[count] = count;

    std::cout << intArray << '\n';
    std::cout << intArray.getArray() << ' ' << intArray.getSize() << '\n';

    // declare a double buffer with room for 4 doubles
    StaticArray<double, 4> doubleArray;

    for (int count { 0 }; count < 4; ++count)
        doubleArray[count] = 4.4 + 0.1 * count;

    std::cout << doubleArray << '\n';
    std::cout << doubleArray.getArray() << ' ' << doubleArray.getSize() << '\n';

    return 0;
}