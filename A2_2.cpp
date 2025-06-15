#include <iostream>
#include <cmath>
#include <fstream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Funktionsprototypen
double f(double x);
double f_abl(double x, double x_vorherig, double fx, double f_vorherig);
void newton_iteration(double x0, double tol, int kmax, const string& dateiname);

int main() {
    double tol = 1e-10;
    int kmax = 50;

    cout << "Newton-Verfahren für x0 = -2 wird ausgeführt" << endl;
    newton_iteration(-2, tol, kmax, "output_minus2.txt");

    cout << "Newton-Verfahren für x0 = 42 wird ausgeführt" << endl;
    newton_iteration(42, tol, kmax, "output_42.txt");

    // Plotten 
    system("gnuplot Plot2_1.gpl - ");
   
    
    
    return 0;
}

// Funktion zur Berechnung von f(x)
double f(double x) {
    return x * x - 2 * x - 3;
}

// Funktion zur Berechnung der numerischen Ableitung f'(x)
double f_abl(double x, double x_vorherig, double fx, double f_vorherig) {
    return (fx - f_vorherig) / (x - x_vorherig);
}

void newton_iteration(double x0, double tol, int kmax, const string& dateiname) {
    ofstream datei;
    datei.open(dateiname);

    double res = 1.0; // Initiales Residuum
    double x = x0;
    double h = 1e-8;
    double x_vorherig = x - h;
    double f_vorherig = f(x_vorherig);
    double fx;
    int k = 0;

    while (res > tol && k < kmax) {
        k++;
        fx = f(x);
        double f_abl_wert = f_abl(x, x_vorherig, fx, f_vorherig); //in Newton klasse reinpacken(mit vektoren)
        res = abs(fx);
        x_vorherig = x;
        f_vorherig = fx;
        x = x - (fx / f_abl_wert);

        // Iterationsdaten zum Plotten speichern
        datei << k << " " << x << endl;

        // Überprüfen, ob x unverändert bleibt
        if (x == x_vorherig) {
            cout << "Nullstelle gefunden: " << x << endl;
            break;
        }
    }

    datei.close();

    cout << "Anzahl der Iterationen: " << k << endl;
}