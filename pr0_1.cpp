#include <iostream>

// Dieses Programm fordert die Eingabe eines Integers und gibt diesen wieder in der Kosole aus
int main (){

//Deklaration 
    double faraday, celsius;

//Eingabeaufforderung

std::cout << "Geben Sie eine Temperatur faraday =" << std::endl;

// Eingabebefehl
std::cin >> faraday;

// Gleichung
celsius = (faraday - 32)*5/9; // wir haben am Ende 5/9 gelassen damit es als double betrachtet, sonst wird es als int betrachtet 

//Ausgabe
std::cout << "Temperatur: " << faraday << "F="<< celsius <<"°C"<< std::endl;

return 0;
} 