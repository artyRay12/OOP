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

template<typename T> 
void PushLineInMatrix(Matrix3x3& matrix, const T& matrixLine, size_t rowNumber)
{
    for (size_t i = 0; i < MATRIX_SIZE_3x3; i++)
    {
        matrix[rowNumber - 1][i] = matrixLine[i];
    }
}

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
        cout << "Error!\n Some number in yout matrix have letter instead digits\n";
        return false;
    }

    return true;
}


optional<vector<float>> getMatrixLine(string& line)
{
    stringstream lineStream(line);
    string elem;
    vector<float> matrixLine;

    if (line.empty())
    {
        cout << "Error!\nRemove empty lines from ur file!\n";
        return nullopt;
    }

    while (getline(lineStream, elem, ' '))
    {
        if (!isNumber(elem))
        {
            return nullopt;
        }

        matrixLine.push_back(stof(elem)); 
    }

    return matrixLine;
}

optional<Matrix3x3> GetMatrix(ifstream& input)
{
    Matrix3x3 matrix;
    string line;
    size_t lineIndex = 1;

    while (getline(input, line))
    {
        auto matrixLine = getMatrixLine(line);

        if (!matrixLine)
        {
            return nullopt;
        }

        if ((lineIndex > MATRIX_SIZE_3x3) || (matrixLine.value().size() != MATRIX_SIZE_3x3))
        {
            cout << "Ur matrix is not 3x3";
            return nullopt;
        }

        PushLineInMatrix(matrix, matrixLine.value(), lineIndex);
        lineIndex++;
    }

    if (matrix[0].empty())
    {
        cout << "Error!\nFile is empty! Please put matrix 3x3 in ur file\n";
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