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
    Datei >> AnzahlZeilen >> AnzahlSpalten;
    MatrixXd M(20, 6), M_Trans(6, 20), M_LGS(6, 6);
    VectorXd W_PA(AnzahlZeilen), W_PE(AnzahlZeilen), d(AnzahlZeilen), P(AnzahlZeilen), b(6), x(6);
    MatrixXd Matrix(1, 6); // 1x6 Matrix für eine Zeile

    for (int i = 0; i < AnzahlZeilen; i++) {
        Datei >> W_PA(i);
        Datei >> d(i);
        Datei >> P(i);
    } 
    cout << "W_PA ist: \n" << W_PA << endl;
    cout << "d ist: \n" << d << endl;
    cout << "P ist: \n" << P << endl;

    // W_PE = 1-W_PA
    VectorXd vektor = VectorXd::Ones(AnzahlZeilen);
    W_PE = vektor - W_PA;
    cout << "W_PE ist: \n" << W_PE << endl;

    // Matrix M erstellen
    for (int i = 0; i < AnzahlZeilen; i++) {
        Matrix(0, 0) = 1;
        Matrix(0, 1) = W_PE(i);
        Matrix(0, 2) = d(i);
        Matrix(0, 3) = W_PE(i) * W_PE(i);
        Matrix(0, 4) = W_PE(i) * d(i);
        Matrix(0, 5) = d(i) * d(i);
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
    


    // Ausgabe in Outputdatei 
    ofstream Output;
    Output.open("MAT_a.txt");
    Output << M_LGS;
    Output.close();
    //Plotten 
    system ("gnuplot Plot.gpl - ");
    
}















