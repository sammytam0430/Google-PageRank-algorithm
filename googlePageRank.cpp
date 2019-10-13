//
// Created by sammy on 2019-10-12.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include "googlePageRank.hpp"

int &getNumOfPage(int &numOfPage) {
    ifstream fin;
    string line;

    fin.open("../connectivity.txt", ios_base::in);
    if (!fin.is_open()) {
        cerr << "Unable to open file" << endl;
        exit(1);
    } else {
        while (getline(fin, line)) {
            numOfPage++;
        }
        fin.close();
        return numOfPage;
    }
}

vector<double> readMatrixFile(int numOfPage) {
    ifstream fin;
    string line;

    vector<double> data = vector<double>(0);
    double d = 0;

    fin.open("../connectivity.txt", ios_base::in);
    if (!fin.is_open()) {
        cerr << "Unable to open file" << endl;
        exit(1);
    } else {
        while (getline(fin, line)) {
            istringstream iss;
            iss.str(line);
            if (line.size() > 0) {
                for (int i = 0; i < numOfPage; ++i) {
                    iss >> d;
                    data.push_back(d);
                }
            }
        }
    }
    fin.close();

    return data;
}

void getInOutDegrees(const Matrix &m, vector<double> &in, vector<double> &out, int numOfPage) {
    in.resize(numOfPage, 0);
    out.resize(numOfPage, 0);

    for (int i = 0; i < numOfPage; ++i)
        for (int j = 0; j < numOfPage; ++j) {
            in[i] += m.get_value(i, j);
            out[j] += m.get_value(i, j);
        }
}

void getImportance(Matrix &m, vector<double> out, int numOfPage) {
    for (int i = 0; i < numOfPage; ++i)
        for (int j = 0; j < numOfPage; ++j) {
            m.set_value(i, j, m.get_value(i, j) / (out[j] > 0 ? out[j] : 1));
            if (out[j] == 0)
                m.set_value(i, j, 1 / (double) numOfPage);
        }
}

void getTransition(Matrix &transition, Matrix &teleportation, int numOfPage) {
    // M = 0.85 * S + (1 - 0.85) * Q
    for (int i = 0; i < numOfPage; ++i)
        for (int j = 0; j < numOfPage; ++j)
            transition.set_value(i, j, transition.get_value(i, j) * ProbabilityFactor);

    for (int i = 0; i < numOfPage; ++i)
        for (int j = 0; j < numOfPage; ++j)
            teleportation.set_value(i, j, teleportation.get_value(i, j) * (1 - ProbabilityFactor));

    transition += teleportation;
}

void markovProcess(Matrix &rank, Matrix &transition, int numOfPage) {
    for (int i = 0; i < numOfPage; ++i) {
        rank.set_value(i, 0, 1);
    }

    Matrix prev = Matrix(numOfPage, 1);

    do {
        prev = rank;
        rank = transition * rank;
    } while ((rank.get_value(0, 0) - prev.get_value(0, 0)) > Tolerance);
}

double getSumOfRank(const Matrix &rank, int numOfPage) {
    double sum = 0;
    for (int i = 0; i < numOfPage; ++i) {
        sum += rank.get_value(i, 0);
    }

    return sum;
}

void scaleRank(Matrix &rank, double sum, int numOfPage) {
    for (int i = 0; i < numOfPage; ++i) {
        rank.set_value(i, 0, rank.get_value(i, 0) / sum);
    }
}

void output(Matrix rank, int numOfPage) {
    char p = 'A';
    cout << fixed << setprecision(2);
    for (int i = 0; i < numOfPage; ++i) {
        cout << "Page " << p++ << ": " << rank.get_value(i, 0) * 100 << "%" << endl;
    }
}