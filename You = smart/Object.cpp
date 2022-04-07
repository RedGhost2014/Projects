#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include "Declarator.h"

using namespace std;

Object::Object()
{

}

Object::~Object()
{

}

Object::Object(char c, int row, int column, bool _isMoveable)
{
	symbol = c;
	coordinate.X = column;
	coordinate.Y = row;
	isMoveable = _isMoveable;
}

void Object::setSettings(char c, int row, int column, bool _isMoveable)
{
	symbol = c;
	coordinate.X = column;
	coordinate.Y = row;
	isMoveable = _isMoveable;
}

bool Object::IsMoveable()
{
	return isMoveable;
}

char Object::getCharPortrait()
{
	return symbol;
}

void Object::setCharPortrait(char portrait)
{
	symbol = portrait;
}

void Object::setMovable(bool condition)
{
	isMoveable = condition;
}