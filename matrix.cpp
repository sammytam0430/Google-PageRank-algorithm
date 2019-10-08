//
// Created by sammy on 2019-10-04.
//

#include <vector>
#include <cmath>
#include <stdexcept>
#include "matrix.hpp"

Matrix::Matrix() {
    row = 1;
    col = 1;
    matrix.resize(row, vector<double>(col, 0.0));
}

Matrix::Matrix(int n) {
    if (n < 1)
        throw invalid_argument("Size cannot be 0 or negative");
    row = col = n;
    matrix.resize(row, vector<double>(col, 0.0));
}

Matrix::Matrix(int r, int c) {
    if (r < 1 || c < 1)
        throw invalid_argument("Size cannot be 0 or negative");
    row = r;
    col = c;
    matrix.resize(row, vector<double>(col, 0.0));
}

Matrix::Matrix(vector<double> v) {
    if (pow((int) sqrt(v.size()), 2) != v.size())
        throw invalid_argument("The size of vector is not a perfect square");
    row = col = floor(sqrt(v.size()));
    matrix.resize(row, vector<double>(col, 0.0));
    for (int r = 0; r < row; ++r) {
        for (int c = 0; c < col; ++c) {
            matrix[r][c] = v[r * row + c];
        }
    }
}

void Matrix::set_value(int r, int c, double val) {
    if (r < 0 || c < 0)
        throw invalid_argument("Index cannot be negative");
    if (r >= row || c >= col)
        throw invalid_argument("Index out of bound");
    matrix[r][c] = val;
}

double Matrix::get_value(int r, int c) {
    if (r < 0 || c < 0)
        throw invalid_argument("Index cannot be negative");
    if (r >= row || c >= col)
        throw invalid_argument("Index out of bound");
    return matrix[r][c];
}

void Matrix::clear() {
    matrix.resize(row, vector<double>(col, 0.0));
}

Matrix::~Matrix(){}

ostream& operator<<(ostream& os, const Matrix& obj) {
    for (int r = 0; r < obj.row; ++r) {
        for (int c = 0; c < obj.col; ++c)
            os << obj.matrix[r][c] << "\t";
        os << endl;
    }
    return os;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
    if(lhs.row != rhs.row && lhs.col != rhs.col)
        return false;
    for (int r = 0; r < lhs.row ; ++r)
        for (int c = 0; c < lhs.col; ++c)
            if (lhs.matrix[r][c] - rhs.matrix[r][c] > 0.01)
                return false;
    return true;
}

bool operator!=(const Matrix &lhs, const Matrix &rhs) {
    return !(lhs == rhs);
}

Matrix &Matrix::operator++() {
    for (int r = 0; r < row; ++r)
        for (int c = 0; c < col; ++c)
            matrix[r][c] += 1;
    return *this;
}

Matrix Matrix::operator++(int) {
    Matrix tmp(*this);
    operator++();
    return tmp;
}

Matrix &Matrix::operator--() {
    for (int r = 0; r < row; ++r)
        for (int c = 0; c < col; ++c)
            matrix[r][c] -= 1;
    return *this;
}

Matrix Matrix::operator--(int) {
    Matrix tmp(*this);
    operator--();
    return tmp;
}

Matrix& Matrix::operator=(Matrix rhs) {
    matrixSwap(*this, rhs);
    return *this;
}

void Matrix::matrixSwap(Matrix& lhs, Matrix& rhs) {
//    lhs.matrix.resize(rhs.row, vector<double>(rhs.col, 0));
    for (int r = 0; r < lhs.row; ++r)
        for (int c = 0; c < lhs.col; ++c)
            lhs.matrix[r][c] = rhs.matrix[r][c];
}

Matrix& Matrix::operator+=(const Matrix &rhs) {
    if(this->row != rhs.row && this->col != rhs.col)
        throw invalid_argument("Two Matrices must be the same size");
    for (int r = 0; r < this->row; ++r)
        for (int c = 0; c < this->col; ++c)
            this->matrix[r][c] += rhs.matrix[r][c];
    return *this;
}

Matrix operator+(Matrix lhs, Matrix &rhs) {
    lhs += rhs;
    return lhs;
}

Matrix& Matrix::operator-=(const Matrix &rhs) {
    if(this->row != rhs.row && this->col != rhs.col)
        throw invalid_argument("Two Matrices must be the same size");
    for (int r = 0; r < this->row; ++r)
        for (int c = 0; c < this->col; ++c)
            this->matrix[r][c] -= rhs.matrix[r][c];
    return *this;
}

Matrix operator-(Matrix lhs, Matrix &rhs) {
    lhs += rhs;
    return lhs;
}

Matrix& Matrix::operator*=(const Matrix &rhs) {
    if(this->col != rhs.row)
        throw invalid_argument("Column of first matrix and row of second matrix must be the same size");
    Matrix product = Matrix();
    product.matrix.resize(this->row, vector<double>(rhs.col, 0));
    for (int r = 0; r < this->row; ++r)
        for (int rc = 0; rc < this->col; ++rc)
            for (int c = 0; c < rhs.col; ++c)
                product.matrix[r][c] += this->matrix[r][rc] * rhs.matrix[rc][c];
    *this = product;
    return *this;
}

Matrix operator*(Matrix lhs, Matrix &rhs) {
    lhs *= rhs;
    return lhs;
}




