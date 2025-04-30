#include <iostream>
#include <Library.h>
#include <Eigen/Dense>
#include "Methods.h"

extern void EinlesenVektorMatrix(MatrixXd & M, VectorXd & b, const char* filename);
extern VectorXd LGS_Solve(const MatrixXd &A, const VectorXd &b);

int main(){

    //Deklaration
    VectorXd x;
    VectorXd b1,b2;
    MatrixXd A1,A2;
    
    char filename1[50]; 
    char filename2[50]; 


    //Dateiname über Konsole fragen
    std::cout<<"Geben Sie den Namen der ersten Datei an (mit .txt!!!):"<<std::endl;
    std::cin>> filename1;

    std::cout<<"Geben Sie den Namen der zweiten Datei an (mit .txt!!!):"<<std::endl;
    std::cin>> filename2;

    // Einlesen aus Datei
    EinlesenVektorMatrix(A1, b1, filename1);
    EinlesenVektorMatrix(A2, b2, filename2);
    
    std::cout << "Matrix A1:\n" << A1 << std::endl;
    std::cout << "Vector b1:\n" << b1 << std::endl;
    std::cout << "Matrix A2:\n" << A2 << std::endl;
    std::cout << "Vector b2:\n" << b2 << std::endl;

    // LGS lösen für die erste Matrix und Vektor
    x = LGS_Solve(A1, b1);
    std::cout << "Loesungsvektor x für A1 und b1:\n" << x << std::endl;

    // LGS lösen für die zweite Matrix und Vektor
    x = LGS_Solve(A2, b2);
    std::cout << "Loesungsvektor x für A2 und b2:\n" << x << std::endl;

    return 0;
}