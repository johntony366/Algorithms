#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

int findMedian(int a, int b, int c)
{
    std::vector<int> numbers{ a, b, c };
    std::sort(numbers.begin(), numbers.end());
    return numbers[1];
}

// [2, 8, 7, 1, 3, 5, 6, 4]
//i,p,j                  r

int partition(std::vector<int>& A, int p, int r, int& sum)
{
    sum += r - p;

    int median = findMedian(A[p],A[(p+r)/2], A[r]);
    int median_index = std::find(A.begin(), A.end(), median) - A.begin();
    std::swap(A[median_index], A[p]);
    
    int x = A[p];
    int i = p+1;
    for (int j = p + 1; j <= r; ++j)
    {
        if (A[j] < x)
        {
            std::swap(A[i], A[j]);
            ++i;
        }
    }
    std::swap(A[p], A[i-1]);
    return i-1;  //returns index of pivot element
}

void quicksort(std::vector<int>& A, int p, int r, int& sum)
{
    if (p < r)
    {
        int q = partition(A, p, r, sum);
        quicksort(A, p, q - 1, sum);
        quicksort(A, q + 1, r, sum);
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
    std::vector<int> A(10000);
    std::ifstream f;
    f.open("Input.txt");
    std::string str;
    int count = 0;

    while(std::getline(f, str))
    {
        A[count++] = std::stoi(str);
    }

    int sum = 0;
    quicksort(A, 0, A.size() -1, sum);
    printArray(A);
    std::cout << "\n\n" << sum << '\n';

    return 0;
}