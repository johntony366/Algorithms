#include "CircularArray.h"
#include <iostream>

int main()
{
    CircularArray<int> arr;
    for (int i = 0; i < 9; ++i)
    {
        arr.insertBack(i);
    }
    arr.insertBack(142);
    arr.insertBack(100);
    arr.print();
    arr.removeBack(); arr.print();
    arr.removeFront(); arr.print();
    std::cout << arr[5] << '\n';

    return 0;
}