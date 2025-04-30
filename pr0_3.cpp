#include <iostream>
#include <fstream>
#include <cmath>
#include "matrix_vector.h"

// /usr/bin/clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g '/Users/imanbelkis/Downloads/Programme/Programme C++/Aufgaben/Assignment_0/Exercise_3/pr0_3.cpp' '/Users/imanbelkis/Downloads/Programme/Programme C++/Aufgaben/Assignment_0/Exercise_3/matrix_vector.cpp' -o '/Users/imanbelkis/Downloads/Programme/Programme C++/Aufgaben/Assignment_0/Exercise_3/pr0_3'

int main()
{
	// Wir deklarieren die Namen für Input- und Outputdataien
	std::string inputFileName, outputFileName;

	// Wir lesen die Namen von Input- und Outputdataien
	std::cout << "Enter input file name: ";
	std::cin >> inputFileName;

	
	std::cout << "Enter output file name: ";
	std::cin >> outputFileName;

	// Wir öffnen die Inputdatei ( i = input ) 
	std::ifstream in(inputFileName);

	// Wir öffnen die Outputdatei ( o = output )
	std::ofstream out(outputFileName);

	// Wir überprüfen ob die Inputdatei offen ist
	if (!in.is_open())
	{
		std::cerr << "Error opening file " << inputFileName << std::endl;
		return -1;
	}

	// Wir überprüfen ob die Outputdatei offen ist
	if (!out.is_open())
	{
		std::cerr << "Error opening file " << outputFileName << std::endl; // cerr ist wie cin und cout aber für Fehlermeldungen
		return -1;
	}

	//  Wir deklarieren die Anzahl der Zeilen und Spalten der Matrix
	int nrRows, nrCols;

	// Wir lesen die Anzahl der Zeilen und Spalten der Matrix ein
	in >> nrRows >> nrCols;

	/* Wir deklarieren die Matrix und allokieren Speicherplatz dafür.
	- new ist ein Keyword, das Speicherplatz für eine neue Variable allokiert 
	- also wir nutzen es um Speicherplatz für eine Matrix zu allokieren (Matrix ist ein Pointer zu ein Pointer)
	 erste * ist für die Zeilen und zweite * ist für die Spalten 
	 
	*/

	// hier allokieren wir Speicherplatz für die Zeilen, wir allokieren Speicherplatz für jede Zeile aus unsere Matrix
	double **A = new double*[nrRows];

	
	// Allokierung für Spalten
	for (int i = 0; i < nrRows; i++)
	{
		A[i] = new double[nrCols];
	}

	/*
	 Kommentar für den obigen Code
	
		j
	  i 00 01 02 03 04
		10 11 12 13 14
		20 21 22 23 24
		30 31 32 33 34
		40 41 42 43 44

		[
			[1.1, 1.2, 1.3, 1.4, 1.5],
			[2.1, 2.2, 2.3, 2.4, 2.5],
			[3.1, 3.2, 3.3, 3.4, 3.5],
			[4.1, 4.2, 4.3, 4.4, 4.5],
			[5.1, 5.2, 5.3, 5.4, 5.5]
		]
	*/

	// Wir lesen die Matrix aus Inputdatei
	for (int i = 0; i < nrRows; i++)
	{
		for (int j = 0; j < nrCols; j++)
		{
			in >> A[i][j];
		}
	}

	// Wir deklarieren die Vektoren x und b und allokieren Speicherplatz dafür
	double *x = new double[nrCols];
	double *b = new double[nrRows];

	// Einlesen des Vektors x aus der Eingabedatei
	for (int i = 0; i < nrCols; i++)
	{
		in >> x[i];
	}

	// Aufruf der Funktion matrixVector
	matrixVector(A, x, b, nrRows, nrCols);

	// Schreiben des Ergenbnisses in die Ausgabedatei
	// Schreiben der Matrix A in die Ausgabedatei
	for (int i = 0; i < nrRows; i++)
	{
		for (int j = 0; j < nrCols; j++)
		{
			out << A[i][j] << " ";
		}
		out << std::endl;
	}

	// Schreiben des Vektor x in die Ausgabedatei
	for (int i = 0; i < nrCols; i++)
	{
		out << x[i] << " ";
	}

	out << std::endl;

	// Schreiben des Vektor b in die Ausgabedatei
	for (int i = 0; i < nrRows; i++)
	{
		out << b[i] << " ";
	}


	return 0;
}