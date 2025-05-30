#include <iostream>
#include <fstream>
#include <chrono>
#include <numeric>
#include "MatrixOps.h"
#include "LoggingUtils.h"

void LogMessage(std::ofstream& logStream, logLevel level, const std::string& message) {
    switch (level){
        case logLevel::INFO: logStream << "[INFO] "; break;
        case logLevel::RESULT: logStream << "[RESULT] "; break;
    }
    logStream << message << std::endl; //This should append the message after the flag logLeve
}

void LogExecutionTimesFixedSize(float Mat1[SIZE][SIZE], float Mat2[SIZE][SIZE], float res[SIZE][SIZE], int iterations) {
    auto operation = [&]() { MatrixMultiplication(Mat1, Mat2, res); };
    LogExecutionTimes("log/execution_times.log", operation, iterations, "fixed-size");
}

void LogExecutionTimesDynamic(std::vector<float>& dynamicMat1, std::vector<float>& dynamicMat2, std::vector<float>& resDynamic, int rows, int shared, int cols, int iterations) {
    auto operation = [&]() { DynamicMatrixMultiplication(resDynamic, dynamicMat1, dynamicMat2, rows, shared, cols); };
    LogExecutionTimes("log/execution_times.log", operation, iterations, "dynamic");
}