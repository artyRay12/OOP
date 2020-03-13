#pragma once
#include <array>
#include <vector>

constexpr int MATRIX_SIZE_3x3 = 3;
constexpr int MATRIX_SIZE_2x2 = 2;
using Matrix3x3Row = std::array<float, MATRIX_SIZE_3x3>;
using Matrix3x3 = std::array<Matrix3x3Row, MATRIX_SIZE_3x3>;
using Matrix2x2 = std::array<std::array<float, MATRIX_SIZE_2x2>, MATRIX_SIZE_2x2>;
