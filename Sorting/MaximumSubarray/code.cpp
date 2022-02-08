#include <iostream>
#include <vector>
#include <tuple>

std::tuple<int, int, double> findMaxCrossingSubarray(std::vector<double> A, int low, int mid, int high)
{
    double leftSum = A[mid];
    double sum = A[mid];
    int max_left = mid;
    for (int leftIndex = mid - 1; leftIndex >= low; --leftIndex)
    {
        sum += A[leftIndex];
        if (sum > leftSum)
        {
            leftSum = sum;
            max_left = leftIndex;
        }
    }

    double rightSum = A[mid + 1];
    sum = A[mid + 1];
    int max_right = mid + 1;
    for (int rightIndex = mid + 2; rightIndex < high; ++rightIndex)
    {
        sum += A[rightIndex];
        if (sum > rightSum)
        {
            rightSum = sum;
            max_right = rightIndex;
        }
    }

    return std::tuple<int, int, double>(max_left, max_right, leftSum + rightSum);
}

std::tuple<int, int, double> findMaxSubarray(std::vector<double> A, int low, int high)
{
    if (low == high)
    {
        return std::tuple<int, int, double>(low, high, A[low]);
    }

    else
    {
        int mid = low + (high - low)/2;
        auto [left_low, left_high, left_sum ] = findMaxSubarray(A, low, mid);
        auto [right_low, right_high, right_sum ] = findMaxSubarray(A, mid+1, high);
        auto [cross_low, cross_high, cross_sum ] = findMaxCrossingSubarray(A, low, mid, high);

        if (left_sum >= right_sum && left_sum >= cross_sum)
        {
            return std::tuple<int, int, double>(left_low, left_high, left_sum);
        }
        else if (right_sum >= left_sum && right_sum >= cross_sum)
        {
            return std::tuple<int, int, double>(right_low, right_high, right_sum);
        }
        else
        {
            return std::tuple<int, int, double>(cross_low, cross_high, cross_sum);
        }

    }
}

int main()
{
    std::vector<double> A{ 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
    auto result{ findMaxSubarray(A, 0, A.size()-1) };
    std::cout << "The starting element of max subarray is at index: " << std::get<0>(result) << '\n';
    std::cout << "The ending element of max subarray is at index: " << std::get<1>(result) << '\n';
    std::cout << "The sum of max subarray is: " << std::get<2>(result) << '\n';
}