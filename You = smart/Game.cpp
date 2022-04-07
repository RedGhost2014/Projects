#include "Declarator.h"
#include <conio.h>

using namespace std;

Game::Game() { LevelSelectorWasLoad = false; }

Game::~Game()
{
	delete thisField;
}

void Game::addHero(char c, int row, int column, bool _isMoveable)
{
	if (!Hero)
	{
		this->Hero = new Object(c, row, column, _isMoveable);
		dir = Direction::Up;
		Singleton::getList()->push_back(Hero);
	}
}

void Game::addObject(char c, int row, int column, bool _isMoveable)
{
	if (thisField->getField()[row][column] == ' ')
	{
		Object* obj = new Object(c, row, column, _isMoveable);
		Singleton::getList()->push_back(obj);
	}
}

void Game::destroyObject(int row, int column)
{
	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end();)
	{
		Object* current = *iter;
		if (current->coordinate.X == column && current->coordinate.Y == row)
		{
			// Idk how and why this is working but let xD
			delete current;
			auto tmpwatcher = iter;
			tmpwatcher++;
			Singleton::getList()->erase(iter);
			iter = tmpwatcher;
		}
		else iter++;
	}
}

void Game::destroyEveryObject(char portrait)
{
	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end();)
	{
		Object* current = *iter;
		if (current->getCharPortrait() == portrait)
		{
			delete current;
			auto tmpwatcher = iter;
			tmpwatcher++;
			Singleton::getList()->erase(iter);
			iter = tmpwatcher;
		}
		else iter++;
	}
}

void Game::setField(int rows, int columns, bool noBorder)
{
	this->thisField = new Field(rows, columns, noBorder);
}

void Game::UserControl(char w, char s, char a, char d)
{
	int rows = thisField->getRows();
	int columns = thisField->getColumns();
	char** field = thisField->getField();

	int key = _getch();
	if (key != VK_LBUTTON && key != VK_RBUTTON)
	{
		if (key == w)
		{
			if (this->Hero->IsMoveable())
			{
				dir = Direction::Up;
				if (Hero->coordinate.Y - 1 > 0)
				{
					bool move = true;
					if (isContainObject(Hero->coordinate.Y - 1, Hero->coordinate.X))
					{
						Object* nearest = getObject(Hero->coordinate.Y - 1, Hero->coordinate.X);
						if (nearest->IsMoveable())
						{
							int ycord = Hero->coordinate.Y - 1;
							int xcord = Hero->coordinate.X;
							int count = 0;
							while (isContainObject(ycord, xcord) && ycord > 0 && getObject(ycord, xcord)->IsMoveable())
							{
								ycord--;
								count++;
							}

							ycord = Hero->coordinate.Y;
							xcord = Hero->coordinate.X;

							for (int i = count; i > 0; i--)
							{
								Object* tmpObject = getObject(ycord - count, xcord);
								if (tmpObject->IsMoveable() && (tmpObject->coordinate.Y - 1 > 0) &&
									(!isContainObject(tmpObject->coordinate.Y - 1, tmpObject->coordinate.X)))
								{
									tmpObject->coordinate.Y--;
								}
								else
								{
									move = false;
									break;
								}
								ycord += 1;
							}
							if (move)
								Hero->coordinate.Y--;
						}
					}
					else Hero->coordinate.Y--;

					// Движение только по одному блоку
					/*if (isContainObject(Hero->coordinate.Y - 1, Hero->coordinate.X))
					{
						Object* tmpObject = getObject(Hero->coordinate.Y - 1, Hero->coordinate.X);
						if (tmpObject->IsMoveable() && !isContainObject(tmpObject->coordinate.Y - 1, tmpObject->coordinate.X) && (tmpObject->coordinate.Y - 1 > 0))
						{
							tmpObject->coordinate.Y--;
							Hero->coordinate.Y--;
						}
					}
					else Hero->coordinate.Y--;*/
				}
			}
		}
		if (key == a)
		{
			if (this->Hero->IsMoveable())
			{
				dir = Direction::Left;
				if (Hero->coordinate.X - 1 > 0)
				{

					bool move = true;
					if (isContainObject(Hero->coordinate.Y, Hero->coordinate.X - 1))
					{
						Object* nearest = getObject(Hero->coordinate.Y, Hero->coordinate.X - 1);
						if (nearest->IsMoveable())
						{
							int ycord = Hero->coordinate.Y;
							int xcord = Hero->coordinate.X - 1;

							int count = 0;
							while (isContainObject(ycord, xcord) && xcord > 0 && getObject(ycord, xcord)->IsMoveable())
							{
								xcord--;
								count++;
							}

							ycord = Hero->coordinate.Y;
							xcord = Hero->coordinate.X;

							for (int i = count; i > 0; i--)
							{
								Object* tmpObject = getObject(ycord, xcord - count);
								if (tmpObject->IsMoveable() && (tmpObject->coordinate.X - 1 > 0) && !isContainObject(tmpObject->coordinate.Y, tmpObject->coordinate.X - 1))
								{
									tmpObject->coordinate.X--;
								}
								else
								{
									move = false;
									break;
								}
								xcord += 1;
							}
							if (move)
								Hero->coordinate.X--;
						}
					}
					else Hero->coordinate.X--;

					/*if (isContainObject(Hero->coordinate.Y, Hero->coordinate.X - 1))
					{
						Object* tmpObject = getObject(Hero->coordinate.Y, Hero->coordinate.X - 1);
						if (tmpObject->IsMoveable() && !isContainObject(tmpObject->coordinate.Y, tmpObject->coordinate.X - 1) && (tmpObject->coordinate.X - 1 > 0))
						{
							tmpObject->coordinate.X--;
							Hero->coordinate.X--;
						}
					}
					else Hero->coordinate.X--;*/
				}
			}
		}
		if (key == s)
		{
			if (this->Hero->IsMoveable())
			{
				dir = Direction::Down;
				if (Hero->coordinate.Y + 1 < rows - 1)
				{
					bool move = true;
					if (isContainObject(Hero->coordinate.Y + 1, Hero->coordinate.X))
					{
						Object* nearest = getObject(Hero->coordinate.Y + 1, Hero->coordinate.X);
						if (nearest->IsMoveable())
						{
							int ycord = Hero->coordinate.Y + 1;
							int xcord = Hero->coordinate.X;
							int count = 0;
							while (isContainObject(ycord, xcord) && ycord < rows - 1 && getObject(ycord, xcord)->IsMoveable())
							{
								ycord++;
								count++;
							}

							ycord = Hero->coordinate.Y;
							xcord = Hero->coordinate.X;

							for (int i = count; i > 0; i--)
							{
								Object* tmpObject = getObject(ycord + count, xcord);
								if (tmpObject->IsMoveable() && (tmpObject->coordinate.Y + 1 < rows - 1) && !isContainObject(tmpObject->coordinate.Y + 1, tmpObject->coordinate.X))
								{
									tmpObject->coordinate.Y++;
								}
								else
								{
									move = false;
									break;
								}
								ycord -= 1;
							}
							if (move)
								Hero->coordinate.Y++;
						}
					}
					else Hero->coordinate.Y++;

					/*if (isContainObject(Hero->coordinate.Y + 1, Hero->coordinate.X))
					{
						Object* tmpObject = getObject(Hero->coordinate.Y + 1, Hero->coordinate.X);
						if (tmpObject->IsMoveable() && !isContainObject(tmpObject->coordinate.Y + 1, tmpObject->coordinate.X) && (tmpObject->coordinate.Y + 1 < rows - 1))
						{
							tmpObject->coordinate.Y++;
							Hero->coordinate.Y++;
						}
					}
					else Hero->coordinate.Y++;*/
				}
			}
		}
		if (key == d)
		{
			if (this->Hero->IsMoveable())
			{
				dir = Direction::Right;
				if (Hero->coordinate.X + 1 < columns - 1)
				{
					bool move = true;
					if (isContainObject(Hero->coordinate.Y, Hero->coordinate.X + 1))
					{
						Object* nearest = getObject(Hero->coordinate.Y, Hero->coordinate.X + 1);
						if (nearest->IsMoveable())
						{
							int ycord = Hero->coordinate.Y;
							int xcord = Hero->coordinate.X + 1;

							int count = 0;
							while (isContainObject(ycord, xcord) && xcord < columns - 1 && getObject(ycord, xcord)->IsMoveable())
							{
								xcord++;
								count++;
							}

							ycord = Hero->coordinate.Y;
							xcord = Hero->coordinate.X;

							for (int i = count; i > 0; i--)
							{
								Object* tmpObject = getObject(ycord, xcord + count);
								if (tmpObject->IsMoveable() && (tmpObject->coordinate.X + 1 < columns - 1) && !isContainObject(tmpObject->coordinate.Y, tmpObject->coordinate.X + 1))
								{
									tmpObject->coordinate.X++;
								}
								else
								{
									move = false;
									break;
								}
								xcord -= 1;
							}
							if (move)
								Hero->coordinate.X++;
						}
					}
					else Hero->coordinate.X++;

					/*if (isContainObject(Hero->coordinate.Y, Hero->coordinate.X + 1))
					{
						Object* tmpObject = getObject(Hero->coordinate.Y, Hero->coordinate.X + 1);
						if (tmpObject->IsMoveable() && !isContainObject(tmpObject->coordinate.Y, tmpObject->coordinate.X + 1) && (tmpObject->coordinate.X + 1 < columns - 1))
						{
							tmpObject->coordinate.X++;
							Hero->coordinate.X++;
						}
					}
					else Hero->coordinate.X++;*/
				}
			}
		}

		if (key == VK_SPACE)
		{
			if (dir == Direction::Up)
			{
				if (isContainObject(Hero->coordinate.Y - 1, Hero->coordinate.X))
				{
					Object* tmpObject = getObject(Hero->coordinate.Y - 1, Hero->coordinate.X);
					if (tmpObject->IsMoveable() && !isContainObject(Hero->coordinate.Y + 1, Hero->coordinate.X) && (Hero->coordinate.Y + 1 < rows - 1))
					{
						tmpObject->coordinate.Y = Hero->coordinate.Y + 1;
					}
				}
			}
			else if (dir == Direction::Down)
			{
				if (isContainObject(Hero->coordinate.Y + 1, Hero->coordinate.X))
				{
					Object* tmpObject = getObject(Hero->coordinate.Y + 1, Hero->coordinate.X);
					if (tmpObject->IsMoveable() && !isContainObject(Hero->coordinate.Y - 1, Hero->coordinate.X) && (Hero->coordinate.Y - 1 > 0))
					{
						tmpObject->coordinate.Y = Hero->coordinate.Y - 1;
					}
				}
			}
			else if (dir == Direction::Left)
			{
				if (isContainObject(Hero->coordinate.Y, Hero->coordinate.X - 1))
				{
					Object* tmpObject = getObject(Hero->coordinate.Y, Hero->coordinate.X - 1);
					if (tmpObject->IsMoveable() && !isContainObject(Hero->coordinate.Y, Hero->coordinate.X + 1) && (Hero->coordinate.X + 1 < columns - 1))
					{
						tmpObject->coordinate.X = Hero->coordinate.X + 1;
					}
				}
			}
			else if (dir == Direction::Right)
			{
				if (isContainObject(Hero->coordinate.Y, Hero->coordinate.X + 1))
				{
					Object* tmpObject = getObject(Hero->coordinate.Y, Hero->coordinate.X + 1);
					if (tmpObject->IsMoveable() && !isContainObject(Hero->coordinate.Y, Hero->coordinate.X - 1) && (Hero->coordinate.X - 1 > 0))
					{
						tmpObject->coordinate.X = Hero->coordinate.X - 1;
					}
				}
			}
		}
	}
}

bool Game::isContainObject(int rows, int columns)
{
	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end(); iter++)
	{
		Object* tmpObject = *iter;
		if (tmpObject->coordinate.X == columns && tmpObject->coordinate.Y == rows)
			return true;
	}
	return false;
}

bool Game::isExistObject(char portrait)
{
	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end(); iter++)
	{
		Object* tmpObject = *iter;
		if (tmpObject->getCharPortrait() == portrait)
			return true;
	}
	return false;
}

Object* Game::getObject(int rows, int columns)
{
	Object* tmpObject = 0;
	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end(); iter++)
	{
		tmpObject = *iter;
		if (tmpObject->coordinate.X == columns && tmpObject->coordinate.Y == rows)
			return tmpObject;
	}
	return 0;
}

int Game::changeHero(int heroChangeState)
{
	if (heroChangeState == 0)
		return 0;
	else if (heroChangeState > 0)
	{
		Object* leftObject = this->getObject(this->equalSign->coordinate.Y, this->equalSign->coordinate.X - 1);
		Object* rightHero = this->Hero;

		this->Hero = leftObject;
		//this->
		this->Hero->setMovable(leftObject->IsMoveable());

		leftObject = rightHero;
		leftObject->setMovable(rightHero->IsMoveable());
		return 1;

		
	}
	else if (heroChangeState < 0)
	{
		this->Hero->setCharPortrait(this->getObject(this->equalSign->coordinate.Y, this->equalSign->coordinate.X + 1)->getCharPortrait());
		return -1;
	}
}


// Kinda overloaded methods

void Game::setObjectsOnField()
{
	char** field = thisField->getField();

	for (auto iter = Singleton::getList()->begin(); iter != Singleton::getList()->end(); iter++)
	{
		Object* tmpObject = *iter;
		field[tmpObject->coordinate.Y][tmpObject->coordinate.X] = tmpObject->getCharPortrait();
	}
}

void Game::clearField(bool ignoreWalls)
{
	this->thisField->clearField(ignoreWalls);
}

void Game::printField()
{
	this->thisField->printField();
}

void Game::printField(int rows, int columns)
{
	this->thisField->printField(rows, columns);
}

void Game::deleteField()
{
	delete this->thisField;
	this->thisField = 0;
}

void Game::printEqualSignAnim(int row, int column, bool isSkinChange)
{
	if (isSkinChange)
	{
		gotoxy(this->equalSign->coordinate.X + column, this->equalSign->coordinate.Y + row - 1);
		cout << "<-";
		Sleep(300);
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1);
		cout << "   ";
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1);
		cout << "<-";
		Sleep(300);
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1);
		cout << "   ";
	}
	else
	{
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1 );
		cout << '/';
		gotoxy(this->equalSign->coordinate.X + column + 1, this->equalSign->coordinate.Y + row - 1 );
		cout << '\\';
		Sleep(300);
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1 );
		cout << "   ";
		gotoxy(this->equalSign->coordinate.X + column, this->equalSign->coordinate.Y + row - 1 );
		cout << '-';
		Sleep(300);
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1 );
		cout << "   ";
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1 );
		cout << '/';
		gotoxy(this->equalSign->coordinate.X + column + 1, this->equalSign->coordinate.Y + row - 1 );
		cout << '\\';
		Sleep(300);
		gotoxy(this->equalSign->coordinate.X + column - 1, this->equalSign->coordinate.Y + row - 1 );
		cout << "   ";
	}
}