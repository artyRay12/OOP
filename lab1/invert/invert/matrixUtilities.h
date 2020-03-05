#pragma once
#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>
#include <cfloat>
#include <iomanip>
#include <cmath>
using namespace std;

void PrintMatrix(vector<vector<float>>& matrix);
vector<vector<float>> GetTransposedMatrix(vector<vector<float>> matrix);
vector<vector<float>> GetConjugateMatirx(vector<vector<float>>& matrix);
float GetDeterminant(vector<vector<float>>& matrix);
optional<vector<vector<float>>> InvertMatrix(vector<vector<float>>& matrix);
float CountAlgebraicAddition(vector<float> algExp);

