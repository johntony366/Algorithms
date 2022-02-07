#include <vector>
#include <iostream>
#include <algorithm>

// [2, 8, 7, 1, 3, 5, 6, 4]
//i,p,j                  r

int partition(std::vector<int>& A, int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; ++j)
    {
        if (A[j] <= x)
        {
            i += 1;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i+1], A[r]);
    return i+1;  //returns index of pivot element
}

void quicksort(std::vector<int>& A, int p, int r)
{
    if (p < r)
    {
        int q = partition(A, p, r);
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}

void printArray(const std::vector<int>& A)
{
    for (auto e : A)
    {
        std::cout << e << ' ';
    }
    std::cout << '\n';
}
int main()
{
    std::vector<int> A{2, 8, 7, 1, 3, 5, 6, 4};
    quicksort(A, 0, A.size() -1);
    printArray(A);

    return 0;
}