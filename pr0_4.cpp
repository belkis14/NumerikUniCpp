#include "Eigen/Dense"
#include <iostream>
#include <fstream>
#include <cstring>
 
using Eigen::MatrixXd;
 
// Prototyp
void ReadMatrix(MatrixXd&, char*);
 
void SaveMatrix(MatrixXd, char*);
 
int main ()
{
    // Deklaration
    char in1[30], in2[30]; // nur die Namen von die Dateien
    int dim;
 
 
    // Name der Inputdataien über Konsole
    std ::cout << "Geben Sie den Name der 1. Einlesedatei an: " << std::endl;
    std :: cin >> in1;
 
    std :: cout << "Geben Sie den Name der 2. Einlesedatei an: " << std::endl;
    std :: cin >> in2;
 
    MatrixXd M1(1, 1), M2(1, 1);
 
    ReadMatrix(M1, in1);
    ReadMatrix(M2, in2);
 
    MatrixXd M_sum = M1 + M2;
 
    std::cout << M_sum << std::endl;
 
    char output_filename[20];
    strcpy(output_filename, "Output.dat"); //strcpy kopiert ein charachter string 
 
    SaveMatrix(M_sum, output_filename);
}
 
void ReadMatrix(MatrixXd & M, char* filename) {
    std::ifstream Datei; 
    Datei.open(filename);
 
    int AnzahlZeilen, AnzahlSpalten;
    int i, j;
    int x;
 
    Datei >> AnzahlZeilen >> AnzahlSpalten; 
 
    M.resize(AnzahlZeilen, AnzahlSpalten);
 
    for(i = 0; i < AnzahlZeilen; i++) {
      for(j = 0; j < AnzahlSpalten; j++) {
        Datei >> x;
 
        M(i, j) = x;
      }
    }
 
    Datei.close();
}
 
void SaveMatrix(MatrixXd M, char* filename) {
  std::ofstream Datei;
 
  Datei.open(filename);
 
  int i, j;
 
  for(i = 0; i < M.rows(); i++) {
    for(int j = 0; j < M.cols(); j++) {
      Datei << M(i, j) << ' ';
    }
 
    Datei << std::endl;
  }
 
  Datei.close();
}
