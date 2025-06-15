#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>
#include <iomanip>
#include "Newton.h"

using namespace std;
using namespace Eigen;

// Funktionsprototypen

VectorXd F1(const VectorXd &x);

int main() {

    int i, n=2;
    double h = pow(10, -5);
    double tol = pow(10,-10);
    double n_iter_max=1000;
    VectorXd x0(n); // (2 dim) Startvektor erstellen 
    cout << "Geben Sie den Vektor x0 an:" << endl;
    for (int i=0; i<n; i++){
        cin >> x0[i]; // in unser Fall sieht es so aus x[0]=-1000 und x[1]=6
    }
    cout << "Startvektor x0:\n";
    for (int i=0; i<n; i++){
        cout << x0[i] << endl; 
    }

    
    Newton N(F1, n_iter_max, tol, h); // new object called N from class Newton. what's in () is called arguments and 'passing values' to the parameteres of the function 
    VectorXd Ergebnis = N.Solve(x0);
    

    //cout << N.Iterationen << endl;
    //cout << N.res << endl;
    

}

VectorXd F1(const VectorXd &x) {
    VectorXd f(2);
    f[0] = (pow(x[0], 2) - 3 * x[1]);
    f[1] = (2 * pow(x[0], 2) - 8 * pow(x[1], 3) + 4);
    return f;
}
