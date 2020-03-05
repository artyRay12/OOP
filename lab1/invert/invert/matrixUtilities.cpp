#include "matrixUtilities.h"
const float MATRIX_SIZE = 3;

void PrintMatrix(vector<vector<float>>& matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            cout << fixed << setprecision(3) << setw(10) <<  matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

vector<vector<float>> GetTransposedMatrix(vector<vector<float>> matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE - 1; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            if ((i != j) && (j > i))
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
    return matrix;
}

float CountAlgebraicAddition(vector<float> algExpr)
{
    return  algExpr[0] * algExpr[3] - algExpr[1] * algExpr[2];

}

float GetConjugateMatrixElem(vector<vector<float>>& matrix, size_t& line, size_t& col)
{
    vector<float> algExpr;
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            if ((i != line) && (j != col))
            {
                algExpr.push_back(matrix[i][j]);
            }
        }
    }
    
    return ((line + col + 2) % 2 == 0) ? CountAlgebraicAddition(algExpr) : -CountAlgebraicAddition(algExpr);

}

vector<vector<float>> GetConjugateMatirx(vector<vector<float>>& matrix)
{
    vector<float> addMatrixLine;
    vector<vector<float>> addMatrix;

    for (size_t x = 0; x < MATRIX_SIZE; x++)
    {
        for (size_t y = 0; y < MATRIX_SIZE; y++)
        {
            addMatrixLine.push_back(GetConjugateMatrixElem(matrix, x, y));
        }
        addMatrix.push_back(addMatrixLine);
        addMatrixLine.clear();
    }
       
    return addMatrix;
}

float GetDeterminant(vector<vector<float>>& matrix)
{
    return (matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) + (matrix[0][2] * matrix[1][0] * matrix[2][1])
        - (matrix[0][2] * matrix[1][1] * matrix[2][0]) - (matrix[0][0] * matrix[1][2] * matrix[2][1]) - (matrix[0][1] * matrix[1][0] * matrix[2][2]);
}


vector<vector<float>> Invert(vector<vector<float>>& matrix, float det)
{
    vector<float> inventedMatrixLine;
    vector<vector<float>> inventedMatrix;
    for (size_t x = 0; x < MATRIX_SIZE; x++)
    {
        for (size_t y = 0; y < MATRIX_SIZE; y++)
        {
            inventedMatrixLine.push_back(static_cast<float>(matrix[x][y]) * (static_cast<float>(1) / det));
        }
        inventedMatrix.push_back(inventedMatrixLine);
        inventedMatrixLine.clear();
    }

    return inventedMatrix;
}


optional<vector<vector<float>>> InvertMatrix(vector<vector<float>>& matrix)
{
    float det = GetDeterminant(matrix);
    if (det == 0)
    {
        cout << "Ohh no, determinant is '0' so we can't invert this matrix" << endl;
        return nullopt;
    }

    vector<vector<float>> transposedMatrix = GetTransposedMatrix(matrix);
    vector<vector<float>> conjugateMatrix= GetConjugateMatirx(transposedMatrix);

    return Invert(conjugateMatrix, det);
}
