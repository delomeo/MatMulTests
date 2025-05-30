#ifndef LOGGING_UTILS_H
#define LOGGING_UTILS_H

#include <vector>
#include <iostream>
# include <fstream>
#include <chrono>
#include <numeric>
#include "MatrixOps.h"
#include "GlobalConstants.h"


// Declare external functions
void MatrixMultiplication(float mat1[SIZE][SIZE], float mat2[SIZE][SIZE], float res[SIZE][SIZE]);
void DynamicMatrixMultiplication(std::vector<float>& res, const std::vector<float>& mat1, const std::vector<float>& mat2, int rows, int shared, int cols);

// Function declarations
void LogExecutionTimesFixedSize(float Mat1[SIZE][SIZE], float Mat2[SIZE][SIZE], float res[SIZE][SIZE], int iterations);
void LogExecutionTimesDynamic(std::vector<float>& dynamicMat1, std::vector<float>& dynamicMat2, std::vector<float>& resDynamic, int rows, int shared, int cols, int iterations);

// Logging utility functions
enum class logLevel {INFO, RESULT};
void LogMessage(std::ofstream& logStream, logLevel level, const std::string& message);

template <typename Func>
void LogExecutionTimes(const std::string& logFilePath, Func matrixOperation, int iterations, const std::string& matrixType) {
    std::ofstream logStream(logFilePath, std::ios::app); // Rename the local variable to logStream
    if (!logStream.is_open()) {
        throw std::runtime_error("Failed to open log file: " + logFilePath);
    }

    std::vector<long long> times;

    for (int i = 0; i < iterations; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        matrixOperation();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        times.push_back(duration);

        LogMessage(logStream, logLevel::INFO, "Iteration " + std::to_string(i + 1) + " (" + matrixType + "): " + std::to_string(duration) + " microseconds");
    }

    long long total = std::accumulate(times.begin(), times.end(), 0LL);
    LogMessage(logStream, logLevel::RESULT, "Average execution time (" + matrixType + "): " + std::to_string(total / iterations) + " microseconds");
}

#endif // LOGGING_UTILS_H