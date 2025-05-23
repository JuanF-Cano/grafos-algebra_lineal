#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include <vector>
#include <iostream>

using namespace std;

// Computes the dot product of two vectors
int dotProduct(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) {
        cerr << "Error: Vectors must be the same length for dot product." << endl;
        return 0;
    }
    int result = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

// Computes the transpose of a matrix
vector<vector<int>> transpose(const vector<vector<int>>& matrix) {
    if (matrix.empty()) return {};
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> transposed(cols, vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

// Multiplies two square matrices using dot product and transposition
vector<vector<int>> matrixMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    vector<vector<int>> B_T = transpose(B);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = dotProduct(A[i], B_T[j]);
        }
    }
    return result;
}

// Prints a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

#endif // MATRIX_UTILS_H