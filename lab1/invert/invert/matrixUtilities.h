#pragma once
#include <iostream>
#include <fstream>
#include <optional>
#include <vector>
#include <cfloat>
#include "invert.h"

void PrintMatrix(const Matrix3x3& matrix);
Matrix3x3 GetTransposedMatrix(Matrix3x3 matrix);
Matrix3x3 GetConjugateMatrix(const Matrix3x3& matrix);
float GetDeterminant(const Matrix3x3& matrix);
std::optional<Matrix3x3> GetInvertedMatrix(const Matrix3x3& matrix);
float CountConjugateMatrixElem(const Matrix2x2 &algExp);

