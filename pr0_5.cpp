#include "Eigen/Dense"
#include <iostream>
#include<math.h>
#include<iomanip> //für set precision
#include<climits> //für int_max und int_min


using Eigen::MatrixXd; // sind namespaces
using Eigen::Vector3d;
using Eigen::VectorXd;

//Prototyp
MatrixXd BerechnungJacobian_analyt(const Vector3d&);
void F(const VectorXd &, VectorXd &); // die Funktion deren JakobiMatrix berechnet werden soll
void JacobiFD(void (*func)(const VectorXd &, VectorXd &), MatrixXd &J, const VectorXd &x, double h);
void JacobiCD(void (*func)(const VectorXd &, VectorXd &), MatrixXd &J, const VectorXd &x, double h);
double absoluteFehlermass(const MatrixXd&, const MatrixXd&);
double relativeFehlermass(const MatrixXd&, const MatrixXd&);
int hoptimal (double *v);

int main()
{
    int i;
    Vector3d x(2.1, 0.5, 3.0); // Werte für Funktion F
    MatrixXd J_FD, J_CD, J_A; 
    // Berechnung von Jakobi
    JacobiFD(F, J_FD, x, 0.1); // Aufruf 
    JacobiCD(F, J_CD, x, 0.1);
    J_A = BerechnungJacobian_analyt(x);
    // Output Ergebnisse
    std::cout << "analytische Jakobi Matrix:\n"
              << J_A << std::endl;
    std::cout << "Jakobi-Matrix durch Vorwärtsdifferenzenquotient für h=0.1:\n"
              << J_FD << std::endl;
    std::cout << "Jakobi-Matrix durch Zentraldifferenzquotient für h=0.1:\n"
              << J_CD << std::endl;

    double err_abs_1[12], err_abs_2[12], err_rel_1[12], err_rel_2[12];
    for (i=1; i<=12; i++){
        double h = pow(10, -i);
        
        MatrixXd aproxFD; // diese Jakobi Matrizen werden in aproxFD gespeichert, aber wir brauchen nicht diese Variable ausser 'for' Schelife
        JacobiFD(F, aproxFD, x, h);

        MatrixXd aproxCD; // aproxFD und aproxCD sint auxiliary variables, die nur in for gebraucht sind
        JacobiCD(F, aproxCD, x, h);

       
        err_abs_1 [i-1] = absoluteFehlermass(J_A, aproxFD); // i-1 weil wir von 0 anfangen wollen (normalerweise so für ein Vektor)
        err_abs_2 [i-1] = absoluteFehlermass(J_A, aproxCD);

        err_rel_1[i-1] = relativeFehlermass (J_A, aproxFD);
        err_rel_2[i-1] = relativeFehlermass (J_A, aproxCD);

    }
    
    std::cout << " h Wert         | abs err FD | abs err CD | rel err FD | rel err CD |\n";

    for (i=0; i<12; i++){
          std::cout << std::fixed << std::setprecision(13) << ' ' << pow(10, -(i + 1)) << std::setprecision(7) << ' ' << err_abs_1[i] << ' ' << err_abs_2[i] << ' ' << err_rel_1[i] << ' ' << err_rel_2[i] << '\n';
     } 
    i = hoptimal(err_abs_1); // I IST DIE ZEILE VON H OPTIMAL 
    std::cout << std::endl <<"Für h optimal" << std::fixed << std::setprecision(13) << ' ' << pow(10, -(i + 1)) << std::setprecision(7) << ' ' << err_abs_1[i] << ' ' << err_abs_2[i] << ' ' << err_rel_1[i] << ' ' << err_rel_2[i] << '\n';
    return 0;

}

MatrixXd BerechnungJacobian_analyt(const Vector3d &x) // const damit die Variable (die Adresse von x) nicht geändert wird (während Programm)
{
    MatrixXd J(3, 3);

    J(0, 0) = 1;
    J(0, 1) = 2 * x(1);
    J(0, 2) = 3;
    J(1, 0) = 4 * pow(x(0), 3);
    J(1, 1) = 5;
    J(1, 2) = 6 * x(2);
    J(2, 0) = 7;
    J(2, 1) = 8 * x(1);
    J(2, 2) = 9;

    return J;
}

void F(const VectorXd &x, VectorXd &result) // VectorXd ist der Art von &x(Adresse)
//const nur bei &x weil x nicht geändert wird, aber kein const bei &result
{
    result.resize(3); // damit Vektor maximal 3 Elemente hat
    result(0) = x(0) + pow(x(1), 2) + 3 * x(2);
    result(1) = pow(x(0), 4) + 5 * x(1) + 3 * pow(x(2), 2);
    result(2) = 7 * x(0) + 4 * pow(x(1), 2) + 9 * x(2);
}
// void (*func)(const VectorXd&, VectorXd&) ist pointer zu eine Funktion
// für Aufruf in main soll man die Funktion F benutzen 

void JacobiFD(void (*func)(const VectorXd &, VectorXd &), MatrixXd &J, const VectorXd &x, double h)
{
   
    int n = x.size(); // size ist 3; x0, x1,x2
    VectorXd f0(x.size()); // Deklarierung 2 Vektoren mit max 3 Elem, f0 ist result
    VectorXd f1(x.size());
    func(x, f0); // F(x, f0) in f0(0) ist result0, f0(1) ist result 2 usw. In f0 wird einfach die werte 2.1 0.5 usw in result(...) eingesetzt
    J.resize(f0.size(), x.size()); // J ist meine Matrix mit 3,3
                                    // resize weil wir noch keine gegebene Grösse haben, und wir wollen die 3,3 grösse geben

    for (int j = 0; j < n; j++)  // die Approximierung
    {
        VectorXd xh = x; //xh ist ein anderer Vektor der jetzt alles von x kopiert
        xh(j) += h; // für jede Position von xh ist ein Step h addiert
        func(xh, f1); // f1 ist result aber von (x+h), also mit Step
        for (int i = 0; i < f0.size(); ++i)
        {
            J(i, j) = (f1(i) - f0(i)) / h; // Jakobi matrix wird generiert mit Approximierung
        }
    }
}

void JacobiCD(void (*func)(const VectorXd &, VectorXd &), MatrixXd &J, const VectorXd &x, double h)
// void -> return type von meine Funktion (bei mir war void F)
// 2 Vektoren x(const) und result als parameter zu mein Pointer zu eine Funktion
{

   
    int n = x.size(); //3
    VectorXd f1(x.size()), f2(x.size()); // 2 Vektoren mit Länge 3
    J.resize(x.size(), x.size()); // Jakobi Matrix 3,3

    for (int j = 0; j < n; j++)
    {
        VectorXd xh = x; // Deklarierung von xh und dan Initialisierung mit x
        xh(j) += h; // x+h
        func(xh, f1); // f(x+h)

        xh = x; // reset von xh
        xh(j) -= h;
        func(xh, f2);

        for (int i = 0; i < x.size(); i++)
        {
            J(i, j) = (f1(i) - f2(i)) / (2 * h);
        }
    }
}

// wir brauchen eine Funktion die die relative und absolte Fehlermass berechnet/zurückgibt

// absolute Fehlermass
double absoluteFehlermass(const MatrixXd& numerisch, const MatrixXd& analytisch) {  // dei Funktion bekommt die Funktion für Approximierung und die 'richtige'
    return (numerisch - analytisch).norm(); // Frobenius-norm der elementweisen Differenz, Eigen kann 2 Matrizen addieren und substrahieren
    // die Implementierung von Determinante in Eigen
}
 // relative Fehlermass
    
    double relativeFehlermass(const MatrixXd& numerisch, const MatrixXd& analytisch){ 
    double abs_error = absoluteFehlermass(numerisch, analytisch); // damit man nicht nochmal Differenz berechnen soll
    double analytische_norm = analytisch.norm(); // Determinante von die Approximierungrn
    return abs_error / analytische_norm; // gesuchte Bruch
}

// Funktion für h optimal
int  hoptimal (double *v){ // dieser vektor ist Spalte von abs err FD
    double minimum = INT_MAX; // wir initialisieren erstmal mit grösste Zahl damit wir es danach damit vergleichen um Minimum zu kriegen
    int minindex = 0;
    for (int i = 0; i <12; i++){
        if ( minimum >  v[i]){
            minimum = v[i];
            minindex = i;
        }
    }
    return minindex;
}
