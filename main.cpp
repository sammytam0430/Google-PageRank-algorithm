#include <iostream>
#include <vector>
#include <iomanip>
#include "matrix.hpp"

using namespace std;

int main() {

    int n = 4;
    vector<Matrix> w = vector<Matrix>(n);
    Matrix g = Matrix(vector<double>{0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0});
    // In degree
    vector<double> r = vector<double>();
    // Out degree
    vector<double> c = vector<double>();
    r.resize(n, 0);
    c.resize(n, 0);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            r[i] += g.get_value(i, j);
            c[j] += g.get_value(i, j);
        }

    Matrix s = g;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            s.set_value(i, j, s.get_value(i, j) / (c[j] > 0 ? c[j] : 1));
            if (c[j] == 0)
                s.set_value(i, j, 1 / (double) n);
        }

    double p = 0.85;
    Matrix q = Matrix(vector<double>(n * n, 1 / (double) n));
    Matrix m = s;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            m.set_value(i, j, m.get_value(i, j) * p);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            q.set_value(i, j, q.get_value(i, j) * (1 - p));

    m += q;

    Matrix rank = Matrix(n, 1);
    for (int i = 0; i < n; ++i)
        rank.set_value(i, 0, 1);

    Matrix prev(n, 1);

    for (int i = 0; i < n * 3; ++i)
        rank = m * rank;

    double sum = 0;

    for (int i = 0; i < n; ++i)
        sum += rank.get_value(i, 0);

    for (int i = 0; i < n; ++i) {
        rank.set_value(i, 0, rank.get_value(i, 0) / sum);
    }

    cout << g << endl;
    cout << s << endl;
    cout << m << endl;
    cout << rank << endl;

    cout << fixed << setprecision(2);
    cout << "Page A: " << rank.get_value(0, 0) * 100 << "%" << endl;
    cout << "Page B: " << rank.get_value(1, 0) * 100 << "%" << endl;
    cout << "Page C: " << rank.get_value(2, 0) * 100 << "%" << endl;
    cout << "Page D: " << rank.get_value(3, 0) * 100 << "%" << endl;

    return 0;
}