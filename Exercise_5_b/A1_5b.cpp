#include <iostream>
#include <fstream>
#include "Eigen/Dense"
#include "Library.h"
#include "Methods.h"
#include <iomanip>

using namespace Eigen;
using namespace std;

extern VectorXd LGS_Solve(const MatrixXd &A, const VectorXd &b);

int main() {
    int AnzahlZeilen, AnzahlSpalten;
    char Input[20];

    ifstream Datei;

    Datei.open("Experiment.txt");
    if (!Datei.is_open()) {
        cerr << "Datei kann nicht geöffnet werden!" << endl;
        return 1;
    }
    Datei >> AnzahlZeilen >> AnzahlSpalten;
    MatrixXd M(AnzahlZeilen, 12), M_Trans(12, AnzahlZeilen), M_LGS(12, 12);
    VectorXd W_PA(AnzahlZeilen), W_PE(AnzahlZeilen), d(AnzahlZeilen), P(AnzahlZeilen), b(12), x(12);
    MatrixXd Matrix(1, 12); // 1x12 Matrix für eine Zeile

    for (int i = 0; i < AnzahlZeilen; i++) {
        Datei >> W_PA(i);
        Datei >> d(i);
        Datei >> P(i);
    }
    cout << "W_PA ist: \n" << W_PA << endl;
    cout << "d ist: \n" << d << endl;
    cout << "P ist: \n" << P << endl;

    // W_PE = 1 - W_PA
    VectorXd vektor = VectorXd::Ones(AnzahlZeilen);
    W_PE = vektor - W_PA;
    cout << "W_PE ist: \n" << W_PE << endl;

    // Matrix M erstellen
    for (int i = 0; i < AnzahlZeilen; i++) {
        Matrix(0, 0) = 1;
        Matrix(0, 1) = W_PE(i);
        Matrix(0, 2) = d(i);
        Matrix(0, 3) = pow(W_PE(i), 2);
        Matrix(0, 4) = W_PE(i) * d(i);
        Matrix(0, 5) = d(i) * d(i);
        Matrix(0, 6) = pow(W_PE(i), 3);
        Matrix(0, 7) = pow(W_PE(i), 2) * pow(d(i), 2);
        Matrix(0, 8) = pow(d(i), 3);
        Matrix(0, 9) = pow(W_PE(i), 4);
        Matrix(0, 10) = pow(W_PE(i), 3)*pow(d(i), 3);
        Matrix(0, 11) = pow(d(i), 4);
        M.row(i) = Matrix; // jede Zeile
    }

    cout << "M= \n" << M << endl;

    // Normalengleichung
    M_Trans = M.transpose();
    M_LGS = M_Trans * M;
    cout << "M_LGS ist: \n" << M_LGS << endl;
    b = M_Trans * P;
    cout << "b ist: \n" << b << endl;

    // Aufruf der Funktion
    x = LGS_Solve(M_LGS, b);
    cout << "x ist: \n" << x << endl;
    Datei.close();

    // a Ergebniss der LR Zerlegung
    VectorXd a(12);
    

    // Ausgabe in Outputdatei 
    ofstream Output;
    Output.open("MAT_b.txt");
    if (Output.is_open()) {
        Output << M_LGS;
        Output.close();
        cout << "Die Matrix M_LGS wurde in MAT_b.txt gespeichert." << endl;
    } else {
        cerr << "Fehler beim Öffnen der Datei zum Schreiben." << endl;
    }

    system (" gnuplot zweitePlot.gpl -");
    return 0;
}
