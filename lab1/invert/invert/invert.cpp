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
        cout << err.what() << "\nError! You should use only numbers in your 3x3 matrix.\nString example <number><space><number><space><number>" << endl;
        return false;
    }

    if (pos != str.length())
    {
        cout << "Error!\n Some number in yout matrix have letter instead digits\n";
        return false;
    }

    return true;
}

optional<Matrix3x3Line> ParseLine(string& line)
{
    stringstream lineStream(line);
    string elem;
    Matrix3x3Line matrixLine;
    int matrixLineIndex = 0;

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
        matrixLine[matrixLineIndex] = stof(elem);
        if (matrixLineIndex < MATRIX_SIZE_3x3)
        {
            matrixLineIndex++;
        }
        else
        {
            cout << "Error!\n Your matrix not 3x3\n";
            return nullopt;
        }
    }
    return matrixLine;
}


optional<Matrix3x3> GetMatrix(ifstream& input)
{
    Matrix3x3 matrix;
    string line;
    int lineIndex = 0;

    while (getline(input, line))
    {
        auto parsedLine = ParseLine(line);

        if (!parsedLine)
        {
            return nullopt;
        }

        matrix[lineIndex] = parsedLine.value();

        if (lineIndex < MATRIX_SIZE_3x3)
        {
            lineIndex++;
        }
        else
        {
            cout << "Ur matrix is not 3x3";
            return nullopt;
        }
        
    }

    if (matrix.empty())
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

optional<string> ParseArgs(int argc, char* argv[])
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
    auto inputFileName = ParseArgs(argc, argv);
    if (!inputFileName)
    {
        return 1;
    }

    auto matrix = GetMatrixFromFile(inputFileName.value());
    if (!matrix)
    {
        return 1;
    }

    auto invertedMatrix = InvertMatrix(matrix.value());
    if (!invertedMatrix)
    {
        return 1;
    }

    PrintMatrix(invertedMatrix.value());

    return 0;

}