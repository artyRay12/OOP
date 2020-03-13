#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <cfloat>
#include <iomanip>
#include <cmath>
#include <array>
#include "matrixUtilities.h"

using namespace std;

//template<typename T>
void PrintMatrix(const Matrix3x3& matrix)
{
    for (auto &row : matrix)
    {
        for (auto elem : row)
        {
            cout << fixed << setprecision(3) << setw(10) << elem << "  ";
        }
        cout << endl;
    }
}

Matrix3x3 GetTransposedMatrix(Matrix3x3 matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE_3x3 - 1; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_3x3; j++)
        {
            if ((i != j) && (j > i))
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    return matrix;
}


float GetDeterminant2x2(const Matrix2x2& algExpr)
{
    return algExpr[0][0] * algExpr[1][1] - algExpr[0][1] * algExpr[1][0];
}


float GetConjugateMatrixElem(const Matrix3x3& matrix, size_t row, size_t col)
{
    Matrix2x2 minor;
    size_t minorRowIndex = 1;
    size_t minorColIndex = 1;
    float sign = 1;

    for (size_t i = 0; i < MATRIX_SIZE_3x3; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_3x3; j++)
        {
            if ((i != row) && (j != col))
            {
                minor[minorRowIndex - 1][minorColIndex - 1] = matrix[i][j];

                if (minorColIndex == MATRIX_SIZE_2x2)
                {
                    minorRowIndex++;
                    minorColIndex = 1;
                }
                else
                {
                    minorColIndex++;
                }
            }
        }
    }

    sign *= -sign;
    return sign * GetDeterminant2x2(minor);
}

Matrix3x3 GetConjugateMatrix(const Matrix3x3& matrix)
{
    Matrix3x3Row conjugateMatrixRow;
    Matrix3x3 conjugateMatrix;
    int sign = 1;

    for (size_t rowIndex = 0; rowIndex < MATRIX_SIZE_3x3; rowIndex++)
    {
        for (size_t colIndex = 0; colIndex < MATRIX_SIZE_3x3; colIndex++)
        {
            conjugateMatrixRow[colIndex] = GetConjugateMatrixElem(matrix, rowIndex, colIndex);
        }
        conjugateMatrix[rowIndex] = conjugateMatrixRow;
    }
 
    return conjugateMatrix;
}

float GetDeterminant3x3(const Matrix3x3& matrix)
{
    return (matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) + (matrix[0][2] * matrix[1][0] * matrix[2][1])
        - (matrix[0][2] * matrix[1][1] * matrix[2][0]) - (matrix[0][0] * matrix[1][2] * matrix[2][1]) - (matrix[0][1] * matrix[1][0] * matrix[2][2]);
}

Matrix3x3 MultiplyMatrixByNumber(Matrix3x3 &matrix, float number)
{
    Matrix3x3 resultMatrix = matrix;

    for (auto& row : resultMatrix)
    {
        for (auto& elem : row)
        {
            elem *= number;
        }
    }
       
    return resultMatrix;
}

optional<Matrix3x3> GetInvertedMatrix(const Matrix3x3& matrix)
{
    float det = GetDeterminant3x3(matrix);

    if (det == 0)
    {
        cout << "Ohhh no!! determinant is zero, so we cant find inverted matrix\n";
        return nullopt;
    }

    Matrix3x3 transposedMatrix = GetTransposedMatrix(matrix);
    Matrix3x3 conjugateMatrix = GetConjugateMatrix(transposedMatrix);

    return MultiplyMatrixByNumber(conjugateMatrix, 1 / det);
}
