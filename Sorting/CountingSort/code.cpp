#include <bits/stdc++.h>

void countingSort(int* A, int n, int k, int* result)
{

    int temp[k+1]{ 0 };

    for (int i = 0; i < n; ++i)
    {
        ++temp[A[i]];
    }

    for (int i = 1; i <= k; ++i)
    {
        temp[i] += temp[i-1];
    }

    for (int i = n-1; i >= 0; --i)
    {
        result[temp[A[i]]-1] = A[i];
        --temp[A[i]];
    }
}

int main()
{
    int A[]{ 2, 5, 3, 0, 2, 3, 0, 3 };
    int n = std::size(A);
    int k = 5;

    int result[n];
    std::copy(A, A + n, result);

    countingSort(A, n, k, result);

    for (int i = 0; i < n; ++i)
    {
        std::cout << result[i] << ' ';
    }
    std::cout << '\n';
    
    return 0;
}