//
// Created by sammy on 2019-10-12.
//

#include "googlePageRank.hpp"

void getInOutDegrees(const Matrix m, vector<double> &in, vector<double> &out) {
    in.resize(NumOfPage, 0);
    out.resize(NumOfPage, 0);

    for (int i = 0; i < NumOfPage; ++i)
        for (int j = 0; j < NumOfPage; ++j) {
            in[i] += m.get_value(i, j);
            out[j] += m.get_value(i, j);
        }
}

void getImportance(Matrix &m, vector<double> out) {
    for (int i = 0; i < NumOfPage; ++i)
        for (int j = 0; j < NumOfPage; ++j) {
            m.set_value(i, j, m.get_value(i, j) / (out[j] > 0 ? out[j] : 1));
            if (out[j] == 0)
                m.set_value(i, j, 1 / (double) NumOfPage);
        }
}

void getTransition(Matrix &transition, Matrix &teleportation) {
    // M = 0.85 * S + (1 - 0.85) * Q
    for (int i = 0; i < NumOfPage; ++i)
        for (int j = 0; j < NumOfPage; ++j)
            transition.set_value(i, j, transition.get_value(i, j) * ProbabilityFactor);

    for (int i = 0; i < NumOfPage; ++i)
        for (int j = 0; j < NumOfPage; ++j)
            teleportation.set_value(i, j, teleportation.get_value(i, j) * (1 - ProbabilityFactor));

    transition += teleportation;
}

void markovProcess(Matrix &rank, Matrix &transition) {
    for (int i = 0; i < NumOfPage; ++i) {
        rank.set_value(i, 0, 1);
    }

    Matrix prev = Matrix(4, 1);

    do {
        prev = rank;
        rank = transition * rank;
    } while ((rank.get_value(0, 0) - prev.get_value(0, 0)) > Tolerance);
}

double getSumOfRank(const Matrix &rank) {
    double sum = 0;
    for (int i = 0; i < NumOfPage; ++i) {
        sum += rank.get_value(i, 0);
    }

    return sum;
}

void scaleRank(Matrix &rank, double sum) {
    for (int i = 0; i < NumOfPage; ++i) {
        rank.set_value(i, 0, rank.get_value(i, 0) / sum);
    }
}