#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <array>
#include <random>

#include "LoggingUtils.h"
#include "MatrixOps.h"
#include "GlobalConstants.h"

using namespace std;

int main() {
    mt19937 rng(SEED); // Seed the random number generator
    uniform_real_distribution<float> dist(0.0f, 1.0f);
    cout << "Matrix multiplication benchmark started." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Number of cycles: " << CYCLES << endl;
    cout << "Size of matrices: " << SIZE << endl;
    cout << "Sparsity: " << (SPARSITY ? "Enabled" : "Disabled") << endl;
    cout << "Seed: " << SEED << endl;
    cout << "----------------------------------------" << endl;

    for(int i=0; i<CYCLES; ++i){
        // Fixed-size matrices
        float Mat1[SIZE][SIZE];
        float Mat2[SIZE][SIZE];
        float res[SIZE][SIZE];

        // Initialize fixed-size matrices with sparsity
        InitArray(Mat1, SIZE, rng, dist, SPARSITY);
        InitArray(Mat2, SIZE, rng, dist, SPARSITY);
        
        LogExecutionTimesFixedSize(Mat1, Mat2, res, CYCLES);
        // Dynamically resizable matrices
        vector<float> dynamicMat1;
        vector<float> dynamicMat2;
        vector<float> resDynamic;

        // Re-seed the random generator to ensure the same values
        rng.seed(SEED);

        // Initialize dynamically resizable matrices with sparsity
        InitDynamicArray(dynamicMat1, SIZE, SIZE, rng, dist, SPARSITY);
        InitDynamicArray(dynamicMat2, SIZE, SIZE, rng, dist, SPARSITY);

        LogExecutionTimesDynamic(dynamicMat1, dynamicMat2, resDynamic, SIZE, SIZE, SIZE, CYCLES);
        
    }
    cout << "Matrix multiplication benchmark completed." << endl;
    cout << "----------------------------------------" << endl;
    return 0;
}