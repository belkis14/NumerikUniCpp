#include <iostream>
#include <math.h>


int main()
{
    // Deklaration
    double a, b, c, x1, x2, delta;

    // Eingabeaufforderung
    std::cout << "Geben Sie die Werte für a, b und c" << std::endl;

    // Eingabebefehl
    std::cin >> a >> b >> c;

    // Gleichungen
    delta = b * b - 4 * a * c;
    if (delta > 0)
    {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);
        // Ausgabe
        std::cout << "x1 ist" << x1 << " und x2 ist " << x2 << std::endl;
    }
    else if(delta == 0)
    {
        std::cout << "x1 = x2 = " << -b / (2 * a);
    }
    else
    {
        std::cout << "Es gibt keine reelle Nullstellen.";
    }

    return 0;
}