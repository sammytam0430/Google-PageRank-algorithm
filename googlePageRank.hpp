//
// Created by sammy on 2019-10-12.
//

#ifndef ASSIGNMENT1_GOOGLEPAGERANK_HPP
#define ASSIGNMENT1_GOOGLEPAGERANK_HPP

#include <vector>
#include "matrix.hpp"

constexpr double Tolerance = 0.001;
constexpr double ProbabilityFactor = 0.85;
constexpr int NumOfPage = 4;

// Get In and Out Degrees
void getInOutDegrees(const Matrix m, vector<double> &in, vector<double> &out);

// Determine value of importance matrix (also known as left stochastic matrix or probability matrix)
void getImportance(Matrix &m, vector<double> out);

// Calculate value in transition matrix
void getTransition(Matrix &transition, Matrix &teleportation);

void markovProcess(Matrix &rank, Matrix &transition);

double getSumOfRank(const Matrix &rank);

void scaleRank(Matrix &rank, double sum);

#endif //ASSIGNMENT1_GOOGLEPAGERANK_HPP
