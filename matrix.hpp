//
// Created by sammy on 2019-10-04.
//

#ifndef ASSIGNMENT1_MATRIX_HPP
#define ASSIGNMENT1_MATRIX_HPP

#include <ostream>

using namespace std;

constexpr double Tolerance = 0.001;

class Matrix {
private:
    vector<vector<double>> matrix;
    int row = 0;
    int col = 0;
public:
    Matrix();

    Matrix(int);

    Matrix(int, int);

    Matrix(vector<double>);

    void set_value(int, int, double);

    double get_value(int, int) const;

    void clear();

    ~Matrix();

    friend ostream &operator<<(ostream &, const Matrix &);

    friend bool operator==(const Matrix &, const Matrix &);

    friend bool operator!=(const Matrix &, const Matrix &);

    Matrix &operator++();

    Matrix operator++(int);

    Matrix &operator--();

    Matrix operator--(int);

    Matrix &operator=(Matrix);

    void matrixSwap(Matrix &, Matrix &);

    Matrix &operator+=(const Matrix &);

    friend Matrix operator+(Matrix, Matrix &);

    Matrix &operator-=(const Matrix &);

    friend Matrix operator-(Matrix, Matrix &);

    Matrix &operator*=(const Matrix &);

    friend Matrix operator*(Matrix, Matrix &);
};

#endif //ASSIGNMENT1_MATRIX_HPP
