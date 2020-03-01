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
vector<vector<int>> GetTransposedMatrix(vector<vector<int>> matrix);
vector<vector<int>> GetAlgebraicAdditions(vector<vector<int>>& matrix);
int GetDeterminant(vector<vector<int>>& matrix);
optional<vector<vector<float>>> InvertMatrix(vector<vector<int>>& matrix);
int CountAlgebraicAddition(vector<int> algExp);

