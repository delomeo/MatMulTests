#include <iostream>
#include <fstream>
#include <chrono>
#include <numeric>
#include "MatrixOps.h"
#include "LoggingUtils.h"

void LogMessage(std::ofstream& logStream, const LogMessageObj& log) {
    if (!logStream.is_open()) {
        throw std::runtime_error("Log stream is not open");
    }

    // Convert high_resolution_clock to system_clock
    auto systemTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        log.timestamp - std::chrono::high_resolution_clock::now() + std::chrono::system_clock::now()
    );

    // Format the timestamp
    auto time = std::chrono::system_clock::to_time_t(systemTime);
    std::string timeStr = std::ctime(&time);
    timeStr.pop_back(); // Remove the newline character added by ctime

    // Convert logLevel to string
    std::string levelStr;
    switch (log.status) {
        case logLevel::INFO: levelStr = "INFO"; break;
        case logLevel::RESULT: levelStr = "RESULT"; break;
        case logLevel::NONE: levelStr = "NONE"; break;
        default: levelStr = "UNKNOWN"; break;
    }

    // Write the formatted log message to the stream
    logStream << "{" << timeStr << "} [" << levelStr << "] " << log.message << std::endl;
}

void LogExecutionTimesFixedSize(float Mat1[SIZE][SIZE], float Mat2[SIZE][SIZE], float res[SIZE][SIZE], int iterations) {
    auto operation = [&]() { MatrixMultiplication(Mat1, Mat2, res); };

    // Use LogMessageObj for logging
    std::ofstream logStream("log/execution_times.log", std::ios::app);
    if (!logStream.is_open()) {
        throw std::runtime_error("Failed to open log file: log/execution_times.log");
    }

    LogMessageObj startLog(logLevel::INFO, "Starting fixed-size matrix multiplication logging.");
    LogMessage(logStream, startLog);

    LogExecutionTimes("log/execution_times.log", operation, iterations, "fixed-size");

    LogMessageObj endLog(logLevel::INFO, "Finished fixed-size matrix multiplication logging.");
    LogMessage(logStream, endLog);
}

void LogExecutionTimesDynamic(std::vector<float>& dynamicMat1, std::vector<float>& dynamicMat2, std::vector<float>& resDynamic, int rows, int shared, int cols, int iterations) {
    auto operation = [&]() { DynamicMatrixMultiplication(resDynamic, dynamicMat1, dynamicMat2, rows, shared, cols); };

    // Use LogMessageObj for logging
    std::ofstream logStream("log/execution_times.log", std::ios::app);
    if (!logStream.is_open()) {
        throw std::runtime_error("Failed to open log file: log/execution_times.log");
    }

    LogMessageObj startLog(logLevel::INFO, "Starting dynamic matrix multiplication logging.");
    LogMessage(logStream, startLog);

    LogExecutionTimes("log/execution_times.log", operation, iterations, "dynamic");

    LogMessageObj endLog(logLevel::INFO, "Finished dynamic matrix multiplication logging.");
    LogMessage(logStream, endLog);
}