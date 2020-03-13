#pragma once
#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <cfloat>
#include "invert.h"

void PrintMatrix(const Matrix3x3& matrix);
std::optional<Matrix3x3> GetInvertedMatrix(const Matrix3x3& matrix);

