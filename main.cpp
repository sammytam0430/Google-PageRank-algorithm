#include <iostream>
#include <vector>
#include <iomanip>
#include "matrix.hpp"
#include "googlePageRank.hpp"

using namespace std;

int main() {

    // Connectivity matrix G
    Matrix connectivity = Matrix(vector<double>{0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0});
    cout << connectivity << endl;

    // In degree
    vector<double> inDeg = vector<double>();
    // Out degree
    vector<double> outDeg = vector<double>();
    // Get In and Out Degrees
    getInOutDegrees(connectivity, inDeg, outDeg);

    // Importance matrix S
    Matrix importance = connectivity;
    // Determine value of importance matrix (also known as left stochastic matrix or probability matrix)
    getImportance(importance, outDeg);
    cout << importance << endl;

    // Transition matrix M
    Matrix transition = importance;
    // Teleportation matrix Q
    Matrix teleportation = Matrix(vector<double>(NumOfPage * NumOfPage, 1 / (double) NumOfPage));
    // Calculate value in transition matrix
    getTransition(transition, teleportation);
    cout << transition << endl;

    Matrix rank = Matrix(NumOfPage, 1);

    markovProcess(rank, transition);

    double sum = getSumOfRank(rank);

    scaleRank(rank, sum);

    cout << rank << endl;

    cout << fixed << setprecision(2);
    cout << "Page A: " << rank.get_value(0, 0) * 100 << "%" << endl;
    cout << "Page B: " << rank.get_value(1, 0) * 100 << "%" << endl;
    cout << "Page C: " << rank.get_value(2, 0) * 100 << "%" << endl;
    cout << "Page D: " << rank.get_value(3, 0) * 100 << "%" << endl;

    return 0;
}
