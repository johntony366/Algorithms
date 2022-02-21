#include <iostream>
#include <cassert>
#include <vector>

void merge(std::vector<int>& array, int start, int mid, int end)
{
    int n1{ mid - start + 1 };
    int n2{ end - mid };
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (int i{ }; i < n1; ++i)
    {
        L[i] = array[start + i];
    }
    for (int j{ }; j < n2; ++j)
    {
        R[j] = array[mid + 1 + j];
    }
    int i{ 0 }, j{ 0 }, k{ start };
    while (i<n1 && j<n2)
    {
        if (L[i] <= R[j])
        {
            array[k] = L[i];
            ++i;
        }
        else
        {
            array[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        array[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n1)
    {
        array[k] = R[j];
        ++j;
        ++k;
    }
}

void mergesort(std::vector<int>& array, int start, int end)
{
    if (start < end)
    {
        int mid{ start + ((end - start)/2) };
        mergesort(array, start, mid);
        mergesort(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}

int main()
{
    std::vector<int> array{ 8, 7, 6, 5, 4, 3, 2, 1 };
    int length{ static_cast<int>(std::size(array)) };
    mergesort(array, 0, length-1);
    for (int element : array)
    {
        std::cout << element << ' ';
    }
    std::cout << '\n';
    return 0;
}