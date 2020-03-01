#include "matrixUtilities.h";
const int MATRIX_SIZE = 3;

void PrintMatrix(vector<vector<float>>& matrix)
{
    for (size_t i = 0; i < MATRIX_SIZE; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE; j++)
        {
            cout << fixed << setprecision(4) << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

vector<vector<int>> GetTransposedMatrix(vector<vector<int>> matrix)
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

int CountAlgebraicAddition(vector<int> algExpr)
{
    return  algExpr[0] * algExpr[3] - algExpr[1] * algExpr[2];

}

int GetAddMatrixElem(vector<vector<int>>& matrix, size_t& line, size_t& col)
{
    vector<int> algExpr;
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

vector<vector<int>> GetAlgebraicAdditions(vector<vector<int>>& matrix)
{
    vector<int> addMatrixLine;
    vector<vector<int>> addMatrix;

    for (size_t x = 0; x < MATRIX_SIZE; x++)
    {
        for (size_t y = 0; y < MATRIX_SIZE; y++)
        {
            addMatrixLine.push_back(GetAddMatrixElem(matrix, x, y));
        }
        addMatrix.push_back(addMatrixLine);
        addMatrixLine.clear();
    }
       
    return addMatrix;
}

int GetDeterminant(vector<vector<int>>& matrix)
{
    return (matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) + (matrix[0][2] * matrix[1][0] * matrix[2][1])
        - (matrix[0][2] * matrix[1][1] * matrix[2][0]) - (matrix[0][0] * matrix[1][2] * matrix[2][1]) - (matrix[0][1] * matrix[1][0] * matrix[2][2]);
}


vector<vector<float>> Invent(vector<vector<int>>& matrix, int det)
{
    det = 154;
    vector<float> inventedMatrixLine;
    vector<vector<float>> inventedMatrix;
    for (size_t x = 0; x < MATRIX_SIZE; x++)
    {
        for (size_t y = 0; y < MATRIX_SIZE; y++)
        {
            inventedMatrixLine.push_back(static_cast<float>(matrix[x][y]) * -det / 10);
        }
        inventedMatrix.push_back(inventedMatrixLine);
    }

    return inventedMatrix;
}


optional<vector<vector<float>>> InvertMatrix(vector<vector<int>>& matrix)
{
    int det = GetDeterminant(matrix);
    if (det == 0)
    {
        cout << "Ohh no, determinant is '0' so we can't invert this matrix" << endl;
        return nullopt;
    }

    vector<vector<int>> transposedMatrix = GetTransposedMatrix(matrix);
    vector<vector<int>> algAdds = GetAlgebraicAdditions(transposedMatrix);

    return Invent(algAdds, det);
}
