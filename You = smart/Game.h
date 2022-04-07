#pragma once
#include <iostream>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include "Declarator.h"
#include "Comparser.h"

using namespace std;

class Game : private Field
{
private:

	// Enum technically belongs to Hero cause of object move mechanic
	enum class Direction
	{
		Up,
		Left,
		Down,
		Right
	};

public:
	Game();
	~Game();

	Direction dir;
	bool LevelSelectorWasLoad;
	Object* level1;
	Object* level2;
	Object* level3;
	Object* level4;
	//list <Object> List;

	Field* thisField;
	Object* Hero;
	Object* equalSign;
	void printEqualSignAnim(int row, int column, bool isSkinChange);

	Comparser comparser;

	void addHero(char c, int row, int column, bool _isMoveable);
	int changeHero(int heroChangeState);
	void UserControl(char w, char s, char a, char d);


	bool isContainObject(int rows, int columns);
	bool isExistObject(char portrait);
	Object* getObject(int rows, int columns);
	void addObject(char c, int row, int column, bool _isMoveable);
	void destroyObject(int row, int column);
	void destroyEveryObject(char portrait);


	void setField(int rows, int columns, bool noBorder);
	void setObjectsOnField();
	void clearField(bool ignoreWalls);
	void printField(int rows, int columns);
	void printField();
	void deleteField();
};
