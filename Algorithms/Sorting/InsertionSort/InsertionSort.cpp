#include <iostream>
#include <algorithm>
#include <iterator>

void insertionSort(int* A, int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

int main()
{
    int A[]{ 5, 1, 2, 4, 3, 9, 8, 7, 6 };
    int n = std::size(A);

    insertionSort(A, n);

    for (int i = 0; i < n; ++i)
    {
        std::cout << A[i] << ' ';
    }

    std::cout << '\n';
    return 0;
}