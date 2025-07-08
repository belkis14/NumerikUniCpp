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
    f[1] = 1.0 * c[0] - 10.0 * c[1];
    f[2] = 10.0 * c[1];
    return f;
}


VectorXd funktion_b (const VectorXd &c) { // Funktion mit k1 = 1 und k2 = 10
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

    MatrixXd Explizit(schritte, y0.size()+1), Explizit2(schritte, y0.size()+1);
    MatrixXd Implizit(schritte, y0.size()+1);
    N = (t_end - t0) / h + 1; // Anzahl der Iterationsschritte 

  
    
    Euler EulerObj(t0, t_end, y0, h, funktion_a);
    Euler EulerObj2(t0, t_end, y0, h, funktion_b);

    Explizit = EulerObj.fsw(&Euler::explizit);
    

    Explizit2 = EulerObj2.fsw(&Euler::explizit);
    


    return 0;
}
    
