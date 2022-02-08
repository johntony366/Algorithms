#include <iostream>
#include <array>
#include <algorithm>

using array_type = std::array<int, 9>;
using index_type = array_type::size_type;
void insertionSort(array_type& array)
{
    auto lastSorted_index{ 0 };
    while (lastSorted_index < std::size(array))
    {
        auto temp{ array[lastSorted_index + 1] };
        auto temp_index{ lastSorted_index + 1 };
        for (int comparisonIndex{ lastSorted_index }; comparisonIndex >= 0; --comparisonIndex)
        {
            if (array[lastSorted_index+1] < array[comparisonIndex])
            {
                array[comparisonIndex+1] = array[comparisonIndex];
                --temp_index;
            }
        }
        array[temp_index] = temp;
        ++lastSorted_index;
    }
}
int main()
{
    array_type array{ 5, 1, 2, 4, 3, 9, 8, 7, 6 };
    insertionSort(array);
    for (int element : array)
    {
        std::cout << element << ' ';
    }
}