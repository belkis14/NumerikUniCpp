#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <iomanip>
#include "Newton.h"

using namespace std;
using namespace Eigen;

//Funktionsprototypen

VectorXd F_gef (const VectorXd &x);
VectorXd F_ungef(const VectorXd &x);


int main (){
    int i, n;
    
    // Deklarationen
    double h = pow(10, -5); // Schrittweite
    double tol = pow(10, -10); // Tolerenz
    int n_iter_max = 1000;
    cout << "Grösse von x0 ist: ";  
    cin >> n;  
    
    VectorXd x0(n); // Startvektor

    cout <<"Hier Startwert x0 eingeben:"<< endl;
    for (i = 0; i < n; i++){
        cin >> x0[i];
    }
    cout << "x0 ist:"<< endl;
    for (i = 0; i < n; i++){
        cout << x0[i]<<endl;
    }


    
    Newton N1(F_gef, n_iter_max, tol, h);
    Newton N2(F_ungef, n_iter_max, tol, h);

    // Newtonverfahren
    cout << "Newtonverfahren mit gepufferte Säure Base Titration"<<endl;
    N1.Solve2(x0);
    

    cout << "Newtonverfahren mit ungepufferte Säure Base Titration"<<endl;
    N2.Solve2(x0);
   
   

}

VectorXd F_gef (const VectorXd &x){
    VectorXd f(1);
    f[0]= 0.73 * (0.25 * x[0] + 0.8 * sin(0.33 * x[0] - 3)) +2-7; // wegen der Schnittestelle mit pH=7 (-7)
    return f;
}

VectorXd F_ungef(const VectorXd &x){ 
    VectorXd f(1);
    f[0]= 7* tanh(x[0]-10)+ 7 - 7; // wegen der Schnittestelle mit pH=7 (-7)
    return f;
}