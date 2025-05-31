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
// Generalized matrix multiplication using templates
template <typename Matrix>
Matrix matmul(const Matrix& mat1, const Matrix& mat2);

std::array<std::array<float, SIZE>, SIZE> matmul(
    const float mat1[SIZE][SIZE],
    const float mat2[SIZE][SIZE]);
    
// Overloading for std::vector<float>
std::vector<float> matmul(const std::vector<float>& mat1, const std::vector<float>& mat2, int rows, int shared, int cols);

// Overloading for Eigen matrices
Eigen::MatrixXd matmul(const Eigen::MatrixXd& mat1, const Eigen::MatrixXd& mat2);

#endif // MATRIX_OPS_H