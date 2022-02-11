#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void printArray(int* arr, int start, int end)
{
    for (int i = start; i <= end; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

int getRandomNumber(int min, int max)
{
    static constexpr double fraction{ 1.0/(RAND_MAX + 1.0) };
    return min + static_cast<int>((max - min + 1)*(std::rand() * fraction));
}

int partition(int* arr, int start, int end)
{
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

int randomisedPartition(int* arr, int start, int end)
{
    int p = getRandomNumber(start, end);

    swap(arr, p, end);
    return partition(arr, start, end);

}

int randomisedSelect(int* arr, int start, int end, int i, int n)
{
    if (start >= end)
    {
        return arr[start];
    }
    int p = randomisedPartition(arr, start, end);
    int k = p - start;

    if (i == k)
    {
        return arr[p];
    }
    else if (i < k)
    {
        return randomisedSelect(arr, start, p - 1, i, n);
    }
    else //i > k
    {
        return randomisedSelect(arr, p + 1, end, i - k - 1, n);
    }

}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();

    int arr[]{ 3, 2, 9, 0, 7, 5, 4, 8, 6, 1 };
    int n = std::size(arr);

    int i;
    std::cin >> i;

    std::cout << randomisedSelect(arr, 0, n-1, i-1, n) << '\n';
    return 0; 
}