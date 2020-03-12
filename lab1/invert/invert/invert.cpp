#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
#include <cfloat>
#include <cmath>
#include <array>
#include "invert.h"
#include "matrixUtilities.h"

using namespace std; 

bool isNumber(const string& str)
{
    size_t pos = 0;

    try
    {
        stof(str, &pos);
    }
    catch (const exception & err)
    {
        cout << err.what() << "\nError! You should use only number and one space between them.\nString example: <number><space><number><space><number><end of line>" << endl;
        return false;
    }

    if (pos != str.length())
    {
        cout << "Error!\nSome number in yout matrix have letter instead digits\n";
        return false;
    }

    return true;
}

optional<Matrix3x3Row> ParseMatrixRow(string& row)
{
    stringstream rowStream(row);
    string elem;
    size_t elemIndex = 0;
    Matrix3x3Row matrixRow;

    if (row.empty())
    {
        cout << "Error!\nRemove empty rows from ur file!\n";
        return nullopt;
    }

    while (getline(rowStream, elem, ' '))
    {
        if (!isNumber(elem))
        {
            return nullopt;
        }

        if (elemIndex + 1 > MATRIX_SIZE_3x3)
        {
            cout << "Ur matrix is not 3x3";
            return nullopt;
        }

        matrixRow[elemIndex] = (stof(elem));
        elemIndex++;
    }

    if (elemIndex < MATRIX_SIZE_3x3)
    {
        cout << "Ur matrix is not 3x3";
        return nullopt;
    }

    return matrixRow;
}

optional<Matrix3x3> GetMatrix(istream& input)
{
    Matrix3x3 matrix;
    string row;
    size_t rowIndex = 0;

    while (getline(input, row))
    {
        auto matrixRow = ParseMatrixRow(row);
        if (!matrixRow)
        {
            return nullopt;
        }

        if (rowIndex + 1> MATRIX_SIZE_3x3)
        {
            cout << "Ur matrix is not 3x3";
            return nullopt;
        }

        matrix[rowIndex] = matrixRow.value();
        rowIndex++;
    }

    if (rowIndex != MATRIX_SIZE_3x3)
    {
        cout << "Ur matrix is not 3x3";
        return nullopt;
    }

    return matrix;
}

optional<Matrix3x3> GetMatrixFromFile(const string& inputFileName)
{
    ifstream input(inputFileName);

    if (!input.is_open())
    {
        cout << "Error!\n Can't open file\n";
        return nullopt;
    }

    if (input.peek() == EOF)
    {
        cout << "Error!\nYour file is empty!\n";
        return nullopt;
    }

    return GetMatrix(input);
}

optional<string> getInputFileName(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Error!\nUsage: invert.exe <file.txt> \n";
        return nullopt;
    }

    return argv[1];
}


int main(int argc, char* argv[])
{
    auto inputFileName = getInputFileName(argc, argv);
    if (!inputFileName)
    {
        return 1;
    }

    auto matrix = GetMatrixFromFile(inputFileName.value());
    if (!matrix)
    {
        return 1;
    }

    auto invertedMatrix = GetInvertedMatrix(matrix.value());
    if (!invertedMatrix)
    {
        return 1;
    }

    PrintMatrix(invertedMatrix.value());

    return 0;
}