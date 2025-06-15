#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include "Newton.h"

using namespace std;
using namespace Eigen;

//Prototyp
VectorXd F_ungepuffert (const VectorXd &x0);

// Hauptcode

int main () {

    int i;
    double h = pow(10, -5); // Schrittweite
    double tol = pow(10, -10); // Tolerenz
    int n_iter_max = 1000;
    VectorXd xk(1);
    //VectorXd x=x0(1); //Startvektor


    std::cout <<"Hier xk eingeben:"<< endl;
    std::cin >> xk(0);

    Newton N(F_ungepuffert, n_iter_max, tol, h);
    std::cout<< "Gedämpftes Newtonverfahren mit F_ungef"<< endl;
    cout << "\n damped"<< endl; // nicht nötig
    N.Solve_damped(xk); //nicht nötig
    cout << " \n damped2"<<endl;
    N.Solve_damped2(xk); 
    cout << N.L2_Norm(xk);

    return 0;

    
}

VectorXd F_ungepuffert (const VectorXd &x0){
    VectorXd f(1);
    f(0)= 7* tanh(x0(0)-10)+ 7 - 7; // wegen der Schnittestelle mit pH=7 (-7)
    return f;
    }