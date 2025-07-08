#include <iostream>
#include <cmath>
#include <fstream>


using namespace std;

double exakt (double t){
    double erg;
    erg = 2* exp(t)-t -1;
    return erg;
}


double relative_Fehler(double (*f)(double), double y , double t){
     double yExakt = f(t);
    return fabs(y - yExakt) / fabs(yExakt) * 100;
}

void EulerVerf (double h , const char* name) {
    double t = 0;
    double y = 1;
    ofstream myfile;
    myfile.open(name);
    double e;

    myfile << t << "\t" << y << "\t" << exakt (t) << "\t" << relative_Fehler(exakt, y, t) << endl;

    while (t<2){
        t += h;
        y += h*(t+y);
        e = relative_Fehler(exakt, y, t);
        myfile << t << "\t" << y << "\t" << exakt (t) << "\t" << e << endl;
    }

    myfile.close();

}

int main (){
    const char* name1 = "h0.5.txt";
    const char* name2 = "h0.01.txt";
    EulerVerf(0.5, name1);
    EulerVerf(0.01, name2);

    //Plotten 
     system ( "gnuplot Plot_A3.gpl - ");
     
    return 0;
}

