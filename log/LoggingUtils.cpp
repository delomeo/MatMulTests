#include <iostream>
#include <cstring>
#include <fstream>
#include <chrono>
#include <numeric>
#include "MatrixOps.h"
#include "LoggingUtils.h"
#include <Eigen/Dense>

using Eigen::MatrixXd;

void LogMessage(std::ofstream& logStream, const LogMessageObj& log) {
    if (!logStream.is_open()) {
        throw std::runtime_error("Log stream is not open");
    }

    char formattedTime[100];
    // Format the timestamp
    auto now = std::chrono::high_resolution_clock::time_point(log.timestamp);
    auto timeT = std::chrono::high_resolution_clock::to_time_t(now);
    std::strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S:", std::localtime(&timeT));

    // Add milliseconds to the formatted time
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    snprintf(formattedTime + strlen(formattedTime), sizeof(formattedTime) - strlen(formattedTime), "%03lld", milliseconds.count());
    // Ensure the formatted time is null-terminated
    formattedTime[sizeof(formattedTime) - 1] = '\0';

    // Convert logLevel to string
    std::string levelStr;
    switch (log.status) {
        case logLevel::INFO: levelStr = "INFO"; break;
        case logLevel::RESULT: levelStr = "RESULT"; break;
        case logLevel::NONE: levelStr = "NONE"; break;
        default: levelStr = "UNKNOWN"; break;
    }

    // Write the formatted log message to the stream
    logStream << formattedTime << " [" << levelStr << "] " << log.message << std::endl;
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
    LogMessage(logStream, LogMessageObj(logLevel::NONE, "----------------------------------------"));
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
    LogMessage(logStream, LogMessageObj(logLevel::NONE, "----------------------------------------"));
}

void LogExecutionTimesEigen(const Eigen::MatrixXd& mat1, const Eigen::MatrixXd& mat2, Eigen::MatrixXd& resEigen, int iterations) {
    auto operation = [&]() { resEigen = mat1 * mat2; };

    // Use LogMessageObj for logging
    std::ofstream logStream("log/execution_times.log", std::ios::app);
    if (!logStream.is_open()) {
        throw std::runtime_error("Failed to open log file: log/execution_times.log");
    }

    LogMessageObj startLog(logLevel::INFO, "Starting Eigen matrix multiplication logging.");
    LogMessage(logStream, startLog);

    LogExecutionTimes("log/execution_times.log", operation, iterations, "Eigen");

    LogMessageObj endLog(logLevel::INFO, "Finished Eigen matrix multiplication logging.");
    LogMessage(logStream, endLog);
    LogMessage(logStream, LogMessageObj(logLevel::NONE, "----------------------------------------"));
}
        