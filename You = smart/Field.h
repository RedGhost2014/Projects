#pragma once
//#include "Object.h"
#include "Declarator.h"

class Field
{
private:

	int rows;
	int columns;

	char** charField;

public:
	Field() {};
	Field(int rows, int columns, bool noBorder);
	~Field();

	int getRows();
	int getColumns();
	char** getField();

	void printField();
	void printField(int rows, int columns);
	void clearField(bool ignoreWalls);
};