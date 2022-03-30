#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include "Field.hpp"

using namespace std;

#define SYMBOL '@'

char* _cdecl strCopy(char* str)
{
#ifdef __cplusplus
	char* strcopy = new char[strlen(str) + 1];
#else
	char* strcopy = (char*)malloc((strlen(str) + 1) * sizeof(char));
#endif
	int i = 0;
	for (i = 0; i < strlen(str); i++)
	{
		strcopy[i] = str[i];
	}
	strcopy[i] = '\0';
	return strcopy;
}

char* _cdecl strGet()
{
#ifdef __cplusplus
	char* dinamic = new char[128];
#else
	char* dinamic = (char*)malloc(HARDCODED_STR_MEMALL * sizeof(char));
#endif
	fgets(dinamic, 128, stdin);
	if (dinamic[(strlen(dinamic) - 1)] == '\n')
		dinamic[(strlen(dinamic) - 1)] = '\0';
	char* str = strCopy(dinamic);

#ifdef __cplusplus
	delete[] dinamic;
#else
	free(dinamic);
#endif 
	return str;
}

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

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int x = SetConsoleScreenBufferSize(Handle, coord);
	int y = SetConsoleWindowInfo(Handle, TRUE, &Rect);
}

int main()
{
	int width = 211;
	int height = 50;

	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_MAXIMIZE);
	SetWindow(width, height);

	Field myField1;
	Field myField2;
	Builder myBuilder(height, width, FSTYLE_SQUARE);
	myBuilder.buildbyReference(&myField1);
	myBuilder.buildbyReference(&myField2);

	char** field1 = myField1.getCharField();
	char** field2 = myField2.getCharField();

	bool exit = false;

	while (!exit)
	{
		gotoxy(0, 0);
		for (int i = 0; i < 50; i++)
			cout << "                                                                                                                                                                                                                                                                                                  " << endl;
		gotoxy(0, 0);
		//system("cls");
		cout << "Choose mode:" << endl;
		cout << "0) Exit" << endl;
		cout << "1) Edit field by keyboard" << endl;
		cout << "2) Edit field by mouse (be carefull)" << endl;
		cout << "3) Start" << endl;
		char* str = strGet();
		if (str[0] == '0' && strlen(str) == 1)
		{
			delete[] str;
			return 0;
		}
		else if (str[0] == '1' && strlen(str) == 1)
		{
			system("cls");
			myField1.printField();
			gotoxy(0, 0);

			int x = 1;
			int y = 0;

			while (GetKeyState(VK_ESCAPE) >= 0)
			{
				char c = _getch();
				if ((c == 'A' || c == 'a') && x > 0)
				{
					x--;
					gotoxy(x, y);
				}
				else if ((c == 'D' || c == 'd') && x < width)
				{
					x++;
					gotoxy(x, y);
				}
				else if ((c == 'W' || c == 'w') && y > 0)
				{
					y--;
					gotoxy(x, y);
				}
				else if ((c == 'S' || c == 's') && y < height)
				{
					y++;
					gotoxy(x, y);
				}
				else if (c == VK_RETURN)
				{
					if (field1[y][x] != '#' && (y > 0) && (y < height) && (x > 0) && (x  < width))
					{
						if (field1[y][x] == ' ')
						{
							field1[y][x] = '@';
							cout << '@';
							gotoxy(x, y);
						}
						else if (field1[y][x] == '@')
						{
							field1[y][x] = ' ';
							cout << ' ';
							gotoxy(x, y);
						}
					}
				}
			}
			system("cls");
			delete[] str;
		}
		else if (str[0] == '2' && strlen(str) == 1)
		{
			system("cls");
			myField1.printField();
			//ShowConsoleCursor(FALSE);
			POINT pt = { 0,0 };

			while (GetKeyState(VK_ESCAPE) >= 0)
			{
				if (GetKeyState(VK_SPACE) == 1)
				{
					GetCursorPos(&pt);
					MapWindowPoints(GetDesktopWindow(), GetConsoleWindow(), &pt, 1);
					//cout << (pt.x / 7) - 2 << (pt.y / 16);
					gotoxy((pt.x / 7) - 3, (pt.y / 16));
					cout << SYMBOL;
					if (pt.x > 0 && pt.y > 0)
					{
						if (field1[(pt.y / 16)][(pt.x / 7) - 3] != '#' && ((pt.y / 16) > 0) && ((pt.y / 16) < height-1) && (((pt.x / 7) - 3) > 0) && (((pt.x / 7) - 3) < width-1))
							field1[(pt.y / 16)][(pt.x / 7) - 3] = SYMBOL;
						gotoxy(0, 0);
					}
				}
				else if (GetKeyState(VK_RETURN) == 1)
				{
					GetCursorPos(&pt);
					MapWindowPoints(GetDesktopWindow(), GetConsoleWindow(), &pt, 1);
					//cout << (pt.x / 7) - 2 << (pt.y / 16);
					gotoxy((pt.x / 7) - 3, (pt.y / 16));
					cout << ' ';

					if (pt.x > 0 && pt.y > 0)
					{
						if (field1[(pt.y / 16)][(pt.x / 7) - 3] != '#' && ((pt.y / 16) > 0) && ((pt.y / 16) < height-1) && (((pt.x / 7) - 3) > 0) && (((pt.x / 7) - 3) < width-1))
							field1[(pt.y / 16)][(pt.x / 7) - 3] = ' ';
						gotoxy(0, 0);
					}
				}
			}
			//ShowConsoleCursor(TRUE);
			delete[] str;
		}
		else if (str[0] == '3' && strlen(str) == 1)
		{
			delete[] str;

			console = GetConsoleWindow();
			ShowWindow(console, SW_MAXIMIZE);
			SetWindow(width, height);
			HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

			WCHAR* screen1 = new WCHAR[width * height + 1];
			WCHAR* screen2 = new WCHAR[width * height + 1];

			int pos = 0;

			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					screen1[pos] = field1[i][j];
					screen2[pos] = field2[i][j];
					pos++;
				}
			}
			screen1[width * height] = '\0';
			screen2[width * height] = '\0';

			SetConsoleActiveScreenBuffer(hConsole);
			DWORD dwBytesWritten = 0;

			int switcher = 0;

			while (GetKeyState(VK_ESCAPE) >= 0)
			{
				if (switcher % 2 == 0)
				{
					myField2.clearField();
					for (int i = 1; i < height - 1; i++)
					{
						for (int j = 1; j < width - 1; j++)
						{
							int counter = 0;

							// Верхний ряд
							if (field1[i - 1][j - 1] == SYMBOL)
								counter++;
							if (field1[i - 1][j] == SYMBOL)
								counter++;
							if (field1[i - 1][j + 1] == SYMBOL)
								counter++;

							// Средний ряд
							if (field1[i][j + 1] == SYMBOL)
								counter++;
							if (field1[i][j - 1] == SYMBOL)
								counter++;

							// Нижний ряд
							if (field1[i + 1][j - 1] == SYMBOL)
								counter++;
							if (field1[i + 1][j] == SYMBOL)
								counter++;
							if (field1[i + 1][j + 1] == SYMBOL)
								counter++;

							if (counter == 3 || (counter == 2 && field1[i][j] == SYMBOL))
							{
								field2[i][j] = SYMBOL;
							}
							else
							{
								field2[i][j] = ' ';
							}
						}
					}
					int pos = 0;
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							screen2[pos] = field2[i][j];
							pos++;
						}
					}
					screen2[width * height] = '\0';
					WriteConsoleOutputCharacter(hConsole, screen2, width * height, { 0, 0 }, &dwBytesWritten);
				}
				else
				{
					myField1.clearField();
					for (int i = 1; i < height - 1; i++)
					{
						for (int j = 1; j < width - 1; j++)
						{
							int counter = 0;
							if (field2[i - 1][j - 1] == SYMBOL)
								counter++;
							if (field2[i - 1][j] == SYMBOL)
								counter++;
							if (field2[i - 1][j + 1] == SYMBOL)
								counter++;

							// Средний ряд
							if (field2[i][j + 1] == SYMBOL)
								counter++;
							if (field2[i][j - 1] == SYMBOL)
								counter++;

							// Нижний ряд
							if (field2[i + 1][j - 1] == SYMBOL)
								counter++;
							if (field2[i + 1][j] == SYMBOL)
								counter++;
							if (field2[i + 1][j + 1] == SYMBOL)
								counter++;

							if (counter == 3 || (counter == 2 && field2[i][j] == SYMBOL))
							{
								field1[i][j] = SYMBOL;
							}
							else
							{
								field1[i][j] = ' ';
							}
						}
					}
					int pos = 0;
					for (int i = 0; i < height; i++)
					{
						for (int j = 0; j < width; j++)
						{
							screen1[pos] = field1[i][j];
							pos++;
						}
					}
					screen1[width * height] = '\0';
					WriteConsoleOutputCharacter(hConsole, screen1, width * height, { 0, 0 }, &dwBytesWritten);
				}
				switcher++;

				Sleep(100);
			}
			FlushConsoleInputBuffer(hConsole);
			//SetConsoleActiveScreenBuffer(NULL);
			hConsole = GetConsoleWindow();
			SetConsoleMode(hConsole, ENABLE_INSERT_MODE | ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
			//SetStdHandle(STD_OUTPUT_HANDLE, hConsole);
			delete[] screen1;
			delete[] screen2;
			myField1.clearField();
			myField2.clearField();
			//system("cls");
		}
	}

	return 0;
}
