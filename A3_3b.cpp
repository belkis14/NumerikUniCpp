#include <Library.h>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "Euler.h"
#include <fstream>
#include <iomanip>

using namespace std;
using namespace Eigen;

VectorXd funktion_a (const VectorXd &c) { // Funktion mit k1 = 1 und k2 = 10
    VectorXd f(3);
    f[0] = -1.0 * c[0];
    f[1] = 1.0 * c[0] - 1e6* c[1];
    f[2] = 1e6 * c[1];
    return f;
}


int main (){
    

    int N, n = 3;
    double t0 = 0;
    double t_end = 20;
    double h = 0.05;
    int schritte =  ((t_end - t0) / h) + 1;
    VectorXd y0(n);
    y0[0] = 1;
    y0[1] = 0;
    y0[2] = 0;

    MatrixXd Explizit(schritte, y0.size()+1);
    MatrixXd Implizit(schritte, y0.size()+1);
    N = (t_end - t0) / h + 1; // Anzahl der Iterationsschritte 

  
    
    Euler EulerObj(t0, t_end, y0, h, funktion_a);
    
    Explizit = EulerObj.fsw(&Euler::explizit);
    Implizit = EulerObj.fsw(&Euler::implizit);
    

    
    int dim_spalte1, dim_zeile1, dim_zeile2;

     dim_spalte1= Explizit.cols(); // gleich wie bei implizit
     dim_zeile1 = Explizit.rows();

     dim_zeile2 =Implizit.rows();
    
   ofstream Datei;
   Datei.open ("Explizit.txt");

   for (int i=0; i< dim_zeile1; i++){
    for (int j=0; j< dim_spalte1; j++){
        Datei << Explizit (i, j) << "\t";
        
    }
     Datei << endl;
   }

    Datei.close();

ofstream Datei2;
Datei2.open ("Implizit.txt");

 for (int i=0; i< dim_zeile2; i++){
    for (int j=0; j< dim_spalte1; j++){
        Datei2 << Implizit (i, j) << "\t";
        
    }
     Datei2 << endl;
   }

    Datei2.close();

   

   /*
    ofstream Outputdatei1; // numerische Lösung
    Outputdatei1.open("Explizit.txt");

    Outputdatei1 << Explizit; //analytische Lösung
    Outputdatei1.close();

    ofstream Outputdatei2; // numerische Lösung
    Outputdatei2.open("Implizit.txt");

    Outputdatei2 << Implizit; //analytische Lösung
    Outputdatei2.close();
 
  */
    // Plotten 
     system("gnuplot 3b.gpl - ");


    return 0;
}