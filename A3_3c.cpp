#include <Eigen/Dense>
#include <iomanip>
#include "Newton.h"

using namespace std;
using namespace Eigen;

// Funktionsprototypen

VectorXd F1(const VectorXd &x);
VectorXd F2(const VectorXd &x);

int main() {

    int i, n=2; //eigentlich nicht nötig, denn es schon in Newton ist
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

    
    Newton N1(F1, n_iter_max, tol, h);
    Newton N2(F2,n_iter_max, tol, h);
    std::cout<<"\nNewton-Verfahren mit F1:\n\n";
    VectorXd Ergebnis1 = N1.Solve2(x0);
    cout << Ergebnis1 << endl;


    std::cout<<"\nNewton-Verfahren mit F2:\n\n";
    VectorXd Ergebnis2 = N2.Solve2(x0);
    cout << Ergebnis2 << endl;
    


}

VectorXd F1(const VectorXd &x) {
    VectorXd f(2);
    f[0] = (pow(x[0], 2) - 3 * x[1]);
    f[1] = (2 * pow(x[0], 2) - 8 * pow(x[1], 3) + 4);
    return f;
}

VectorXd F2 (const VectorXd &x) {
    VectorXd f(2);
    f[0]= (pow(x[0],2)-3*x[1])*pow(10,6);
    f[1]= 2*pow(x[0],2)-8*pow(x[1],3)+4;
    return f;
}