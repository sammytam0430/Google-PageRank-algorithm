//
// Created by sammy on 2019-10-04.
//

#ifndef ASSIGNMENT1_MATRIX_HPP
#define ASSIGNMENT1_MATRIX_HPP

#include <ostream>

using namespace std;

class Matrix {
private:
    vector<vector<double>> matrix;
    int row = 0;
    int col = 0;
public:
    Matrix();
    Matrix(int n);
    Matrix(int r, int c);
    Matrix(vector<double> v);
    void set_value(int r, int c, double val);
    double get_value(int r, int c);
    void clear();
    ~Matrix();
    friend ostream& operator<<(ostream& os, const Matrix& matrix);
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
    Matrix& operator++();
    Matrix operator++(int);
    Matrix& operator--();
    Matrix operator--(int);
    Matrix& operator=(Matrix rhs);
    void matrixSwap(Matrix& lhs, Matrix& rhs);
    Matrix& operator+=(const Matrix& rhs);
    friend Matrix operator+(Matrix lhs, Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    friend Matrix operator-(Matrix lhs, Matrix& rhs);
    Matrix& operator*=(const Matrix& rhs);
    friend Matrix operator*(Matrix lhs, Matrix& rhs);
};

#endif //ASSIGNMENT1_MATRIX_HPP
