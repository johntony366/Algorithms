#include <iostream>
#include <cmath>

void countingSort(int* A, int n, unsigned long long exp)
{
    int result[n];
    int temp[10]{ 0 };

    for (int i = 0; i < n; ++i)
    {
        ++temp[(A[i]/exp)%10];
    }

    for (int i = 1; i <= 9; ++i)
    {
        temp[i] += temp[i-1];
    }

    for (int i = n-1; i >= 0; --i)
    {
        result[temp[(A[i]/exp)%10]-1] = A[i];
        --temp[(A[i]/exp)%10];
    }

    //update A
    for (int i = 0; i < n; ++i)
    {
        A[i] = result[i];
    }
}

void radixSort(int* A, int n, int d)
{
    unsigned long long exp = 1;

    for (int i = 1; i <= d; ++i)
    {
        countingSort(A, n, exp);
        exp *= 10;
    }
}

int main()
{
    int A[]{ 329, 457, 657, 839, 436, 720, 355 };
    int n = std::size(A);
    int d = 3;

    radixSort(A, n, d);

    for (int i = 0; i < n; ++i)
    {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}