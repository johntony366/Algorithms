#include <iostream>
#include <vector>
#include <array>

using matrix_t = std::vector<std::vector<int>>;

matrix_t matrixSlice(matrix_t M, int portion)
{
    int n = M.size();
    matrix_t slice{ };
    int startRow{ };
    int endRow{ n/2-1 };
    int startCol{ };
    int endCol{ n/2-1 };
    switch (portion)
    {
    case 1:
        break;
    case 2:
        startCol = n/2;
        endCol = n-1;
        break;
    case 3:
        startRow = n/2;
        endRow = n-1;
        break;
    case 4:
        startRow = n/2;
        endRow = n-1;
        startCol = n/2;
        endCol = n-1;
        break;
    }
    std::vector<int> temp{ };
    for (int row = startRow; row <= endRow; ++row)
    {
        temp = {};
        for (int col = startCol; col <= endCol; ++col)
        {
            temp.push_back(M[row][col]);
        }
        slice.push_back(temp);
    }
    return slice;
}

matrix_t add(const matrix_t& M1, const matrix_t& M2)
{
    int n = M1.size();
    matrix_t M(n, std::vector(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            M[i][j] = M1[i][j] + M2[i][j];
        }
    }
    return M;
}

matrix_t combinePortions(matrix_t c11, matrix_t c12, matrix_t c21, matrix_t c22)
{
    int n = c11.size();
    matrix_t C(2*n, std::vector<int>(2*n, 0));
    int row_n = 0;
    for (int i = 0; i < n; ++i)
    {
        std::vector<int> tempRow;
        tempRow.insert( tempRow.end(), c11[i].begin(), c11[i].end() );
        tempRow.insert( tempRow.end(), c12[i].begin(), c12[i].end() );
        C[row_n++] = tempRow;
    }
    for (int i = 0; i < n; ++i)
    {
        std::vector<int> tempRow;
        tempRow.insert( tempRow.end(), c21[i].begin(), c21[i].end() );
        tempRow.insert( tempRow.end(), c22[i].begin(), c22[i].end() );
        C[row_n++] = tempRow;
    }
    return C;
}

matrix_t squareMatrixMultiplyRecursive(matrix_t A, matrix_t B)
{
    int n = A.size();
    matrix_t C(n, std::vector(n, 0));
    if (n == 1)
    {
        C[0][0] = A[0][0]*B[0][0];
    }
    else
    {
        matrix_t a11 = matrixSlice(A, 1);
        matrix_t a12 = matrixSlice(A, 2);
        matrix_t a21 = matrixSlice(A, 3);
        matrix_t a22 = matrixSlice(A, 4);

        matrix_t b11 = matrixSlice(B, 1);
        matrix_t b12 = matrixSlice(B, 2);
        matrix_t b21 = matrixSlice(B, 3);
        matrix_t b22 = matrixSlice(B, 4);

        matrix_t c11 = matrixSlice(C, 1);
        matrix_t c12 = matrixSlice(C, 2);
        matrix_t c21 = matrixSlice(C, 3);
        matrix_t c22 = matrixSlice(C, 4);               

        c11 = add(squareMatrixMultiplyRecursive(a11, b11), squareMatrixMultiplyRecursive(a12, b21));
        c12 = add(squareMatrixMultiplyRecursive(a11, b12), squareMatrixMultiplyRecursive(a12, b22));
        c21 = add(squareMatrixMultiplyRecursive(a21, b11), squareMatrixMultiplyRecursive(a22, b21));
        c22 = add(squareMatrixMultiplyRecursive(a21, b12), squareMatrixMultiplyRecursive(a22, b22));

        C = combinePortions(c11, c12, c21, c22);
    }

    return C;
}

int main()
{
    matrix_t A
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };
    matrix_t B
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };

    matrix_t C{ squareMatrixMultiplyRecursive(A, B) };

    return 0;
}