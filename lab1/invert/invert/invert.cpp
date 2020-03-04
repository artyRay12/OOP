#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
#include <cfloat>
#include <cmath>
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
        cout << err.what() << endl;;
        return false;
    }

    if (pos != str.length())
    {
        return false;
    }

    return true;
}

optional<vector<float>> ParseLine(string& line)
{
    stringstream lineStream(line);
    string elem;
    vector<float> matrixLine;

    while (getline(lineStream, elem, ' '))
    {
        if (!isNumber(elem))
        {
            cout << "Error!\nWrong elem matrix plase use numbers!\n";
            return nullopt;
        }
        matrixLine.push_back(stof(elem));
    }

    return matrixLine;
}


optional<vector<vector<float>>> getMatrix(ifstream& input)
{
    vector<vector<float>> matrix;
    string line;

    while (getline(input, line))
    {
        auto parsedLine = ParseLine(line);
        if (!parsedLine)
        {
            return nullopt;
        }

        if ((parsedLine.value().size() != 3) || (matrix.size() != 3))
        {
            cout << "Error\nYour matrix is not 3x3\nPlease use 3x3 matrix\n";
            return nullopt;
        }

        matrix.push_back(parsedLine.value());
    }

    return matrix;
}

optional<vector<vector<float>>> GetMatrixFromFile(const string& inputFileName)
{
    ifstream input(inputFileName);

    if (!input.is_open())
    {
        cout << "Error!\n Can't open file\n";
        return nullopt;
    }

    return getMatrix(input);
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