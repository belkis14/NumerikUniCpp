#include "MNF.h"

double* MNF(double a, double b, double c)
{
    double delta = b * b - 4 * a * c;

    if (delta > 0)
    {
        double* solutions = new double[2];
        solutions[0] = (-b + sqrt(delta)) / (2 * a);
        solutions[1] = (-b - sqrt(delta)) / (2 * a);
        return solutions;
    }
    else
    {
        return NULL;
    }
}