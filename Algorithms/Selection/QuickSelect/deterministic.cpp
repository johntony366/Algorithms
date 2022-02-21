#include <iostream>

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

void swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(int* arr, int start, int end, int x)
{
    int p;
    for (p = start; p < end; ++p)
    {
        if (arr[p] == x)
        {
            break;
        }
    }
    swap(arr, p, end);

    int pivotElement = arr[end];
    int i = start - 1;
    for (int j = start; j < end; ++j)
    {

        if (arr[j] <= pivotElement)
        {
            ++i;
            swap(arr, i, j);
        }
    }
    swap(arr, i+1, end);
    return i+1;

}

int findMedian(int* A, int n)
{
    insertionSort(A, n);
    return A[n/2];
}

int quickSelect(int* arr, int start, int end, int i)
{
    int n = end - start + 1;    //Number of elements in array arr[start... end]
    if (n == 1)
    {
        return arr[0];
    }

    int j;          
    int medians[static_cast<int>((n+4)/5)];     //array to store median of all the 5 element groups
    
    for (j = 0; j < n/5; ++j)
    {
        medians[j] = findMedian(arr + start + j*5, 5);
    }
    if (j*5 < n)
    {
        medians[j++] = findMedian(arr + start + j*5, n%5);
    }

    int medianOfMedians = quickSelect(medians, 0, j - 1, j/2);

    int p = partition(arr, start, end, medianOfMedians);
    int k = p - start;

    if (i == k)
    {
        return arr[p];
    }
    else if (i < k)
    {
        return quickSelect(arr, start, p - 1, i);
    }
    else //i > k
    {
        return quickSelect(arr, p + 1, end, i - k - 1);
    }

}

int main()
{
    int arr[]{ 12, 3, 5, 7, 4, 19, 26 };
    int n = std::size(arr);

    int i;
    std::cin >> i;

    int ithOrderStatistic = quickSelect(arr, 0, n-1, i-1);
    std::cout << "The ith smallest element is: " << ithOrderStatistic << '\n';

    return 0; 
}