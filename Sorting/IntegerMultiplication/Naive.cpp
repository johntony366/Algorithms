#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

int multiply(int n1, int n2)
{
    std::string x{ std::to_string(n1) };
    std::string y{ std::to_string(n2) };

    int result = 0;

    for (int i = y.length()-1; i >= 0; --i)
    {
        int carry = 0;
        std::string intermediate_result = "";
        for (int j = x.length()-1; j >= 0; --j)
        {
            int num = (x[j]-'0') * (y[i] - '0') + carry;
            if (num > 9)
            {
                carry = num/10;
                num = num%10;
            }
            else
            {
                carry = 0;
            }
            intermediate_result += std::to_string(num); 
        }
        std::reverse(intermediate_result.begin(), intermediate_result.end());
        result += std::stoi(intermediate_result)*(std::pow(10, y.length()-i -1));
    }
    return result;
}

int main()
{
    int n1{ };
    std::cout << "Enter the first number: ";
    std::cin >> n1;
    
    int n2{ };
    std::cout << "Enter the second number: ";
    std::cin >> n2;

    int product{ multiply(n1, n2) };
    std::cout << "The product is: " << product << '\n';
}