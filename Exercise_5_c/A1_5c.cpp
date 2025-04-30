#include <iostream>
#include <fstream>
#include "Eigen/Dense"
#include "Library.h"
#include "Methods.h"
#include <iomanip>

using namespace std;
extern VectorXd LGS_Solve(const MatrixXd &A, const VectorXd &b);

int main() {

    //Deklaration
   
    int 	i;
    char Input1[20]; //= "MAT_a.txt";
    char Input2[20]; // = "MAT_b.txt";




/////////////////////////// MAT_a////////////////////////////////////////////////
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

    
    //////////////////////////////MAT_b.txt////////////////////////////////////////////////////////////////////////

    int AnzahlZeilenb, AnzahlSpaltenb;
    char Inputb[20];

    ifstream Dateib;

    
    MatrixXd Mb(AnzahlZeilen, 12), M_Transb(12, AnzahlZeilen), M_LGSb(12, 12);
    MatrixXd Matrixb(1, 12); // 1x12 Matrix für eine Zeile

    

    // Matrix Mb erstellen
    for (int i = 0; i < AnzahlZeilenb; i++) {
        Matrixb(0, 0) = 1;
        Matrixb(0, 1) = W_PE(i);
        Matrixb(0, 2) = d(i);
        Matrixb(0, 3) = pow(W_PE(i), 2);
        Matrixb(0, 4) = W_PE(i) * d(i);
        Matrixb(0, 5) = d(i) * d(i);
        Matrixb(0, 6) = pow(W_PE(i), 3);
        Matrixb(0, 8) = pow(d(i), 3);
        Matrixb(0, 9) = pow(W_PE(i), 4);
        Matrixb(0, 10) = pow(W_PE(i), 3)*pow(d(i), 3);
        Matrixb(0, 11) = pow(d(i), 4);
        Mb.row(i) = Matrixb; 
    }

    cout << "Mb= \n" << Mb << endl;

    // Normalengleichung
    M_Transb = Mb.transpose();
    M_LGSb = M_Transb * Mb;
    cout << "M_LGSb ist: \n" << M_LGSb << endl;
    
   
    
    Dateib.close();
    ofstream Outputb;
    Outputb.open("MAT_b.txt");
    if (Outputb.is_open()) {
        Outputb << M_LGSb;
        Outputb.close();
        cout << "Die Matrix M_LGS wurde in MAT_b.txt gespeichert." << endl;
    } else {
        cerr << "Fehler beim Öffnen der Datei zum Schreiben." << endl;
    }




 VectorXd EW1(6), EW2(12);
 EW1 = M_LGS.eigenvalues().real();
 EW2 = M_LGSb.eigenvalues().real();
 cout<<" EW1" << EW1 <<endl;
 cout<< " EW2" << EW2 << endl;

 double SVP1 = EW1.maxCoeff() / EW1.minCoeff();
 double SVP2 = EW2.maxCoeff() / EW2.minCoeff();

 cout <<"k1 ist: \n" << SVP1 << endl;
 cout <<"k2 ist: \n" << SVP2 << endl;


}