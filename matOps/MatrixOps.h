#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <vector>
#include <random>
#include "GlobalConstants.h"

void InitArray(float arr[SIZE][SIZE], int size, std::mt19937& rng, std::uniform_real_distribution<float>& dist, bool sparse);
void InitDynamicArray(std::vector<float>& mat, int rows, int cols, std::mt19937& rng, std::uniform_real_distribution<float>& dist, bool sparse);

// Function declarations for matrix operations
void MatrixMultiplication(float mat1[SIZE][SIZE], float mat2[SIZE][SIZE], float res[SIZE][SIZE]);
void DynamicMatrixMultiplication(std::vector<float>& res, const std::vector<float>& mat1, const std::vector<float>& mat2, int rows, int shared, int cols);

void PrintDynamicArray(const std::vector<float>& mat, int rows, int cols);
#endif // MATRIX_OPS_H