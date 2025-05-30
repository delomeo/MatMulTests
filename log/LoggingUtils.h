#ifndef LOGGING_UTILS_H
#define LOGGING_UTILS_H

#include <vector>
#include <iostream>
# include <fstream>
#include <chrono>
#include <numeric>
#include "MatrixOps.h"
#include "GlobalConstants.h"

struct LogMessageObj{
    std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;
    logLevel status;
    std::string message;

    LogMessageObj(logLevel level, const std::string& msg)
        : timestamp(std::chrono::high_resolution_clock::now()), status(level), message(msg) {}
};

// Declare external functions
void MatrixMultiplication(float mat1[SIZE][SIZE], float mat2[SIZE][SIZE], float res[SIZE][SIZE]);
void DynamicMatrixMultiplication(std::vector<float>& res, const std::vector<float>& mat1, const std::vector<float>& mat2, int rows, int shared, int cols);

// Function declarations
void LogExecutionTimesFixedSize(float Mat1[SIZE][SIZE], float Mat2[SIZE][SIZE], float res[SIZE][SIZE], int iterations);
void LogExecutionTimesDynamic(std::vector<float>& dynamicMat1, std::vector<float>& dynamicMat2, std::vector<float>& resDynamic, int rows, int shared, int cols, int iterations);

// Logging utility functions
enum class logLevel {INFO, RESULT, NONE};
void LogMessage(std::ofstream& logStream, const LogMessageObj& log);

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
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        times.push_back(duration);

        // Create a LogMessageObj for each iteration
        LogMessageObj log(logLevel::INFO, "Iteration " + std::to_string(i + 1) + " (" + matrixType + "): " + std::to_string(duration) + " nanoseconds");
        LogMessage(logStream, log);
    }

    long long total = std::accumulate(times.begin(), times.end(), 0LL);
    LogMessageObj resultLog(logLevel::RESULT, "Average execution time (" + matrixType + "): " + std::to_string(total / iterations) + " nanoseconds");
}

#endif // LOGGING_UTILS_H