#include "Matrix.h"
// Описываемый пользователем "класс" и его функции
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

void clearMatrix(void** element)
{
	Matrix* thismatrix = (Matrix*)*element;

	if (thismatrix != 0)
	{
		for (int i = 0; i < thismatrix->rows; i++)
		{
			free(thismatrix->matrix[i]);
		}
		free(thismatrix->matrix);
		free(thismatrix);

		thismatrix = 0;
		*element = 0;
	}
}
void printMatrix(void** element)
{
	Matrix* thismatrix = (Matrix*)*element;
	if (element == 0 || thismatrix == 0)
	{
		printf("Matrix on adress \"%p\" does not exist or null-pointer\n", element);
		return;
	}
	else
	{
		for (int i = 0; i < thismatrix->rows; i++)
		{
			for (int j = 0; j < thismatrix->columns; j++)
			{
				printf("%2d  ", thismatrix->matrix[i][j]);
			}
			printf("\n");
		}
	}
	printf("\n");
}

void* copyMatrix(void* matrix)
{
	Matrix* thismatrix = (Matrix*)matrix;
	Matrix* newmatrix = createMatrix(thismatrix->rows, thismatrix->columns);
	for (int i = 0; i < thismatrix->rows; i++)
	{
		for (int j = 0; j < thismatrix->columns; j++)
		{
			newmatrix->matrix[i][j] = thismatrix->matrix[i][j];
		}
	}
	return newmatrix;
}