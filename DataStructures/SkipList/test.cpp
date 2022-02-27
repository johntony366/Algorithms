#include "SkipList.h"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    SkipList<int> list(3, 0.5);  //3 is max level, 0.5 is P. Ideally max level would be log2(n)
  
    list.insert(3);
    list.insert(3);
    list.insert(7);
    list.insert(9);
    list.insert(12);
    list.insert(19);
    list.insert(17);
    list.insert(26);
    list.insert(21);
    list.insert(25);
    list.displayList();
  
    // Search for node 19
    std::cout << std::boolalpha << list.find(19) << '\n';
  
    //Delete node 19
    list.remove(19);
    list.displayList();
    return 0;
}