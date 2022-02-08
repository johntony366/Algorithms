#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

std::string sumOfProducts(std::vector<std::string>& results)
{
    int tp = 0;
    for (std::string& result : results)
    {
        result += std::string(tp++, '0');
    }
    auto length = (results.back()).size();
    for (std::string& result : results)
    {
        auto currentLength{ result.size() };
        std::string temp2 = std::string(length - currentLength, '0');
        result = temp2 + result;
    }
    std::string finalSum = "";
    int carry = 0;
    for (int i = 0; i < length; ++i)
    {
        int columnSum = 0;
        for (std::string& result : results)
        {
            columnSum += (result.back() - '0');
            result = result.substr(0, result.size()-1);
        }
        columnSum += carry;
        if ((columnSum > 9) && (i != length - 1))
        {
            carry = columnSum/10;
            columnSum = columnSum%10;
        }
        else
        {
            carry = 0;
        }
        finalSum = std::to_string(columnSum) + finalSum;
    }
    return finalSum;
} 

std::string multiply(std::string x, std::string y)
{

    std::vector<std::string> results{ };

    for (int i = y.length()-1; i >= 0; --i)
    {
        int carry = 0;
        std::string intermediate_result = "";
        for (int j = x.length()-1; j >= 0; --j)
        {
            int num = (x[j]-'0') * (y[i] - '0') + carry;
            if (num > 9 && j != 0)
            {
                carry = num/10;
                num = num%10;
            }
            else
            {
                carry = 0;
            }
            intermediate_result = std::to_string(num) + intermediate_result; 
        }
        results.push_back(intermediate_result);
    }
    std::string final_result{ sumOfProducts(results) };
    return final_result;
}

int main()
{
    std::string n1{ };
    std::cout << "Enter the first number: ";
    std::cin >> n1;
    
    std::string n2{ };
    std::cout << "Enter the second number: ";
    std::cin >> n2;

    std::string product{ multiply(n1, n2) };
    std::cout << "The product is: " << product << '\n';
}