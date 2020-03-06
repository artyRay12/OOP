#include "matrixUtilities.h"
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <cfloat>
#include <iomanip>
#include <cmath>
using namespace std;

void PrintMatrix(const Matrix3x3& matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE_3x3; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_3x3; j++)
        {
            cout << fixed << setprecision(3) << setw(10) <<  matrix[i][j] << "  ";
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

float CountAlgebraicAddition(Matrix2x2 algExpr)
{
    return  algExpr[0] * algExpr[3] - algExpr[1] * algExpr[2];

}

float GetConjugateMatrixElem(const Matrix3x3& matrix, size_t line, size_t col)
{
    Matrix2x2 algExpr;
    for (size_t i = 0; i < MATRIX_SIZE_2x2; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_2x2; j++)
        {
            if ((i != line) && (j != col))
            {
                algExpr.push_back(matrix[i][j]);
            }
        }
    }
    
    return ((line + col) % 2 == 0) ? CountAlgebraicAddition(algExpr) : -CountAlgebraicAddition(algExpr);

}

Matrix3x3 GetConjugateMatrix(const Matrix3x3& matrix)
{

    Matrix3x3Line conjugateMatrixLine;
    Matrix3x3 conjugateMatrix;

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

float GetDeterminant(Matrix3x3& matrix)
{
    return (matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) + (matrix[0][2] * matrix[1][0] * matrix[2][1])
        - (matrix[0][2] * matrix[1][1] * matrix[2][0]) - (matrix[0][0] * matrix[1][2] * matrix[2][1]) - (matrix[0][1] * matrix[1][0] * matrix[2][2]);
}


Matrix3x3 Invert(Matrix3x3& matrix, float det)
{
    Matrix3x3Line inventedMatrixLine;
    Matrix3x3 inventedMatrix;
    for (size_t x = 0; x < MATRIX_SIZE_3x3; x++)
    {
        for (size_t y = 0; y < MATRIX_SIZE_3x3; y++)
        {
            inventedMatrixLine[y] = static_cast<float>(matrix[x][y]) * (static_cast<float>(1) / det);
        }
        inventedMatrix[x] = inventedMatrixLine;
    }

    return inventedMatrix;
}


optional<Matrix3x3> InvertMatrix(Matrix3x3& matrix)
{
    float det = GetDeterminant(matrix);
    if (det == 0)
    {
        cout << "Ohh no, determinant is '0' so we can't invert this matrix" << endl;
        return nullopt;
    }

    Matrix3x3 transposedMatrix = GetTransposedMatrix(matrix);
    Matrix3x3 conjugateMatrix = GetConjugateMatrix(transposedMatrix);    
    return Invert(conjugateMatrix, det);
}
