#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <omp.h>
#include "Stuff.hpp"
#include "Elevator.hpp"

using namespace std;

Elevator::Elevator(short floorsCount)
{
	this->mode = 0;
	this->floorsCount = floorsCount;
	this->field = new char* [floorsCount];

	for (short i = 0; i < floorsCount; i++)
	{
		this->field[i] = new char[2 + 1];
	}
	for (short i = 0; i < floorsCount; i++)
	{
		this->field[i][0] = '|';
		this->field[i][1] = '|';
		this->field[i][2] = '\0';
	}

	this->field[this->floorsCount - 1][1] = '_';
	this->currentfloor = this->floorsCount - 1;
	this->targetfloorOfHuman = -1;
	this->targetfloortoHuman = -1;
	this->currentTarget = -1;
}

int Elevator::getCurrentFloor()
{
	return this->currentfloor;
}

int Elevator::isActive()
{
	return mode;
}

void Elevator::ActiveState(int state)
{
	this->mode = state;
}

char** Elevator::getField()
{
	return field;
}

void Elevator::setTargetFloor(int floorTo, int floorOf)
{
	this->currentTarget = floorTo;
	this->targetfloortoHuman = floorTo;
	this->targetfloorOfHuman = floorOf;
}

Elevator::~Elevator()
{
	for (short i = 0; i < this->floorsCount; i++)
	{
		delete[] this->field[i];
	}
	delete[] this->field;
}

bool Elevator::move()
{
	if (this->currentTarget > 0 && this->currentTarget < this->floorsCount)
	{
		if (this->mode > 0)
		{
			if (this->currentfloor > currentTarget)
			{
				this->field[this->currentfloor][1] = '|';
				this->currentfloor--;
				this->field[this->currentfloor][1] = '_';
			}
			else if (this->currentfloor < currentTarget)
			{
				this->field[this->currentfloor][1] = '|';
				this->currentfloor++;
				this->field[this->currentfloor][1] = '_';
			}
			if (this->currentfloor == currentTarget && this->currentTarget > 0)
			{
				this->targetfloortoHuman = -1;
				this->currentTarget = abs(this->floorsCount - targetfloorOfHuman);
				this->ActiveState(-1);
				return true;
			}
		}
		else if (mode < 0)
		{
			if (this->currentfloor > currentTarget)
			{
				this->field[this->currentfloor][1] = '|';
				this->currentfloor--;
				this->field[this->currentfloor][1] = '_';
			}
			else if (this->currentfloor < currentTarget)
			{
				this->field[this->currentfloor][1] = '|';
				this->currentfloor++;
				this->field[this->currentfloor][1] = '_';
			}
			if (this->currentfloor == currentTarget && this->currentTarget > 0)
			{
				this->targetfloortoHuman = -1;
				this->targetfloorOfHuman = -1;
				this->currentTarget = -1;
				this->ActiveState(0);
				return true;
			}
		}
		return false;
	}
	return false;
}








Observer::Observer()
{
	
}

Observer::~Observer()
{
	for (int i = 0; i < 4; i++)
	{
		delete elevators[i];
	}
}

void Observer::setElevators(short floorsCount = 0)
{
	for (int i = 0; i < 4; i++)
	{
		this->elevators[i] = new Elevator(floorsCount);
	}

	this->floorsCount = floorsCount;
}

void Observer::gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void Observer::printElevators()
{
	int pos = 0;

	for (int count = 0; count < 4; count++)
	{
		gotoxy(pos, 0);
		for (int i = 0; i < this->floorsCount; i++)
		{
			gotoxy(pos, i);
			for (int j = 0; j < 2; j++)
			{
				cout << this->elevators[count]->getField()[i][j];
			}
		}
		pos += 30;
	}
}

void Observer::CommandListener()
{
	gotoxy(0, this->floorsCount + 3);
	cout << "Click to call elevator:" << endl;
	while (1)
	{
		while (!_kbhit())
		{
			gotoxy(0, 0);
			CommandAnalyzer(0, 0);
			//thread thr(test);
			this->printElevators();
			Sleep(1000);
		}
		_getch_nolock();
		gotoxy(0, this->floorsCount + 4);
		ShowConsoleCursor(TRUE);
		cout << "Enter the floor you are on: " << ends;
		char* currentfloor = strGet();
		int cfloor = atoi(currentfloor);
		delete[] currentfloor;
		cout << "Enter the target floor: " << ends;
		char* targetfloor = strGet();
		int tfloor = atoi(targetfloor);
		delete[] targetfloor;
		gotoxy(0, this->floorsCount + 4);
		ShowConsoleCursor(FALSE);
		CommandAnalyzer(cfloor, tfloor);
		cout << "                                                                                                                   " << endl;
		cout << "                                                                                                                   " << endl;

	}
}

void Observer::CommandAnalyzer(int currentHumanFloor = 0, int targetHumanFloor = 0)
{
	int target = abs(this->floorsCount - currentHumanFloor);
	if (currentHumanFloor == 0 || targetHumanFloor == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			if (this->elevators[i]->move())
			{
				gotoxy((30 * i) + 3, this->elevators[i]->getCurrentFloor());
				cout << "Elevator reach his target" << endl;
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (!elevators[i]->isActive())
			{
				elevators[i]->ActiveState(1);
				elevators[i]->setTargetFloor(target, targetHumanFloor);
				break;
			}
		}
	}	
}

