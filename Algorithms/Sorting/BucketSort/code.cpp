#include <iostream>
#include <iterator>
#include <vector>

void insertionSort(std::vector<float>& A)
{
    int n = A.size();
    for (int i = 1; i < n; ++i)
    {
        float key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key)
        {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

void bucketSort(float* A, int n)
{
    std::vector<float> bucket[n];
    
    for (int i = 0; i < n; ++i)
    {
        int bucketIndex = static_cast<int>(n*A[i]);
        bucket[bucketIndex].push_back(A[i]);
    }

    for (int i = 0; i < n; ++i)
    {
        insertionSort(bucket[i]);
    }

    int index = 0;
    for (int i = 0; i < n; ++i)
    {
        for (float f : bucket[i])
        {
            A[index++] = f;
        }
    }
}

int main()
{
    float A[]{ 0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68 };
    int n = std::size(A);

    bucketSort(A, n);

    for (int i = 0; i < n; ++i)
    {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}