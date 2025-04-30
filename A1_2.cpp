#include <iostream>
using namespace std;

int main() {
    // Matrix A
    double A[3][3] = {
        {4, 3, 1},
        {11, 9, 10},
        {6, 9, 9}
    };

    // Matrizen L und R initialisieren
    double L[3][3] = {0};
    double R[3][3] = {0};

    // LR-Zerlegung durchführen
    for (int i = 0; i < 3; i++) {
        // Obere Dreiecksmatrix R
        for (int k = i; k < 3; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * R[j][k];
            }
            R[i][k] = A[i][k] - sum;
        }

        // Untere Dreiecksmatrix L
        for (int k = i; k < 3; k++) {
            if (i == k) {
                L[i][i] = 1; // Diagonaleinträge von L sind 1
            } else {
                double sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += L[k][j] * R[j][i];
                }
                L[k][i] = (A[k][i] - sum) / R[i][i];
            }
        }
    }

    // Matrix A prüfen
    double A_Probe[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                A_Probe[i][j] += L[i][k] * R[k][j];
            }
        }
    }

    // Ergebnisse ausgeben
    cout << "Matrix L:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix R:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << R[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Matrix A_Probe:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << A_Probe[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}