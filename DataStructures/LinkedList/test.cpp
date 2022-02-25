#include "SinglyLinkedList.h"

int main()
{
    LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
    {
        list.append(i);
    }
    std::cout << list << '\n';

    list[5] = 149;
    std::cout << list << '\n' << list.find(5) << ' ' << list.find(149) << '\n';
    list.remove(0);
    std::cerr << list << '\n';
    list.remove(3);
    std::cerr << list << '\n';
    list.remove(list.getSize() - 1);
    std::cout << list << '\n';
    list.insert(98, 0);
    list.insert(42, 6);
    list.insert(100, list.getSize());
    std::cout << list << '\n';

    return 0;
}