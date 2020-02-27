#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<int>> getMatrix(ifstream &inputFile)
{
    vector<vector<int>> outVector;
    string str, newStr;
    

    while (getline(inputFile, str, ' '))
    {
        stringstream strStream(str);
        while (getline(strStream, newStr , ' '))
        {
            outVector.push_back(stoi(newStr));
        }

        for (size_t i = 0; i < outVector.size(); i++)
        {
            for (size_t j = 0; j < outVector[i].size(); j++)
            {
                outVector[i][j].push_back(newStr);
                break;
            }
        }
    }
    return outVector;
}

int main(int argc, char* argv[])
{
    vector<vector<int>> matrix;

    ifstream input;
    input.open(argv[1]);
    ofstream output;

    martrix = getMatrix(input)

    
}
