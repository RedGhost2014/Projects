#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

class Matrix
{
private:
	int rows;
	int columns;
	int** matrix;
	int det;

	bool detWasCalculated;

	int DeterFind(int** matrix, int row, int column);
	void calculateDeterminant();

public:
	Matrix() = delete;
	Matrix(int x, int y);
	Matrix(const Matrix& thismatrix);
	Matrix(int x, int y, string str);
	~Matrix();

	void setFromConsole();
	void setRandomMatrix(int border);

	void printMatrix();
	void printMatrixFile(string str);

	int getDeterminant();

	int getRows()
	{
		return rows;
	}
	int getColumns()
	{
		return columns;
	}

	int* operator[](int index1);

	friend Matrix& operator+(const Matrix &left, const Matrix &right);
	friend Matrix& operator-(const Matrix &left, const Matrix &right);
	friend Matrix& operator*(const Matrix &left, const Matrix &right);
};