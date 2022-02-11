#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>



// [2, 8, 7, 1, 3, 5, 6, 4]
//i,p,j                  r

int getRandomNumber(int min, int max)
{
    static constexpr double fraction{ 1.0/(RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1)*(std::rand()*fraction));
}

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

int randomisedPartition(std::vector<int>& A, int p, int r)
{
    int i = getRandomNumber(p, r);
    std::swap(A[i], A[r]);
    return partition(A, p, r);
}

void quicksort(std::vector<int>& A, int p, int r)
{
    if (p < r)
    {
        int q = randomisedPartition(A, p, r);
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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();

    std::vector<int> A{2, 8, 7, 1, 3, 5, 6, 4};
    quicksort(A, 0, A.size() -1);
    printArray(A);

    return 0;
}