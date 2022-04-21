#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct Matrix
{
	int rows;
	int columns;
	int** matrix;
} Matrix;

Matrix* createMatrix(int rows, int columns);
void fillRandomMatrix(Matrix* matrix);

// Функции для передачи в список
void clearMatrix(void** matrix);
void printMatrix(void** matrix);
void* copyMatrix(void* matrix);