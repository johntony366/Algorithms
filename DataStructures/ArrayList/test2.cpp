#include "ArrayList.h"
#include <iostream>

int main()
{
    ArrayList<int> array{ 1, 2, 3, 7, 3, 5 };
    std::cout << array << '\n';

    return 0;
}