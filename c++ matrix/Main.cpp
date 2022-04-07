#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Matrix.h"

int main()
{
	srand(time(0));
	Matrix mat1(3, 3, "123.txt");
	Matrix mat2(3, 3, "111.txt");
	cout << "Matrix 1:" << endl;
	mat1.printMatrix();
	cout << endl;
	cout << "Matrix1[1][1] = " << ends;
	cout << mat1[1][1] << endl;

	mat1[1][1] = 12355;
	cout << endl;
	cout << "Matrix 1:" << endl;
	mat1.printMatrix();
	cout << endl;
	cout << "Matrix 2:" << endl;
	mat2.printMatrix();
	cout << endl;

	Matrix result = mat1;
	result = mat1 + mat2;
	result.printMatrix();
	cout << endl;

	result = mat1 + mat2;
	result.printMatrix();
	cout << endl;

	cout << "Determinant = " << result.getDeterminant() << endl;

	result.setRandomMatrix(100);
	result.printMatrix();
	cout << endl;

	cout << "Determinant = " << result.getDeterminant() << endl;
	cout << "Determinant = " << result.getDeterminant() << endl;

	return 0;
}