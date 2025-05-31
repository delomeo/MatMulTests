#include <random>
#include <algorithm>
#include <vector>
#include <iostream>
#include "MatrixOps.h"
#include "GlobalConstants.h"

// Function to initialize a fixed-size matrix
void InitArray(float arr[SIZE][SIZE], int size, std::mt19937& rng, std::uniform_real_distribution<float>& dist, bool sparse = true) {
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            if (sparse) {
                // Use the random generator to decide sparsity
                arr[i][j] = (dist(rng) < 0.2f) ? dist(rng) : 0.0f; // 20% non-zero elements
            } else {
                arr[i][j] = dist(rng); // Fully dense matrix
            }
        }
    }
}

// Function to initialize a dynamically resizable matrix
void InitDynamicArray(std::vector<float>& mat, int rows, int cols, std::mt19937& rng, std::uniform_real_distribution<float>& dist, bool sparse = true) {
    mat.resize(rows * cols, 0.0f);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (sparse) {
                // Use the random generator to decide sparsity
                mat[i * cols + j] = (dist(rng) < 0.2f) ? dist(rng) : 0.0f; // 20% non-zero elements
            } else {
                mat[i * cols + j] = dist(rng); // Fully dense matrix
            }
        }
    }
}

// Function to perform matrix multiplication for fixed-size matrices
void MatrixMultiplication(float mat1[SIZE][SIZE], float mat2[SIZE][SIZE], float res[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            res[i][j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// Function to perform matrix multiplication for dynamically resizable matrices
void DynamicMatrixMultiplication(std::vector<float>& res, const std::vector<float>& mat1, const std::vector<float>& mat2, int rows, int shared, int cols) {
    res.resize(rows * cols, 0.0f);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < shared; ++k) {
                res[i * cols + j] += mat1[i * shared + k] * mat2[k * cols + j];
            }
        }
    }
}

// Function to print a dynamically resizable matrix
void PrintDynamicArray(const std::vector<float>& mat, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << mat[i * cols + j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename Matrix>
Matrix matmul(const Matrix& mat1, const Matrix& mat2){

    assert(mat1.cols() == mat2.rows()); // Ensure dimensions are compatible

    Matrix result(mat1.rows(), mat2.cols());
    for (int i = 0; i < mat1.rows(); ++i) {
        for (int j = 0; j < mat2.cols(); ++j) {
            result(i, j) = 0;
            for (int k = 0; k < mat1.cols(); ++k) {
                result(i, j) += mat1(i, k) * mat2(k, j);
            }
        }
    }
    return result;
}

std::array<std::array<float, SIZE>, SIZE> matmul(
    const float mat1[SIZE][SIZE],
    const float mat2[SIZE][SIZE]) {
    std::array<std::array<float, SIZE>, SIZE> result = {};
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

std::vector<float> matmul(const std::vector<float>& mat1, const std::vector<float>& mat2, int rows, int shared, int cols) {
    std::vector<float> result(rows * cols, 0.0f);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < shared; ++k) {
                result[i * cols + j] += mat1[i * shared + k] * mat2[k * cols + j];
            }
        }
    }
    return result;
}

Eigen::MatrixXd matmul(const Eigen::MatrixXd& mat1, const Eigen::MatrixXd& mat2) {
    return mat1 * mat2; // Use Eigen's built-in multiplication
}