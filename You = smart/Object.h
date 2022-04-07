#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>

using namespace std;

class Object;

class Object
{
private:

	char symbol;
	bool isMoveable;

public:
	
	COORD coordinate;

	char getCharPortrait();
	void setCharPortrait(char portrait);
	void setMovable(bool condition);

	Object();
	~Object();
	Object(char c, int row, int column, bool _isMoveable);

	bool IsMoveable();
	void setSettings(char c, int row, int column, bool _isMoveable);
	//void setCoordinates();
};
