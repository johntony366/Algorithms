#include <iostream>
#include <string>
#include <vector>
#include <cmath>

void equalizeLength(std::string& n1, std::string& n2)
{
    if (n1.length() > n2.length())
    {
        do
        {
            n2 = "0" + n2;
        }
        while (n1.length() != n2.length());
    }
    else if (n2.length() > n1.length())
    {
        do
        {
            n1 = "0" + n1;
        }
        while (n1.length() != n2.length());
    }
}

std::string add(std::string n1, std::string n2)
{
    equalizeLength(n1, n2);
    int n = n1.length();
    std::string resultString = "";
    int carry = 0;
    while (n > 0)
    {
        int columnSum = ((n1[n-1]-'0') + (n2[n-1] - '0')) + carry;
        if ((columnSum > 9) && n != 1)
        {
            carry = columnSum/10;
            columnSum = columnSum%10;
        }
        else
        {
            carry = 0;
        }
        resultString = std::to_string(columnSum) + resultString;
        --n;
    }
    return resultString;
}

std::string subtract(std::string n1, std::string n2)
{
    equalizeLength(n1, n2);
    int n = n1.length();
    int carry = 0;
    std::string resultString = "";
    for (int i = n-1; i >= 0; --i)
    {
        int diff = (n1[i] - '0') - (n2[i] - '0') - carry;
        if (diff < 0)
        {
            if (i == 0)
            {
                return "";
            }
            diff += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        resultString = std::to_string(diff) + resultString;
    }
    return resultString;
}

std::string multiply(std::string n1, std::string n2)
{
    equalizeLength(n1, n2);
    int n = n1.length();
    if (n == 1)
    {
        return std::to_string(std::stoi(n1)*std::stoi(n2));
    }
    std::string a = n1.substr(0, n/2);
    std::string b = n1.substr(n/2, n - n/2);
    std::string c = n2.substr(0, n/2);
    std::string d = n2.substr(n/2, n - n/2);
    std::string ac = multiply(a,c);
    std::string bd = multiply(b,d);
    // std::string ad = multiply(a,d);
    // std::string bc = multiply(b,c);
    std::string apb = add(a,b);
    std::string cpd = add(c,d);
    equalizeLength(apb, cpd);
    std::string sumprod = multiply(apb, cpd);
    std::string adpbc = subtract(subtract(sumprod, ac), bd) + std::string(n/2,'0');
    ac +=  std::string(n,'0');
    std::string temp = add(ac, adpbc); 
    return (add(temp, bd));
}

int main()
{
    std::string n1{ };
    std::cin >> n1;

    std::string n2{};
    std::cin >> n2;

    std::cout << multiply(n1, n2) << '\n';
}