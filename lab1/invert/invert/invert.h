#pragma once
#include <array>
#include <vector>

constexpr int MATRIX_SIZE_3x3 = 3;
constexpr int MATRIX_SIZE_2x2 = 3;
using Matrix3x3Line = std::array<float, MATRIX_SIZE_3x3>;
using Matrix3x3 = std::array<Matrix3x3Line, MATRIX_SIZE_3x3>;
using Matrix2x2 = std::vector<float>;
