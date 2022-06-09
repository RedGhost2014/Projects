#pragma once
#ifndef CELL
#define CELL

#include <iostream>
#include <vector>
class Figure;

class Cell
{
private:
	size_t x;
	size_t y;
	bool enemyFigure;
public:
	Cell(size_t _x, size_t _y);
	Cell(size_t _x, size_t _y, bool isEnemyFigure);
	static Figure* getFigureInCell(size_t x, size_t y, std::vector<Figure*>* figures);

	bool isEnemy();
	size_t getCordX();
	size_t getCordY();
};

#endif // !CELL

