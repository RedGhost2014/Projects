#include "Matrix.h"

Matrix* createMatrix(int rows, int columns)
{
	Matrix* newMatrix = (Matrix*)malloc(sizeof(Matrix));
	newMatrix->rows = rows;
	newMatrix->columns = columns;

	newMatrix->matrix = (int**)malloc(newMatrix->rows * sizeof(int*));
	for (int i = 0; i < newMatrix->rows; i++)
	{
		newMatrix->matrix[i] = (int*)malloc(newMatrix->columns * sizeof(int));
	}
	return newMatrix;
}

void fillRandomMatrix(Matrix* matrix)
{
	for (int i = 0; i < matrix->rows; i++)
	{
		for (int j = 0; j < matrix->columns; j++)
		{
			matrix->matrix[i][j] = (rand() % 30) - 15;
		}
	}
}