#include "ArrayList.h"
#include <string>
#include <iostream>

int main()
{
//ArrayList<int>
    ArrayList<int> array(10);
    for (int i = 0; i < 10; ++i)
    {
        array[i] = i;
    }
    std::cout << array << '\n';

    array.insert(52, 3);
    std::cout << array << '\n';

    array.insert(183, 11);

    std::cout << array.find(5) << '\n';
    std::cout << array << '\n';

    std::cout << array << '\n';
    
//ArrayList<char>
    ArrayList<char> str(5);
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str.add('p');
    std::cout << str << str.find('e') << '\n';

//ArrayList<std::string>
    ArrayList<std::string> strl;
    strl.add("Hello");
    strl.add("World");
    std::cout << strl << '\n';

    return 0;
}