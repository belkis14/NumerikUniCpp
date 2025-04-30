void matrixVector(double** matrix, double* x, double* b, int nrRows, int nrCols)
{
	for (int i = 0; i < nrRows; i++)
	{
		b[i] = 0;
		for (int j = 0; j < nrCols; j++)
		{
			b[i] += matrix[i][j] * x[j]; 
		}
	}
}