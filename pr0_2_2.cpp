#include "MNF.h"

// /usr/bin/clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g '/Users/imanbelkis/Downloads/Programme/Programme C++/Aufgaben/Assignment_0/Exercise_2/Exercise_2_3/pr0_2_2.cpp' '/Users/imanbelkis/Downloads/Programme/Programme C++/Aufgaben/Assignment_0/Exercise_2/Exercise_2_3/MNF.cpp' -o '/Users/imanbelkis/Downloads/Programme/Programme C++/Aufgaben/Assignment_0/Exercise_2/Exercise_2_3/pr0_2_2'

// it needed to be compiled both MNF.cpp and pr0_2_2.cpp in order to work

int main()
{
    double a, b, c;
    std::cout << "Geben Sie die Werte für a, b und c" << std::endl;
    std::cin >> a >> b >> c;

    double *solutions = MNF(a, b, c);

    if (solutions == NULL)
    {
        std::cout << "Es gibt keine reele NST";
    }
    else if (solutions[1]) // Assuming delta was not zero and both roots are valid
    {
        std::cout << "Es gibt zwei reele NST, x1 = " << solutions[0] << " x2 = " << solutions[1];
        delete[] solutions;  // Ensure to delete if allocated
    }
    else  // This handles the case when delta is zero
    {
        std::cout << "Es gibt eine reele NST, x = " << solutions[0];
        delete[] solutions;  // Ensure to delete if allocated
    }

    return 0;
}
