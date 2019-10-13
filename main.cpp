#include <iostream>
#include <vector>
#include <iomanip>
#include "matrix.hpp"
#include "googlePageRank.hpp"

using namespace std;

int main() {

    try {
        int numOfPage = 0;
        getNumOfPage(numOfPage);

        vector<double> values = readMatrixFile(numOfPage);

        // Connectivity matrix G
        Matrix connectivity = Matrix(values);
        cout << "Connectivity Matrix =" << endl;
        cout << connectivity << endl;

        // In degree
        vector<double> inDeg = vector<double>();
        // Out degree
        vector<double> outDeg = vector<double>();
        // Get In and Out Degrees
        getInOutDegrees(connectivity, inDeg, outDeg, numOfPage);

        // Importance matrix S
        Matrix importance = connectivity;
        // Determine value of importance matrix (also known as left stochastic matrix or probability matrix)
        getImportance(importance, outDeg, numOfPage);
        cout << "Importance (Pobability) Matrix =" << endl;
        cout << importance << endl;

        // Transition matrix M
        Matrix transition = importance;
        // Teleportation matrix Q
        Matrix teleportation = Matrix(vector<double>(numOfPage * numOfPage, 1.0 / numOfPage));
        // Calculate value in transition matrix
        getTransition(transition, teleportation, numOfPage);

        cout << "Transition Matrix =" << endl;
        cout << transition << endl;

        Matrix rank = Matrix(numOfPage, 1);

        markovProcess(rank, transition, numOfPage);

        cout << "Rank =" << endl;
        cout << rank << endl;

        double sum = getSumOfRank(rank, numOfPage);

        scaleRank(rank, sum, numOfPage);

        cout << "Rank (scaled) =" << endl;
        cout << rank << endl;

        output(rank, numOfPage);

    } catch (exception e) {
        e.what();
    }
    return 0;
}
