#include "Field.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

Field::Field() {}

char** Field::getCharField()
{
	return field;
}

short Field::getColumns()
{
	return columns;
}

short Field::getRows()
{
	return rows;
}

void Field::clearField()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (this->field[i][j] != '#')
				this->field[i][j] = ' ';
		}
	}
}

void Field::printField()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << this->field[i][j];
		}
		cout << endl;
	}
}

Field::Field(short rows, short columns)
{
	this->rows = rows;
	this->columns = columns;
	this->field = new char*[this->rows];

	for (int i = 0; i < this->rows; i++)
	{
		this->field[i] = new char[this->columns];
	}

	int i = 0;
	int j = 0;

	for (i = 0; i < this->rows; i++)
	{
		for (j = 0; j < this->columns; j++)
		{
			this->field[i][j] = ' ';
			if (i == 0 || j == 0 || i == (this->rows - 1) || j == (this->columns - 1))
				this->field[i][j] = '#';
		}
	}
}

Field::~Field()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] field[i];
	}
	delete field;
}

Builder::Builder() {}

Builder::Builder(short rows, short columns, short style)
{
	this->setSize(rows, columns);
	this->setStyle(style);
}

void Builder::setSize(short rows, short columns)
{
	this->rows = rows;
	this->columns = columns;
}

void Builder::setStyle(short style)
{
	this->style = style;
}

void Builder::buildbyReference(Field* newfield)
{
	newfield->rows = this->rows;
	newfield->columns = this->columns;
	newfield->field = new char* [newfield->rows+1];

	for (int i = 0; i < newfield->rows; i++)
	{
		newfield->field[i] = new char[newfield->columns+1];
	}

	int i = 0;
	int j = 0;

	for (i = 0; i < newfield->rows; i++)
	{
		for (j = 0; j < newfield->columns; j++)
		{
			newfield->field[i][j] = ' ';
		}
		newfield->field[i][j] = '\0';
	}

	if (style & FSTYLE_SQUARE)
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < newfield->rows; i++)
		{
			for (j = 0; j < newfield->columns; j++)
			{
				if (i == 0 || j == 0 || i == (newfield->rows - 1) || j == (newfield->columns - 1))
					newfield->field[i][j] = '#';
			}
		}
	}

	if (style & FSTYLE_HDASH)
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < newfield->rows; i++)
		{
			for (j = 0; j < newfield->columns; j++)
			{
				if (i == newfield->rows / 2)
					newfield->field[i][j] = '#';
			}
		}
	}

	if (style & FSTYLE_VDASH)
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < newfield->rows; i++)
		{
			for (j = 0; j < newfield->columns; j++)
			{
				if (j == newfield->rows / 2)
					newfield->field[i][j] = '#';
			}
		}
	}

	if (style & FSTYLE_BACKSLASH)
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < newfield->rows; i++)
		{
			for (j = 0; j < newfield->columns; j++)
			{
				if (i == j)
					newfield->field[i][j] = '#';
			}
		}
	}

	if (style & FSTYLE_SLASH)
	{
		int i = 0;
		int j = 0;
		for (i = 0; i < newfield->rows; i++)
		{
			for (j = 0; j < newfield->columns; j++)
			{
				if (i == (this->columns - j - 1))
					newfield->field[i][j] = '#';
			}
		}
	}
}
