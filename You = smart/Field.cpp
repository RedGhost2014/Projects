#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include "Declarator.h"

using namespace std;

int Field::getColumns()
{
	return this->columns;
}

int Field::getRows()
{
	return this->rows;
}

char** Field::getField()
{
	return this->charField;
}

Field::Field(int rows, int columns, bool noBorder)
{
	this->rows = rows;
	this->columns = columns;

	this->charField = new char*[this->rows];

	for (int i = 0; i < this->rows; i++)
	{
		this->charField[i] = new char[this->columns + 1];
		this->charField[i][this->columns] ='\0';
	}

	if (noBorder)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				this->charField[i][j] = ' ';
			}
		}
	}
	else
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				this->charField[i][j] = ' ';

				if (i == 0 || j == 0 || i == (this->rows - 1) || j == (this->columns - 1))
				{
					this->charField[i][j] = '#';
				}
			}
		}
	}
}

Field::~Field()
{
	for (int i = 0; i < this->rows; i++)
	{
		delete[] charField[i];
	}
	delete charField;
}

void Field::printField()
{
	for (int i = 0; i < this->rows; i++)
	{
		if (i == this->rows - 1)
		{
			cout << this->charField[i] << ends;
		}
		else
		{
			cout << this->charField[i] << endl;
		}
	}
}

void Field::printField(int rows, int columns)
{
	//gotoxy(columns, rows - 1);
	for (int i = 0; i < this->rows; i++)
	{
		if (i == this->rows - 1)
		{
			gotoxy(columns, rows + i);
			cout << this->charField[i] << ends;
		}
		else
		{
			gotoxy(columns, rows + i);
			cout << this->charField[i] << ends;
		}
	}
	gotoxy(0, 0);
}

void Field::clearField(bool ignoreWalls)
{
	if (ignoreWalls)
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				this->charField[i][j] = ' ';
			}
		}
	}
	else
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->columns; j++)
			{
				this->charField[i][j] = ' ';

				if (i == 0 || j == 0 || i == (this->rows - 1) || j == (this->columns - 1))
				{
					this->charField[i][j] = '#';
				}
			}
		}
	}
}