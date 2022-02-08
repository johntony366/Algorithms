#include <iostream>
#include <vector>

using matrix_t = std::vector<std::vector<int>>;

matrix_t multiply(matrix_t A, matrix_t B)
{
    int n = A.size();
    matrix_t C(n, std::vector<int>(n, 0));
    
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < n; ++col)
        {
            for (int i = 0; i < n; ++i)
            {
                C[row][col] += A[row][i]*B[i][col];
            }
        }
    }
    return C;

    
}

void displayMatrix(matrix_t M)
{
    for (auto row : M)
    {
        for (auto element : row)
        {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main()
{
    matrix_t A{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    matrix_t B{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    matrix_t C{ multiply(A, B) };
    displayMatrix(C);

    return 0;
}