#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <optional>
#include <fstream>
#include <functional> 
#include <algorithm>

std::vector<float> ReadVector(std::istream& inputStream);
void MultiplyVectorByNumber(std::vector<float>& vec, std::optional<float> number);
std::optional<float> GetMinValue(const std::vector<float>& vec);
void GetSortVector(std::vector<float>& vec);
void PrintVector(const std::vector<float>& vec);