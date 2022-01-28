#include <iostream>
#include <algorithm>
#include <vector>

int mergeAndCountSplitInv(std::vector<int> a, int start, int mid, int end)
{
    int countSplitInv = 0;
    int n1 = mid - start + 1;
    int n2 = end - mid;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (int i = 0; i < n1; ++i)
    {
        L[i] = a[start + i];
    }
    for (int i = 0; i < n2; ++i)
    {
        R[i] = a[mid + 1 + i];
    }
    int i{0}, j{0}, k{start};
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            a[k] = L[i];
            ++i;
            ++k;
        }
        else
        {
            a[k] = R[j];
            countSplitInv += n1 - i;
            ++j;
            ++k;
        }
    }
    while (i < n1)
    {
        a[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        a[k] = L[j];
        ++j;
        ++k;
    }

    return countSplitInv;
}

int sortAndCountInv(std::vector<int> a, int start, int end)
{
    int inv = 0;

    if (start < end)
    {
        int mid = start + (end - start)/2;
        inv += sortAndCountInv(a, start, mid);
        inv += sortAndCountInv(a, mid+1, end);
        inv += mergeAndCountSplitInv(a, start, mid, end);
    }
    return inv;

}


int main()
{
    std::vector<int> a{ 1, 20, 6, 4, 5 };
    std::cout << sortAndCountInv(a, 0, std::size(a)-1) << '\n';
}