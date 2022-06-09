#include <raylibcpp/include/raylib-cpp.hpp>
#include "Figure.h"

std::vector<Cell*>* Figure::getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs)
{
	return nullptr;
}
void Figure::MoveTo(size_t newX, size_t newY)
{
	X = newX;
	Y = newY;
}

Figure& Figure::setName(std::string& name)
{
	figurename = name;
	return *this;
}
Figure& Figure::setTexture(const raylib::Texture& _texture)
{
	texture = _texture;
	return *this;
}
Figure& Figure::setColor(FigureColor _color)
{
	color = _color;
	return *this;
};
Figure& Figure::setXY(size_t x = 0, size_t y = 0)
{
	X = x;
	Y = y;
	return *this;
}
Figure& Figure::setType(FigureType type)
{
	figuretype = type;
	return *this;
}
Figure& Figure::setFirstMove(bool move)
{
	isfirstmove = move;
	return *this;
}

Figure& Figure::setAliveMode(bool alive)
{
	isalive = alive;
	return *this;
}

raylib::Texture& Figure::getTexture()
{
	return texture;
}
size_t Figure::getX()
{
	return X;
}
size_t Figure::getY()
{
	return Y;
}
Figure::FigureType& Figure::getType()
{
	return figuretype;
}
Figure::FigureColor& Figure::getColor()
{
	return color;
}
bool Figure::isFirstMove()
{
	return isfirstmove;
}
bool Figure::isAlive()
{
	return isalive;
}
Figure::Figure()
{
	isfirstmove = true;
	isalive = true;
};
Figure::~Figure() {};



std::vector<Cell*>* Pawn::getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs)
{
	std::vector<Cell*>* moves = new std::vector<Cell*>;

	int x = this->getX();
	int y = this->getY();

	/*int pos = -1;
	if (this->getColor() == FigureColor::FIGURE_WHITE)
	{
		pos = y - 1;
	}
	else if (this->getColor() == FigureColor::FIGURE_BLACK)
	{
		pos = y + 1;
	}*/

	if (this->getColor() == FigureColor::FIGURE_WHITE)
	{
		if (y - 1 >= 0 && (Cell::getFigureInCell(x, y - 1, &figures) == nullptr))
		{
			moves->push_back(new Cell(x, y - 1));
			if (this->isFirstMove())
			{
				if (Cell::getFigureInCell(x, y - 2, &figures) == nullptr)
				{
					moves->push_back(new Cell(x, y - 2));
				}
			}
		}
		Figure* enemy1 = nullptr;
		Figure* enemy2 = nullptr;
		if (x - 1 >= 0)
			enemy1 = Cell::getFigureInCell(x - 1, y - 1, &figures);
		if (x + 1 <= gs.getWidthSize())
			enemy2 = Cell::getFigureInCell(x + 1, y - 1, &figures);
		if (enemy1 != nullptr && enemy1->getColor() != this->getColor())
		{
			moves->push_back(new Cell(enemy1->getX(), enemy1->getY(), true));
		}
		if (enemy2 != nullptr && enemy2->getColor() != this->getColor())
		{
			moves->push_back(new Cell(enemy2->getX(), enemy2->getY(), true));
		}
	}
	else if (this->getColor() == FigureColor::FIGURE_BLACK)
	{
		if (y + 1 < gs.getHeightSize() && (Cell::getFigureInCell(x, y + 1, &figures) == nullptr))
		{
			moves->push_back(new Cell(x, y + 1));
			if (this->isFirstMove())
			{
				if (Cell::getFigureInCell(x, y + 2, &figures) == nullptr)
				{
					moves->push_back(new Cell(x, y + 2));
				}
			}
		}
		Figure* enemy1 = nullptr;
		Figure* enemy2 = nullptr;
		if (x - 1 >= 0)
			enemy1 = Cell::getFigureInCell(x - 1, y + 1, &figures);
		if (x + 1 <= gs.getWidthSize())
			enemy2 = Cell::getFigureInCell(x + 1, y + 1, &figures);
		if (enemy1 != nullptr && enemy1->getColor() != this->getColor())
		{
			moves->push_back(new Cell(enemy1->getX(), enemy1->getY(), true));
		}
		if (enemy2 != nullptr && enemy2->getColor() != this->getColor())
		{
			moves->push_back(new Cell(enemy2->getX(), enemy2->getY(), true));
		}
	}

	return moves;
}
Pawn::Pawn() = default;
Pawn::~Pawn() = default;


std::vector<Cell*>* Rook::getPossibleMoves(std::vector<Figure*>&figures, GameSettings & gs)
{
	std::vector<Cell*>* moves = new std::vector<Cell*>;

	int x = this->getX();
	int y = this->getY();

	for (int i = x; i < gs.getWidthSize(); i++)
	{
		Figure* fig = Cell::getFigureInCell(i, y, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, y));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, y, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x; i >= 0; i--)
	{
		Figure* fig = Cell::getFigureInCell(i, y, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, y));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, y, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = y; i >= 0; i--)
	{
		Figure* fig = Cell::getFigureInCell(x, i, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x, i));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(x, i, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = y; i < gs.getHeightSize(); i++)
	{
		Figure* fig = Cell::getFigureInCell(x, i, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x, i));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(x, i, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	return moves;
}
Rook::Rook() = default;
Rook::~Rook() = default;

std::vector<Cell*>* Bishop::getPossibleMoves(std::vector<Figure*>&figures, GameSettings & gs)
{
	std::vector<Cell*>* moves = new std::vector<Cell*>;

	int x = this->getX();
	int y = this->getY();

	for (int i = x, j = y; i < gs.getWidthSize() && j < gs.getHeightSize(); i++, j++)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x, j = y; i >= 0 && j < gs.getHeightSize(); i--, j++)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x, j = y; i >= 0 && j >= 0; i--, j--)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x, j = y; i < gs.getWidthSize() && j >= 0; i++, j--)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	return moves;
}
Bishop::Bishop() = default;
Bishop::~Bishop() = default;

std::vector<Cell*>* Knight::getPossibleMoves(std::vector<Figure*>&figures, GameSettings & gs)
{
	std::vector<Cell*>* moves = new std::vector<Cell*>;

	int x = this->getX();
	int y = this->getY();

	Figure* fig = nullptr;

	if (x + 1 < gs.getWidthSize() && y + 2 < gs.getHeightSize())
	{
		fig = Cell::getFigureInCell(x + 1, y + 2, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x + 1, y + 2, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x + 1, y + 2, true));
		}
	}

	if (x - 1 >= 0 && y + 2 < gs.getHeightSize())
	{
		fig = Cell::getFigureInCell(x - 1, y + 2, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x - 1, y + 2, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x - 1, y + 2, true));
		}
	}

	if (x - 1 >= 0 && y - 2 >= 0)
	{
		fig = Cell::getFigureInCell(x - 1, y - 2, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x - 1, y - 2, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x - 1, y - 2, true));
		}
	}

	if (x + 1 < gs.getWidthSize() && y - 2 >= 0)
	{
		fig = Cell::getFigureInCell(x + 1, y - 2, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x + 1, y - 2, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x + 1, y - 2, true));
		}
	}

	if (x + 2 < gs.getWidthSize() && y + 1 < gs.getHeightSize())
	{
		fig = Cell::getFigureInCell(x + 2, y + 1, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x + 2, y + 1, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x + 2, y + 1, true));
		}
	}

	if (x + 2 < gs.getWidthSize() && y - 1 >= 0)
	{
		fig = Cell::getFigureInCell(x + 2, y - 1, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x + 2, y - 1, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x + 2, y - 1, true));
		}
	}


	if (x - 2 >= 0 && y + 1 < gs.getHeightSize())
	{
		fig = Cell::getFigureInCell(x - 2, y + 1, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x - 2, y + 1, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x - 2, y + 1, true));
		}
	}


	if (x - 2 >= 0 && y - 1 >= 0)
	{
		fig = Cell::getFigureInCell(x - 2, y - 1, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x - 2, y - 1, false));
		}
		else if (this->getColor() != fig->getColor())
		{
			moves->push_back(new Cell(x - 2, y - 1, true));
		}
	}

	return moves;
}
Knight::Knight() = default;
Knight::~Knight() = default;



std::vector<Cell*>* King::getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs)
{
	std::vector<Cell*>* moves = new std::vector<Cell*>;

	int x = this->getX();
	int y = this->getY();

	Figure* fig = nullptr;

	for (int i = x - 1, times = 0; times < 3; i++, times++)
	{
		if (i >= 0 && i < gs.getWidthSize() && y + 1 < gs.getHeightSize())
		{
			fig = Cell::getFigureInCell(i, y + 1, &figures);
			if (fig == nullptr)
			{
				moves->push_back(new Cell(i, y + 1, false));
			}
			else if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, y + 1, true));
			}
		}

		if (i >= 0 && i < gs.getWidthSize() && y < gs.getHeightSize())
		{
			fig = Cell::getFigureInCell(i, y, &figures);
			if (fig == nullptr)
			{
				moves->push_back(new Cell(i, y, false));
			}
			else if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, y, true));
			}
		}

		if (i >= 0 && i < gs.getWidthSize() && y - 1 >= 0)
		{
			fig = Cell::getFigureInCell(i, y - 1, &figures);
			if (fig == nullptr)
			{
				moves->push_back(new Cell(i, y - 1, false));
			}
			else if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, y - 1, true));
			}
		}
	}

	if (this->isFirstMove())
	{
		Figure* leftRook = Cell::getFigureInCell(x + 3, y, &figures);
		Figure* rightRook = Cell::getFigureInCell(x - 4, y, &figures);

		if (leftRook->isFirstMove())
		{
			bool isFreeSpace = true;

			for (int i = x + 1; i < gs.getWidthSize() - 1; i++)
			{
				fig = Cell::getFigureInCell(i, y, &figures);
				if (fig != nullptr)
				{
					isFreeSpace = false;
					break;
				}
			}

			if (isFreeSpace)
			{
				moves->push_back(new Cell(x + 2, y, false));
			}
		}

		if (rightRook->isFirstMove())
		{
			bool isFreeSpace = true;

			for (int i = x - 1; i >= 1; i--)
			{
				fig = Cell::getFigureInCell(i, y, &figures);
				if (fig != nullptr)
				{
					isFreeSpace = false;
					break;
				}
			}

			if (isFreeSpace)
			{
				moves->push_back(new Cell(x - 2, y, false));
			}
		}
	}

	return moves;
}
King::King() = default;
King::~King() = default;


std::vector<Cell*>* Queen::getPossibleMoves(std::vector<Figure*>& figures, GameSettings& gs)
{
	std::vector<Cell*>* moves = new std::vector<Cell*>;

	int x = this->getX();
	int y = this->getY();

	Figure* fig = nullptr;

	for (int i = x, j = y; i < gs.getWidthSize() && j < gs.getHeightSize(); i++, j++)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x, j = y; i >= 0 && j < gs.getHeightSize(); i--, j++)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x, j = y; i >= 0 && j >= 0; i--, j--)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x, j = y; i < gs.getWidthSize() && j >= 0; i++, j--)
	{
		Figure* fig = Cell::getFigureInCell(i, j, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, j));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, j, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}
	
	for (int i = x; i < gs.getWidthSize(); i++)
	{
		Figure* fig = Cell::getFigureInCell(i, y, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, y));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, y, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = x; i >= 0; i--)
	{
		Figure* fig = Cell::getFigureInCell(i, y, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(i, y));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(i, y, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = y; i >= 0; i--)
	{
		Figure* fig = Cell::getFigureInCell(x, i, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x, i));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(x, i, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	for (int i = y; i < gs.getHeightSize(); i++)
	{
		Figure* fig = Cell::getFigureInCell(x, i, &figures);
		if (fig == nullptr)
		{
			moves->push_back(new Cell(x, i));
		}
		else
		{
			if (this->getColor() != fig->getColor())
			{
				moves->push_back(new Cell(x, i, true));
				break;
			}
			else if (this->getColor() == fig->getColor() && this != fig)
			{
				break;
			}
		}
	}

	return moves;
}
Queen::Queen() = default;
Queen::~Queen() = default;