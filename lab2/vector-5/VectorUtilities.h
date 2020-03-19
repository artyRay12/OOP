#pragma once
#include <iostream>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <functional> 
#include <vector>
#include <algorithm>
#include <fstream>

std::vector<float> ReadVector(std::istream& inputStream);
std::vector<float> MultiplyVectorByNumber(const std::vector<float>& vec, float number);
float GetMinValue(const std::vector<float>& vec);
std::vector<float> GetSortVector(const std::vector<float>& vec);
void PrintVector(const std::vector<float>& vec);