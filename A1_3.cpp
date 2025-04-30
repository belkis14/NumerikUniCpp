#include <iostream>
#include <Library.h>
#include <Eigen/Dense>
#include "Methods.h"

using namespace std;
using namespace Eigen;

extern VectorXd LGS_Solve(const MatrixXd &A, const VectorXd &b);

int main() {
    const int n = 3;  // Dimension of the matrix is always 3

    MatrixXd A(n, n);
    VectorXd b(n);

    // Einlesen von Matrix A
    for (int i = 0; i < n; ++i) {
        cout << "Bitte Zeile " << i + 1 << " der Matrix A eingeben:" << endl;
        for (int j = 0; j < n; ++j) {
            cout << "A" << j + 1 << "=";
            cin >> A(i, j);
        }
    }

    // Einlesen von Vektor b
    cout << "Bitte Vektor b eingeben:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "b" << i + 1 << "=";
        cin >> b(i);
    }

    // Probe
    cout << "Lösung mittels x=A\\b:" << endl;
    VectorXd x_exakt = A.colPivHouseholderQr().solve(b);
    cout << x_exakt << endl;

    // LR Zerlegung
    VectorXd x = LGS_Solve(A, b);
    cout << "Numerische Lösung:" << endl;
    cout << x.transpose() << endl;

    return 0;
}