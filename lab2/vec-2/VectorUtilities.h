#pragma once
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

std::vector<float> ReadVector(std::istream& inputStream);
void MultiplyVectorByNumber(std::vector<float>& vec, std::optional<float> number);
std::optional<float> GetMinValue(const std::vector<float>& vec);
void SortVector(std::vector<float>& vec);
void PrintVector(const std::vector<float>& vec);