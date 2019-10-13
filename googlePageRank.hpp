//
// Created by sammy on 2019-10-12.
//

#ifndef ASSIGNMENT1_GOOGLEPAGERANK_HPP
#define ASSIGNMENT1_GOOGLEPAGERANK_HPP

#include <vector>
#include "matrix.hpp"

constexpr double ProbabilityFactor = 0.85;

int &getNumOfPage(int &);

// Read Matrix File
vector<double> readMatrixFile(int);

// Get In and Out Degrees
void getInOutDegrees(const Matrix &, vector<double> &, vector<double> &, int);

// Determine value of importance matrix (also known as left stochastic matrix or probability matrix)
void getImportance(Matrix &, vector<double>, int);

// Calculate value in transition matrix
void getTransition(Matrix &, Matrix &, int);

// do markov process
void markovProcess(Matrix &, Matrix &, int);

// calculate the sum of rank
double getSumOfRank(const Matrix &, int);

// scale rank so its elements sum to 1
void scaleRank(Matrix &, double, int);

// Format result to output
void output(Matrix, int);

#endif //ASSIGNMENT1_GOOGLEPAGERANK_HPP
