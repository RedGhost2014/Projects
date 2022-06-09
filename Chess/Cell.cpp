#include <iostream>
#include <vector>
#include "Figure.h"
#include "Cell.h"

Figure* Cell::getFigureInCell(size_t x, size_t y, std::vector<Figure*>* figures)
{
	for (size_t i = 0; i < figures[0].size(); i++)
	{
		if (x == figures[0][i]->getX() && y == figures[0][i]->getY() && figures[0][i]->isAlive())
			return figures[0][i];
	}
	return nullptr;
}

size_t Cell::getCordX() { return x; };
size_t Cell::getCordY() { return y; };

bool Cell::isEnemy()
{
	return enemyFigure;
}

Cell::Cell(size_t _x, size_t _y) : x(_x), y(_y), enemyFigure(false) {};
Cell::Cell(size_t _x, size_t _y, bool isEnemyFigure) : x(_x), y(_y), enemyFigure(isEnemyFigure) {};