#pragma once
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Matrix.h"
#include <stdarg.h>

void Matrix::setRandomMatrix(int border = 10)
{
	this->detWasCalculated = false;
	if (!matrix)
	{
		return;
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				matrix[i][j] = (rand() % border) - (border / 2);
			}
		}
	}
}

void Matrix::setFromConsole()
{
	this->detWasCalculated = false;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cin >> matrix[i][j];
			//cout << " ";
		}
		cout << endl;
	}
}

Matrix::Matrix(const Matrix& thismatrix)
{
	this->~Matrix();
	this->rows = thismatrix.rows;
	this->columns = thismatrix.columns;
	matrix = new int* [rows];

	this->det = 0;
	this->detWasCalculated = false;

	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->columns; j++)
		{
			this->matrix[i][j] = thismatrix.matrix[i][j];
		}
	}
}

Matrix::Matrix(int x, int y)
{
	this->~Matrix();
	rows = x;
	columns = y;

	this->det = 0;
	this->detWasCalculated = false;

	matrix = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}
}

Matrix::Matrix(int x, int y, string str)
{
	this->~Matrix();
	rows = x;
	columns = y;

	this->det = 0;
	this->detWasCalculated = false;

	matrix = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
	}

	ifstream myifStream(str);
	if (myifStream)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				myifStream >> matrix[i][j];
			}
		}
		myifStream.close();
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete matrix;
}

void Matrix::printMatrix()
{
	cout << "Your matrix:" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void Matrix::printMatrixFile(string str = nullptr)
{
	ofstream myofstream(str);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			myofstream << matrix[i][j] << " ";
		}
		myofstream << endl;
	}
	myofstream.close();
}

int Matrix::getDeterminant()
{
	if (!this->detWasCalculated)
		calculateDeterminant();
	return det;
}

void Matrix::calculateDeterminant()
{
	this->detWasCalculated = true;
	det = DeterFind(matrix, rows, columns);
}

int Matrix::DeterFind(int** matrix, int row, int column)
{
	int determinant = 0;

	int N = row;
	if (row == 1 && column == 1)
	{
		return 1;
	}
	if (row == 2 && column == 2)
	{
		int x = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
		return x;
	}
	else
	{
		for (int ColumnIncrem = 0; ColumnIncrem < N; ColumnIncrem++)
		{
			//int** tmpMatrix = (int**)malloc((N - 1) * sizeof(int*));
			int** tmpMatrix = new int* [N - 1];
			for (int i = 0; i < N - 1; i++)
			{
				//tmpMatrix[i] = (int*)malloc((N - 1) * sizeof(int));
				tmpMatrix[i] = new int[N - 1];
			}
			for (int i = 0; i < N - 1; i++)
			{
				for (int j = 0; j < N - 1; j++)
				{
					if (j < ColumnIncrem)
					{
						tmpMatrix[i][j] = matrix[i + 1][j];
					}
					else tmpMatrix[i][j] = matrix[i + 1][j + 1];
				}
			}
			// Debugging here
			//printf("\nYour resulted %d matrix is:\n", ColumnIncrem);
			//printMatrix(tmpMatrix, N-1, N-1);
			//printf("Will be multiplied on %d\n", matrix[0][ColumnIncrem]);

			if (ColumnIncrem % 2 == 0)
			{
				determinant += matrix[0][ColumnIncrem] * DeterFind(tmpMatrix, N - 1, N - 1);
			}
			else determinant += (-1) * matrix[0][ColumnIncrem] * DeterFind(tmpMatrix, N - 1, N - 1);
			for (int i = 0; i < N - 1; i++)
				//free(tmpMatrix[i]);
				delete[] tmpMatrix[i];
			//free(tmpMatrix);
			delete[] tmpMatrix;
		}
	}
	return determinant;
}

Matrix& operator+(const Matrix& left, const Matrix& right)
{
	Matrix* result = new Matrix(left.rows, left.columns);
	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->columns; j++)
		{
			result->matrix[i][j] = left.matrix[i][j] + right.matrix[i][j];
		}
	}

	return *result;
}

Matrix& operator-(const Matrix& left, const Matrix& right)
{
	Matrix* result = new Matrix(left.rows, left.columns);

	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->columns; j++)
		{
			result->matrix[i][j] = left.matrix[i][j] - right.matrix[i][j];
		}
	}

	return *result;
}

Matrix& operator*(const Matrix& left, const Matrix& right)
{
	Matrix* result = new Matrix(left.rows, right.columns);

	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->columns; j++)
		{
			result->matrix[i][j] = left.matrix[i][j] - right.matrix[i][j];
		}
	}

	for (int i = 0; i < result->rows; i++)
	{
		for (int j = 0; j < result->columns; j++)
		{
			int sum = 0;
			for (int k = 0; k < left.columns; k++)
			{
				sum = sum + left.matrix[i][k] * right.matrix[k][j];
			}
			result->matrix[i][j] = sum;
		}
	}

	return *result;
}

int* Matrix::operator[](int index)
{
	return this->matrix[index];
}