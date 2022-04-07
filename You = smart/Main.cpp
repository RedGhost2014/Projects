#include <iostream>
#include <list>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <Windows.h>
#include "Declarator.h"

using namespace std;

int testCamera();
int Level1();
int Level2();
int Level3();
int Level4();

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

BOOL ShowConsoleCursor(BOOL bShow)
{
	CONSOLE_CURSOR_INFO cci;
	HANDLE hStdOut;
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE)
		return FALSE;
	if (!GetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	cci.bVisible = bShow;
	if (!SetConsoleCursorInfo(hStdOut, &cci))
		return FALSE;
	return TRUE;
}

void LoadLeveLSelector()
{
	Game* myGame = Singleton::getGame();
	//myGame->from = Singleton::getList()->back();
	myGame->addObject('C', 14, 70, true);
	myGame->addObject('h', 14, 71, true);
	myGame->addObject('o', 14, 72, true);
	myGame->addObject('o', 14, 73, true);
	myGame->addObject('s', 14, 74, true);
	myGame->addObject('e', 14, 75, true);
	myGame->addObject('L', 14, 77, true);
	myGame->addObject('v', 14, 78, true);
	myGame->addObject('L', 14, 79, true);
	myGame->addObject(':', 14, 80, true);

	myGame->addObject('1', 16, 73, true);
	myGame->level1 = Singleton::getList()->back();
	myGame->addObject('2', 18, 73, true);
	myGame->level2 = Singleton::getList()->back();
	myGame->addObject('3', 20, 73, true);
	myGame->level3 = Singleton::getList()->back();
	myGame->addObject('4', 16, 78, true);
	myGame->level4 = Singleton::getList()->back();
	//myGame->to = Singleton::getList()->back();
}


void LoadMainMenu()
{
	Game* myGame = Singleton::getGame();

	myGame->addHero('H', 17, 52, true);
	myGame->addObject('=', 17, 64, true);
	myGame->equalSign = Singleton::getList()->back();

	myGame->addObject('N', 17, 55, true);
	myGame->addObject('e', 17, 56, true);
	myGame->addObject('w', 17, 57, true);
	myGame->addObject('G', 17, 59, true);
	myGame->addObject('a', 17, 60, true);
	myGame->addObject('m', 17, 61, true);
	myGame->addObject('e', 17, 62, true);

	myGame->addObject('E', 19, 57, true);
	myGame->addObject('x', 19, 58, true);
	myGame->addObject('i', 19, 59, true);
	myGame->addObject('t', 19, 60, true);

	// Y Letter
	int YgapRow = 0;
	int YgapCoolumn = 0;
	char y = 'Y';
	myGame->addObject(y, 5 + YgapRow, 20 + YgapCoolumn, true);
	myGame->addObject(y, 6 + YgapRow, 21 + YgapCoolumn, true);
	myGame->addObject(y, 7 + YgapRow, 22 + YgapCoolumn, true);
	myGame->addObject(y, 8 + YgapRow, 23 + YgapCoolumn, true);

	myGame->addObject(y, 9 + YgapRow, 24 + YgapCoolumn, true);
	myGame->addObject(y, 10 + YgapRow, 24 + YgapCoolumn, true);
	myGame->addObject(y, 11 + YgapRow, 24 + YgapCoolumn, true);
	myGame->addObject(y, 12 + YgapRow, 24 + YgapCoolumn, true);

	myGame->addObject(y, 5 + YgapRow, 28 + YgapCoolumn, true);
	myGame->addObject(y, 6 + YgapRow, 27 + YgapCoolumn, true);
	myGame->addObject(y, 7 + YgapRow, 26 + YgapCoolumn, true);
	myGame->addObject(y, 8 + YgapRow, 25 + YgapCoolumn, true);


	// O Letter
	int OgapRow = 0;
	int OgapCoolumn = 1;
	char o = 'o';
	myGame->addObject(o, 5 + OgapRow, 32 + OgapCoolumn, true);
	myGame->addObject(o, 5 + OgapRow, 33 + OgapCoolumn, true);
	myGame->addObject(o, 5 + OgapRow, 34 + OgapCoolumn, true);
	myGame->addObject(o, 6 + OgapRow, 35 + OgapCoolumn, true);

	myGame->addObject(o, 7 + OgapRow, 36 + OgapCoolumn, true);
	myGame->addObject(o, 8 + OgapRow, 36 + OgapCoolumn, true);
	myGame->addObject(o, 9 + OgapRow, 36 + OgapCoolumn, true);
	myGame->addObject(o, 10 + OgapRow, 36 + OgapCoolumn, true);

	myGame->addObject(o, 11 + OgapRow, 35 + OgapCoolumn, true);
	myGame->addObject(o, 12 + OgapRow, 34 + OgapCoolumn, true);
	myGame->addObject(o, 12 + OgapRow, 33 + OgapCoolumn, true);
	myGame->addObject(o, 12 + OgapRow, 32 + OgapCoolumn, true);

	myGame->addObject(o, 11 + OgapRow, 31 + OgapCoolumn, true);
	myGame->addObject(o, 10 + OgapRow, 30 + OgapCoolumn, true);
	myGame->addObject(o, 9 + OgapRow, 30 + OgapCoolumn, true);
	myGame->addObject(o, 8 + OgapRow, 30 + OgapCoolumn, true);
	myGame->addObject(o, 7 + OgapRow, 30 + OgapCoolumn, true);
	myGame->addObject(o, 6 + OgapRow, 31 + OgapCoolumn, true);

	// U Letter
	int UgapRow = 0;
	int UgapCoolumn = 1;
	char u = 'u';
	myGame->addObject(u, 5 + UgapRow, 39 + UgapCoolumn, true);
	myGame->addObject(u, 6 + UgapRow, 39 + UgapCoolumn, true);
	myGame->addObject(u, 7 + UgapRow, 39 + UgapCoolumn, true);
	myGame->addObject(u, 8 + UgapRow, 39 + UgapCoolumn, true);
	myGame->addObject(u, 9 + UgapRow, 39 + UgapCoolumn, true);
	myGame->addObject(u, 10 + UgapRow, 39 + UgapCoolumn, true);
	myGame->addObject(u, 11 + UgapRow, 39 + UgapCoolumn, true);

	myGame->addObject(u, 12 + UgapRow, 40 + UgapCoolumn, true);
	myGame->addObject(u, 12 + UgapRow, 41 + UgapCoolumn, true);
	myGame->addObject(u, 12 + UgapRow, 42 + UgapCoolumn, true);
	myGame->addObject(u, 11 + UgapRow, 43 + UgapCoolumn, true);
	myGame->addObject(u, 10 + UgapRow, 44 + UgapCoolumn, true);

	myGame->addObject(u, 5 + UgapRow, 45 + UgapCoolumn, true);
	myGame->addObject(u, 6 + UgapRow, 45 + UgapCoolumn, true);
	myGame->addObject(u, 7 + UgapRow, 45 + UgapCoolumn, true);
	myGame->addObject(u, 8 + UgapRow, 45 + UgapCoolumn, true);
	myGame->addObject(u, 9 + UgapRow, 45 + UgapCoolumn, true);
	myGame->addObject(u, 10 + UgapRow, 45 + UgapCoolumn, true);
	myGame->addObject(u, 11 + UgapRow, 45 + UgapCoolumn, true);
	myGame->addObject(u, 12 + UgapRow, 45 + UgapCoolumn, true);

	// = Letter
	int EqualgapRow = 0;
	int EqualgapCoolumn = 1;
	char EqualSign = '=';
	myGame->addObject(EqualSign, 7 + EqualgapRow, 48 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 7 + EqualgapRow, 49 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 7 + EqualgapRow, 50 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 7 + EqualgapRow, 51 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 7 + EqualgapRow, 52 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 7 + EqualgapRow, 53 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 7 + EqualgapRow, 54 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 7 + EqualgapRow, 55 + EqualgapCoolumn, true);

	myGame->addObject(EqualSign, 10 + EqualgapRow, 48 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 10 + EqualgapRow, 49 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 10 + EqualgapRow, 50 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 10 + EqualgapRow, 51 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 10 + EqualgapRow, 52 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 10 + EqualgapRow, 53 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 10 + EqualgapRow, 54 + EqualgapCoolumn, true);
	myGame->addObject(EqualSign, 10 + EqualgapRow, 55 + EqualgapCoolumn, true);


	// S Letter
	int SgapRow = 0;
	int SgapCoolumn = 1;
	char s = 's';
	myGame->addObject(s, 6 + SgapRow, 58 + SgapCoolumn, true);
	myGame->addObject(s, 7 + SgapRow, 58 + SgapCoolumn, true);

	myGame->addObject(s, 5 + SgapRow, 59 + SgapCoolumn, true);
	myGame->addObject(s, 5 + SgapRow, 60 + SgapCoolumn, true);
	myGame->addObject(s, 5 + SgapRow, 61 + SgapCoolumn, true);
	myGame->addObject(s, 5 + SgapRow, 62 + SgapCoolumn, true);
	myGame->addObject(s, 5 + SgapRow, 63 + SgapCoolumn, true);
	myGame->addObject(s, 5 + SgapRow, 64 + SgapCoolumn, true);
	myGame->addObject(s, 6 + SgapRow, 65 + SgapCoolumn, true);

	myGame->addObject(s, 8 + SgapRow, 59 + SgapCoolumn, true);
	myGame->addObject(s, 8 + SgapRow, 60 + SgapCoolumn, true);
	myGame->addObject(s, 8 + SgapRow, 61 + SgapCoolumn, true);
	myGame->addObject(s, 9 + SgapRow, 62 + SgapCoolumn, true);
	myGame->addObject(s, 9 + SgapRow, 63 + SgapCoolumn, true);
	myGame->addObject(s, 9 + SgapRow, 64 + SgapCoolumn, true);

	myGame->addObject(s, 10 + SgapRow, 65 + SgapCoolumn, true);
	myGame->addObject(s, 11 + SgapRow, 65 + SgapCoolumn, true);
	myGame->addObject(s, 12 + SgapRow, 64 + SgapCoolumn, true);
	myGame->addObject(s, 12 + SgapRow, 63 + SgapCoolumn, true);
	myGame->addObject(s, 12 + SgapRow, 62 + SgapCoolumn, true);
	myGame->addObject(s, 12 + SgapRow, 61 + SgapCoolumn, true);
	myGame->addObject(s, 12 + SgapRow, 60 + SgapCoolumn, true);
	myGame->addObject(s, 12 + SgapRow, 59 + SgapCoolumn, true);
	myGame->addObject(s, 11 + SgapRow, 58 + SgapCoolumn, true);

	// M Letter
	int MgapRow = 0;
	int MgapCoolumn = 1;
	char m = 'm';
	myGame->addObject(m, 5 + MgapRow, 68 + MgapCoolumn, true);
	myGame->addObject(m, 6 + MgapRow, 68 + MgapCoolumn, true);
	myGame->addObject(m, 7 + MgapRow, 68 + MgapCoolumn, true);
	myGame->addObject(m, 8 + MgapRow, 68 + MgapCoolumn, true);
	myGame->addObject(m, 9 + MgapRow, 68 + MgapCoolumn, true);
	myGame->addObject(m, 10 + MgapRow, 68 + MgapCoolumn, true);
	myGame->addObject(m, 11 + MgapRow, 68 + MgapCoolumn, true);
	myGame->addObject(m, 12 + MgapRow, 68 + MgapCoolumn, true);

	myGame->addObject(m, 7 + MgapRow, 69 + MgapCoolumn, true);
	myGame->addObject(m, 6 + MgapRow, 70 + MgapCoolumn, true);
	myGame->addObject(m, 5 + MgapRow, 71 + MgapCoolumn, true);
	myGame->addObject(m, 6 + MgapRow, 72 + MgapCoolumn, true);
	myGame->addObject(m, 7 + MgapRow, 72 + MgapCoolumn, true);
	myGame->addObject(m, 8 + MgapRow, 72 + MgapCoolumn, true);
	myGame->addObject(m, 9 + MgapRow, 72 + MgapCoolumn, true);
	myGame->addObject(m, 10 + MgapRow, 72 + MgapCoolumn, true);
	myGame->addObject(m, 11 + MgapRow, 72 + MgapCoolumn, true);
	myGame->addObject(m, 12 + MgapRow, 72 + MgapCoolumn, true);

	myGame->addObject(m, 7 + MgapRow, 73 + MgapCoolumn, true);
	myGame->addObject(m, 6 + MgapRow, 74 + MgapCoolumn, true);
	myGame->addObject(m, 5 + MgapRow, 75 + MgapCoolumn, true);
	myGame->addObject(m, 6 + MgapRow, 76 + MgapCoolumn, true);

	myGame->addObject(m, 7 + MgapRow, 76 + MgapCoolumn, true);
	myGame->addObject(m, 8 + MgapRow, 76 + MgapCoolumn, true);
	myGame->addObject(m, 9 + MgapRow, 76 + MgapCoolumn, true);
	myGame->addObject(m, 10 + MgapRow, 76 + MgapCoolumn, true);
	myGame->addObject(m, 11 + MgapRow, 76 + MgapCoolumn, true);
	myGame->addObject(m, 12 + MgapRow, 76 + MgapCoolumn, true);

	// A Letter
	int AgapRow = 0;
	int AgapCoolumn = 1;
	char a = 'a';
	myGame->addObject(a, 7 + AgapRow, 79 + AgapCoolumn, true);
	myGame->addObject(a, 6 + AgapRow, 80 + AgapCoolumn, true);
	myGame->addObject(a, 5 + AgapRow, 81 + AgapCoolumn, true);
	myGame->addObject(a, 5 + AgapRow, 82 + AgapCoolumn, true);
	myGame->addObject(a, 5 + AgapRow, 83 + AgapCoolumn, true);
	myGame->addObject(a, 6 + AgapRow, 84 + AgapCoolumn, true);
	myGame->addObject(a, 7 + AgapRow, 85 + AgapCoolumn, true);
	myGame->addObject(a, 8 + AgapRow, 85 + AgapCoolumn, true);
	myGame->addObject(a, 9 + AgapRow, 85 + AgapCoolumn, true);
	myGame->addObject(a, 10 + AgapRow, 85 + AgapCoolumn, true);
	myGame->addObject(a, 11 + AgapRow, 85 + AgapCoolumn, true);
	myGame->addObject(a, 12 + AgapRow, 85 + AgapCoolumn, true);

	myGame->addObject(a, 11 + AgapRow, 84 + AgapCoolumn, true);
	myGame->addObject(a, 12 + AgapRow, 83 + AgapCoolumn, true);
	myGame->addObject(a, 12 + AgapRow, 82 + AgapCoolumn, true);
	myGame->addObject(a, 12 + AgapRow, 81 + AgapCoolumn, true);
	myGame->addObject(a, 12 + AgapRow, 80 + AgapCoolumn, true);
	myGame->addObject(a, 11 + AgapRow, 79 + AgapCoolumn, true);
	myGame->addObject(a, 10 + AgapRow, 79 + AgapCoolumn, true);
	myGame->addObject(a, 9 + AgapRow, 80 + AgapCoolumn, true);
	myGame->addObject(a, 9 + AgapRow, 81 + AgapCoolumn, true);
	myGame->addObject(a, 8 + AgapRow, 82 + AgapCoolumn, true);
	myGame->addObject(a, 8 + AgapRow, 83 + AgapCoolumn, true);
	myGame->addObject(a, 8 + AgapRow, 84 + AgapCoolumn, true);

	// R Letter
	int RgapRow = 0;
	int RgapCoolumn = 1;
	char r = 'r';
	myGame->addObject(r, 5 + RgapRow, 88 + RgapCoolumn, true);
	myGame->addObject(r, 6 + RgapRow, 88 + RgapCoolumn, true);
	myGame->addObject(r, 7 + RgapRow, 88 + RgapCoolumn, true);
	myGame->addObject(r, 8 + RgapRow, 88 + RgapCoolumn, true);
	myGame->addObject(r, 9 + RgapRow, 88 + RgapCoolumn, true);
	myGame->addObject(r, 10 + RgapRow, 88 + RgapCoolumn, true);
	myGame->addObject(r, 11 + RgapRow, 88 + RgapCoolumn, true);
	myGame->addObject(r, 12 + RgapRow, 88 + RgapCoolumn, true);

	myGame->addObject(r, 6 + RgapRow, 89 + RgapCoolumn, true);
	myGame->addObject(r, 5 + RgapRow, 90 + RgapCoolumn, true);
	myGame->addObject(r, 5 + RgapRow, 91 + RgapCoolumn, true);
	myGame->addObject(r, 5 + RgapRow, 92 + RgapCoolumn, true);
	myGame->addObject(r, 5 + RgapRow, 93 + RgapCoolumn, true);
	myGame->addObject(r, 6 + RgapRow, 94 + RgapCoolumn, true);

	// T Letter
	int TgapRow = 0;
	int TgapCoolumn = 1;
	char t = 't';
	myGame->addObject(t, 6 + TgapRow, 97 + TgapCoolumn, true);
	myGame->addObject(t, 6 + TgapRow, 98 + TgapCoolumn, true);
	myGame->addObject(t, 6 + TgapRow, 99 + TgapCoolumn, true);
	myGame->addObject(t, 6 + TgapRow, 100 + TgapCoolumn, true);
	myGame->addObject(t, 6 + TgapRow, 101 + TgapCoolumn, true);
	myGame->addObject(t, 6 + TgapRow, 102 + TgapCoolumn, true);

	myGame->addObject(t, 4 + TgapRow, 99 + TgapCoolumn, true);
	myGame->addObject(t, 5 + TgapRow, 99 + TgapCoolumn, true);
	myGame->addObject(t, 7 + TgapRow, 99 + TgapCoolumn, true);
	myGame->addObject(t, 8 + TgapRow, 99 + TgapCoolumn, true);
	myGame->addObject(t, 9 + TgapRow, 99 + TgapCoolumn, true);
	myGame->addObject(t, 10 + TgapRow, 99 + TgapCoolumn, true);
	myGame->addObject(t, 11 + TgapRow, 99 + TgapCoolumn, true);

	myGame->addObject(t, 12 + TgapRow, 100 + TgapCoolumn, true);
	myGame->addObject(t, 12 + TgapRow, 101 + TgapCoolumn, true);
	myGame->addObject(t, 12 + TgapRow, 102 + TgapCoolumn, true);
}

int main()
{
	system("cls");
	gotoxy(0, 0);
	srand(time(0));
	ShowConsoleCursor(FALSE);
	Singleton::createList();
	Singleton::createGame();

	Game* myGame = Singleton::getGame();
	myGame->setField(30, 120, false);
	LoadMainMenu();

	myGame->clearField(false);
	myGame->setObjectsOnField();
	system("cls");
	gotoxy(0, 0);
	myGame->printField();
	gotoxy(0, 0);
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		char* targetstr = myGame->thisField->getField()[(myGame->equalSign->coordinate.Y)];
		if (myGame->comparser.strContain((char*)"NewGame", targetstr) >= 0)
		{
			if (myGame->comparser.strContain((char*)"NewGame", targetstr) + strlen("NewGame") == myGame->equalSign->coordinate.X)
			{
				if (!myGame->LevelSelectorWasLoad)
				{
					myGame->LevelSelectorWasLoad = true;
					system("cls");
					LoadLeveLSelector();
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();
				}
				else if (myGame->equalSign->coordinate.X + 1 == myGame->level1->coordinate.X && myGame->equalSign->coordinate.Y == myGame->level1->coordinate.Y)
				{
					Level1();
					// Restore Main Menu
					system("cls");
					myGame->setField(30, 120, false);
					LoadMainMenu();
					myGame->LevelSelectorWasLoad = false;
					myGame->level1 = 0;
					myGame->level2 = 0;
					myGame->level3 = 0;
					myGame->level4 = 0;
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();
				}
				else if (myGame->equalSign->coordinate.X + 1 == myGame->level2->coordinate.X && myGame->equalSign->coordinate.Y == myGame->level2->coordinate.Y)
				{
					Level2();
					system("cls");
					myGame->setField(30, 120, false);
					LoadMainMenu();
					myGame->LevelSelectorWasLoad = false;
					myGame->level1 = 0;
					myGame->level2 = 0;
					myGame->level3 = 0;
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();
				}
				else if (myGame->equalSign->coordinate.X + 1 == myGame->level3->coordinate.X && myGame->equalSign->coordinate.Y == myGame->level3->coordinate.Y)
				{
					Level3();
					//testCamera();
					system("cls");
					myGame->setField(30, 120, false);
					LoadMainMenu();
					myGame->LevelSelectorWasLoad = false;
					myGame->level1 = 0;
					myGame->level2 = 0;
					myGame->level3 = 0;
					myGame->level4 = 0;
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();
				}
				else if (myGame->equalSign->coordinate.X + 1 == myGame->level4->coordinate.X && myGame->equalSign->coordinate.Y == myGame->level4->coordinate.Y)
				{
					Level4();
					//testCamera();
					system("cls");
					myGame->setField(30, 120, false);
					LoadMainMenu();
					myGame->LevelSelectorWasLoad = false;
					myGame->level1 = 0;
					myGame->level2 = 0;
					myGame->level3 = 0;
					myGame->level4 = 0;
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();
				}
			}
		}
		else if (myGame->comparser.strContain((char*)"Exit", targetstr) >= 0)
		{
			if (myGame->comparser.strContain((char*)"Exit", targetstr) + strlen("Exit") == myGame->equalSign->coordinate.X)
			{
				break;
			}
		}

		myGame->UserControl('w', 's', 'a', 'd');

		gotoxy(0, 0);
		myGame->clearField(false);
		myGame->setObjectsOnField();
		myGame->printField();
	}
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;
	Singleton::deleteGame();
	Singleton::destroyList();

	system("cls");
	return 0;
}

int Level1()
{
	Game* myGame = Singleton::getGame();

	// Clear Main Menu
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;

	myGame->setField(15, 30, false);
	myGame->addHero('H', 5, 5, true);
	myGame->addObject('=', 5, 8, true);
	myGame->equalSign = Singleton::getList()->back();
	myGame->addObject('+', 7, 7, true);
	myGame->addObject('7', 8, 8, true);
	myGame->addObject('5', 4, 12, true);

	int digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	gotoxy(40, 0);
	cout << "Level 1: A little bit of math..." << ends;
	gotoxy(40, 2);
	cout << "  Just try to get all digits" << ends;
	myGame->clearField(false);
	myGame->setObjectsOnField();
	myGame->printField(7, 40);
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		gotoxy(40, 7);
		myGame->clearField(false);
		myGame->setObjectsOnField();
		myGame->printField(7, 40);
		char* targetstr = myGame->thisField->getField()[(myGame->equalSign->coordinate.Y)];
		if (myGame->comparser.findOperation_Math(targetstr))
		{
			if (myGame->comparser.retrieveNumbers_Math(targetstr))
			{
				myGame->comparser.setAnswer();
				myGame->comparser.addResultObjects(myGame->equalSign, myGame->thisField->getColumns());
				myGame->clearField(false);
				myGame->setObjectsOnField();
				myGame->printField(7, 40);
			}
		}
		bool isWin = true;
		for (int i = 0; i < 10; i++)
		{
			if (myGame->isExistObject(digits[i] + '0'))
			{
				gotoxy(10, 10 + i);
				cout << digits[i] << " : Done" << endl;
			}
			else
			{
				isWin = false;
				gotoxy(10, 10 + i);
				cout << digits[i] << " : ... " << endl;
			}
		}
		if (isWin)
		{
			gotoxy(42, 27);
			cout << "Congratulations! You win!" << endl;
			Sleep(3000);
			break;
		}
		myGame->UserControl('w', 's', 'a', 'd');
	}
	// Clearing lvl 
	Singleton::clearList();
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;
	return 0;
}

int Level2()
{
	Game* myGame = Singleton::getGame();

	// Clear Main Menu
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;


	myGame->setField(15, 30, false);
	myGame->addHero('H', 5, 5, true);
	myGame->addObject('=', 5, 8, true);
	myGame->equalSign = Singleton::getList()->back();
	myGame->addObject('+', 7, 16, false);

	int digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	myGame->addObject('#', 6, 17, false);
	myGame->addObject('#', 6, 16, false);
	myGame->addObject('#', 6, 15, false);
	myGame->addObject('#', 7, 17, false);
	myGame->addObject('#', 8, 17, false);
	myGame->addObject('#', 8, 16, false);
	myGame->addObject('#', 8, 15, false);

	myGame->addObject('H', 10, 22, true);
	myGame->addObject('i', 11, 23, true);
	myGame->addObject('n', 10, 24, true);
	myGame->addObject('t', 11, 25, true);

	myGame->addObject('7', 9, 9, true);
	myGame->addObject('5', 4, 12, true);

	gotoxy(35, 0);
	cout << "Level 2: And another little bit of math..." << ends;
	//gotoxy(40, 2);
	//cout << "Looks like there is no s+oon..." << ends;
	//gotoxy(43, 3);
	//cout << "What you gonna do now?" << ends;

	myGame->clearField(false);
	myGame->setObjectsOnField();
	myGame->printField(7, 40);
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		gotoxy(40, 7);
		myGame->clearField(false);
		myGame->setObjectsOnField();
		myGame->printField(7, 40);
		char* targetstr = myGame->thisField->getField()[(myGame->equalSign->coordinate.Y)];
		if (myGame->comparser.findOperation_Math(targetstr))
		{
			if (myGame->comparser.retrieveNumbers_Math(targetstr))
			{
				myGame->comparser.setAnswer();
				myGame->comparser.addResultObjects(myGame->equalSign, myGame->thisField->getColumns());
				myGame->clearField(false);
				myGame->setObjectsOnField();
				myGame->printField(7, 40);
			}
		}

		int cHresult = myGame->changeHero(myGame->comparser.isHeroCanChange());
		if (cHresult > 0)
		{
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField(7, 40);

			// Animation drawing
			myGame->printEqualSignAnim(7, 40, false);
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField(7, 40);
		}
		else if (cHresult < 0)
		{
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField(7, 40);

			// Animation drawing
			myGame->printEqualSignAnim(7, 40, true);
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField(7, 40);
		}
		if (myGame->Hero == 0 || (myGame->Hero->IsMoveable() == false))
		{
			system("cls");
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField();
			gotoxy(5, 20);
			cout << "Game Over - You cant move now" << endl;
			Sleep(3000);
			break;
		}
		//if (myGame.)
		for (int i = 0; i < myGame->thisField->getRows(); i++)
		{
			if (myGame->comparser.strContain((char*)"Hint", myGame->thisField->getField()[i]) >= 0)
			{
				gotoxy(80, 18);
				cout << "Can you \"equal\" yourself to plus?" << endl;
				gotoxy(0, 0);
			}
			//else 
		}
		bool isWin = true;
		for (int i = 0; i < 10; i++)
		{
			if (myGame->isExistObject(digits[i] + '0'))
			{
				gotoxy(10, 10 + i);
				cout << digits[i] << " : Done" << endl;
			}
			else
			{
				isWin = false;
				gotoxy(10, 10 + i);
				cout << digits[i] << " : ... " << endl;
			}
		}
		if (isWin)
		{
			gotoxy(42, 27);
			cout << "Congratulations! You win!" << endl;
			Sleep(3000);
			break;
		}

		myGame->UserControl('w', 's', 'a', 'd');
		
	}
	// Clearing lvl 
	Singleton::clearList();
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;
	return 0;
}

int Level3()
{
	Game* myGame = Singleton::getGame();

	// Clear Main Menu
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;

	int digits[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int rowconstantgap = 5;

	myGame->setField(15, 30, true);
	myGame->addHero('H', 5, 5, true);
	myGame->addObject('=', 5, 8, true);
	myGame->equalSign = Singleton::getList()->back();
	myGame->addObject('H', 10, 22, true);
	myGame->addObject('i', 11, 23, true);
	myGame->addObject('n', 10, 24, true);
	myGame->addObject('t', 11, 25, true);
	myGame->addObject('1', 9, 13, true);
	myGame->addObject('0', 8, 15, true);

	gotoxy(42, 0);
	cout << "Level 3: Is it collapse?..." << ends;
	gotoxy(40, 2);
	cout << "Looks like there is no s+oon..." << ends;
	gotoxy(43, 3);
	cout << "What you gonna do now?" << ends;

	myGame->clearField(false);
	myGame->setObjectsOnField();
	myGame->printField(7, 40);

	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		gotoxy(40, 7);
		myGame->clearField(false);
		myGame->setObjectsOnField();
		myGame->printField(7, 40);
		char* targetstr = myGame->thisField->getField()[(myGame->equalSign->coordinate.Y)];

		if (myGame->comparser.retrieveNumbers_CS(targetstr))
		{
			myGame->comparser.setAnswer_CS();
			myGame->comparser.addResultObjects(myGame->equalSign, myGame->thisField->getColumns());
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField(7, 40);
		}

		bool isWin = true;
		for (int i = 0; i < 10; i++)
		{
			if (myGame->isExistObject(digits[i] + '0'))
			{
				gotoxy(10, 10 + i);
				cout << digits[i] << " : Done" << endl;
			}
			else
			{
				isWin = false;
				gotoxy(10, 10 + i);
				cout << digits[i] << " : ..." << endl;
			}
		}
		if (isWin)
		{
			gotoxy(40, 25);
			cout << "Congratulations! You win!" << endl;
			Sleep(3000);
			break;
		}

		for (int i = 0; i < myGame->thisField->getRows(); i++)
		{
			if (myGame->comparser.strContain((char*)"Hint", myGame->thisField->getField()[i]) >= 0)
			{
				gotoxy(80, 18);
				cout << "What about counting systems?" << endl;
				gotoxy(80, 19);
				cout << "Try to find a pattern" << endl;
				gotoxy(0, 0);
			}
			//else 
		}
		myGame->UserControl('w', 's', 'a', 'd');
	}


	//myGame->addObject('+', 7, 16, false);

	// Clearing lvl 
	Singleton::clearList();
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;
	return 0;
}

int Level4()
{
	Game* myGame = Singleton::getGame();

	// Clear Main Menu
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;

	const int addrows = 7;
	const int addcolumns = 40;

	myGame->setField(30, 120, false);

	const char* levelname = "Level 4: Board Clearing";
	const char* leveldescription = "Just take out all trash please, i forgot";

	for (int i = 0; i < strlen(levelname); i++)
	{
		if (levelname[i] != ' ')
			myGame->addObject(levelname[i], 1, 43 + i, true);
	}
	for (int i = 0; i < strlen(leveldescription); i++)
	{
		if (leveldescription[i] != ' ')
			myGame->addObject(leveldescription[i], 3, 37 + i, true);
	}

	for (int i = 0; i <= 30; i++)
	{
		myGame->addObject('#', 7, 40 + i, false);
		myGame->addObject('#', 7 + 15, 40 + i, false);
	}

	myGame->addHero('H', 8 + addrows, 5 + addcolumns, true);
	myGame->addObject('=', 8 + addrows, 8 + addcolumns, true);
	myGame->equalSign = Singleton::getList()->back();

	for (int i = 1; i < 15; i++)
	{
		myGame->addObject('#', 7 + i, 40, false);
		myGame->addObject('#', 7 + i, 40 + 30, false);
	}

	myGame->addObject('d', 11 + addrows, 9 + addcolumns, true);
	myGame->addObject('e', 11 + addrows, 11 + addcolumns, true);
	myGame->addObject('l', 11 + addrows, 13 + addcolumns, true);

	myGame->clearField(true);
	myGame->setObjectsOnField();
	myGame->printField(0, 0);
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		gotoxy(0, 0);
		myGame->clearField(true);
		myGame->setObjectsOnField();
		myGame->printField(0, 0);
		char* targetstr = myGame->thisField->getField()[(myGame->equalSign->coordinate.Y)];

		if (myGame->comparser.strContain((char*)"del", targetstr) >= 0)
		{
			int ptr = myGame->comparser.strContain((char*)"del", targetstr);
			if (ptr - 1 == myGame->equalSign->coordinate.X)
			{
				Object* tmp = myGame->getObject(myGame->equalSign->coordinate.Y, myGame->equalSign->coordinate.X - 1);
				if (tmp)
				{
					if (tmp->getCharPortrait() == '#')
					{
						myGame->destroyEveryObject('#');
					}
					else myGame->destroyObject(tmp->coordinate.Y, tmp->coordinate.X);
					/*system("cls");
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();
					Sleep(300);*/
					//system("cls");
					gotoxy(0, 0);
					myGame->clearField(true);
					myGame->setObjectsOnField();
					myGame->printField();

					if (Singleton::getList()->size() == 4)
					{
						gotoxy(15, 40);
						cout << "Congratulations! You win!" << endl;
						Sleep(3000);
						break;
					}
					if (tmp == myGame->Hero)
					{
						/*system("cls");
						myGame->clearField(false);
						myGame->setObjectsOnField();
						myGame->printField();*/
						gotoxy(25, 40);
						cout << "Game Over - You have been deleted" << endl;
						Sleep(3000);
						break;
					}
				}
			}
		}
		myGame->UserControl('w', 's', 'a', 'd');
	}


	// Clearing lvl 
	Singleton::clearList();
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;
	return 0;
}

int testCamera()
{
	/*Singleton::createList();
	Singleton::createGame();*/
	Game* myGame = Singleton::getGame();

	// Clear Main Menu
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;

	// Loading lvl
	myGame->setField(15, 30, false);
	myGame->addHero('H', 5, 5, true);
	myGame->addObject('=', 5, 8, true);
	myGame->equalSign = Singleton::getList()->back();

	myGame->addObject('+', 5, 7, true);
	myGame->addObject('-', 6, 7, true);
	myGame->addObject('/', 4, 7, true);
	myGame->addObject('*', 3, 7, true);
	myGame->addObject('1', 8, 8, true);
	myGame->addObject('3', 6, 8, true);
	myGame->addObject('7', 6, 9, true);
	myGame->addObject('9', 6, 10, true);
	myGame->addObject('#', 7, 11, false);

	myGame->addObject('d', 10, 11, true);
	myGame->addObject('e', 10, 12, true);
	myGame->addObject('l', 10, 13, true);

	myGame->clearField(false);
	myGame->setObjectsOnField();
	myGame->printField();
	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		//system("cls");
		gotoxy(0, 0);
		myGame->clearField(false);
		myGame->setObjectsOnField();
		myGame->printField();
		char* targetstr = myGame->thisField->getField()[(myGame->equalSign->coordinate.Y)];
		if (myGame->comparser.findOperation_Math(targetstr))
		{
			if (myGame->comparser.retrieveNumbers_Math(targetstr))
			{
				myGame->comparser.setAnswer();
				myGame->comparser.addResultObjects(myGame->equalSign, myGame->thisField->getColumns());
				system("cls");
				myGame->clearField(false);
				myGame->setObjectsOnField();
				myGame->printField();
			}
		}
		if (myGame->comparser.strContain((char*)"del", targetstr) >= 0)
		{
			int ptr = myGame->comparser.strContain((char*)"del", targetstr);
			if (ptr - 1 == myGame->equalSign->coordinate.X)
			{
				Object* tmp = myGame->getObject(myGame->equalSign->coordinate.Y, myGame->equalSign->coordinate.X - 1);
				if (tmp)
				{
					myGame->destroyObject(tmp->coordinate.Y, tmp->coordinate.X);
					/*system("cls");
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();
					Sleep(300);*/
					system("cls");
					myGame->clearField(false);
					myGame->setObjectsOnField();
					myGame->printField();

					if (tmp == myGame->Hero)
					{
						/*system("cls");
						myGame->clearField(false);
						myGame->setObjectsOnField();
						myGame->printField();*/
						gotoxy(5, 20);
						cout << "Game Over - You have been deleted" << endl;
						Sleep(3000);
						break;
					}
				}
			}
		}
		int cHresult = myGame->changeHero(myGame->comparser.isHeroCanChange());
		if (cHresult > 0)
		{
			system("cls");
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField();

			// Animation drawing
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << '/';
			gotoxy(myGame->equalSign->coordinate.X + 1, myGame->equalSign->coordinate.Y - 1);
			cout << '\\';
			Sleep(300);
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << "   ";
			gotoxy(myGame->equalSign->coordinate.X, myGame->equalSign->coordinate.Y - 1);
			cout << '-';
			Sleep(300);
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << "   ";
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << '/';
			gotoxy(myGame->equalSign->coordinate.X + 1, myGame->equalSign->coordinate.Y - 1);
			cout << '\\';
			Sleep(300);
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << "   ";
		}
		else if (cHresult < 0)
		{
			system("cls");
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField();

			// Animation drawing
			gotoxy(myGame->equalSign->coordinate.X, myGame->equalSign->coordinate.Y - 1);
			cout << "<-";
			Sleep(300);
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << "   ";
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << "<-";
			Sleep(300);
			gotoxy(myGame->equalSign->coordinate.X - 1, myGame->equalSign->coordinate.Y - 1);
			cout << "   ";
		}
		if (myGame->Hero == 0 || (myGame->Hero->IsMoveable() == false))
		{
			system("cls");
			myGame->clearField(false);
			myGame->setObjectsOnField();
			myGame->printField();
			gotoxy(5, 20);
			cout << "Game Over - You are Wall now" << endl;
			Sleep(3000);
			break;
		}
		myGame->UserControl('w', 's', 'a', 'd');
		//system("cls");
		gotoxy(0, 0);
		myGame->clearField(false);
		myGame->setObjectsOnField();
		myGame->printField();
	}
	// Clearing lvl 
	Singleton::clearList();
	system("cls");
	myGame->deleteField();
	Singleton::clearList();
	myGame->Hero = 0;

	return 0;
}