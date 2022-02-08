#include <iostream>
#include <vector>
#include <array>

using matrix_t = std::vector<std::vector<int>>;

void displayMatrix(matrix_t M)
{
    int n = M.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cout << M[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

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

matrix_t subtract(const matrix_t& M1, const matrix_t& M2)
{
    int n = M1.size();
    matrix_t M(n, std::vector(n, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            M[i][j] = M1[i][j] - M2[i][j];
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

        //computing 10 "S" matrices
        matrix_t S1 = subtract(b12, b22);
        matrix_t S2 = add(a11, a12);
        matrix_t S3 = add(a21, a22);
        matrix_t S4 = subtract(b21, b11);
        matrix_t S5 = add(a11, a22);
        matrix_t S6 = add(b11, b22);
        matrix_t S7 = subtract(a12, a22);
        matrix_t S8 = add(b21, b22);
        matrix_t S9 = subtract(a11, a21);
        matrix_t S10 = add(b11, b12);

        matrix_t P1 = squareMatrixMultiplyRecursive(a11, S1);
        matrix_t P2 = squareMatrixMultiplyRecursive(S2, b22);
        matrix_t P3 = squareMatrixMultiplyRecursive(S3, b11);
        matrix_t P4 = squareMatrixMultiplyRecursive(a22, S4);
        matrix_t P5 = squareMatrixMultiplyRecursive(S5, S6);
        matrix_t P6 = squareMatrixMultiplyRecursive(S7, S8);
        matrix_t P7 = squareMatrixMultiplyRecursive(S9, S10);

        matrix_t c11 = matrixSlice(C, 1);
        matrix_t c12 = matrixSlice(C, 2);
        matrix_t c21 = matrixSlice(C, 3);
        matrix_t c22 = matrixSlice(C, 4);               

        c11 = add(subtract(add(P5, P4), P2), P6);
        c12 = add(P1, P2);
        c21 = add(P3, P4);
        c22 = subtract(subtract(add(P5, P1), P3), P7);

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
    displayMatrix(C);
    return 0;
}