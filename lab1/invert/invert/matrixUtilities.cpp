#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <cfloat>
#include <iomanip>
#include <cmath>
#include "matrixUtilities.h"

using namespace std;

//template<typename Tt>
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

float CountConjugateMatrixElem(const Matrix2x2 &algExpr, size_t line, size_t col)
{   
    return  static_cast<float>(pow(-1, line + col)) * (algExpr[0][0] * algExpr[1][1] - algExpr[0][1] * algExpr[1][0]);
}

void UpdateMinorCurrentPosition(size_t &line, size_t &elem)
{
    if (elem == 1)
    {
        line = 1;
        elem = 0;
    }
    else
    {
        elem++;
    }
}

float GetConjugateMatrixElem(const Matrix3x3& matrix, size_t line, size_t col)
{
    Matrix2x2 minor;
    size_t minorLineIndex = 0;
    size_t minorElemIndex = 0;

    for (size_t i = 0; i < MATRIX_SIZE_3x3; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_3x3; j++)
        {
            if ((i != line) && (j != col))
            {
                minor[minorLineIndex][minorElemIndex] = matrix[i][j];
                UpdateMinorCurrentPosition(minorLineIndex, minorElemIndex);
            }
        }
    }
       
    return CountConjugateMatrixElem(minor, line, col);
}

Matrix3x3 GetConjugateMatrix(const Matrix3x3& matrix)
{

    Matrix3x3Line conjugateMatrixLine;
    Matrix3x3 conjugateMatrix;
    int sign = 1;

    for (size_t x = 0; x < MATRIX_SIZE_3x3; x++)
    {
        for (size_t y = 0; y < MATRIX_SIZE_3x3; y++)
        {
            conjugateMatrixLine[y] = GetConjugateMatrixElem(matrix, x, y);
        }
        conjugateMatrix[x] = conjugateMatrixLine;
    }
 
    return conjugateMatrix;
}

float GetDeterminant(const Matrix3x3& matrix)
{
    return (matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) + (matrix[0][2] * matrix[1][0] * matrix[2][1])
        - (matrix[0][2] * matrix[1][1] * matrix[2][0]) - (matrix[0][0] * matrix[1][2] * matrix[2][1]) - (matrix[0][1] * matrix[1][0] * matrix[2][2]);
}

Matrix3x3 MultiplyMatrixByNumber(Matrix3x3 &matrix, float number)
{
    for (auto& row : matrix)
    {
        for (auto& elem : row)
        {
            elem *= number;
        }
    }

    return matrix;
}

optional<Matrix3x3> GetInvertedMatrix(const Matrix3x3& matrix)
{
    float det = GetDeterminant(matrix);

    if (det == 0)
    {
        cout << "Ohhh no!! determinant is zero, so we cant fint inverted matrix\n";
        return nullopt;
    }

    Matrix3x3 transposedMatrix = GetTransposedMatrix(matrix);
    Matrix3x3 conjugateMatrix = GetConjugateMatrix(transposedMatrix);

    return MultiplyMatrixByNumber(conjugateMatrix, 1/det);
}
