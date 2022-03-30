#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include "Elevator.hpp"
#include "Stuff.hpp"

using namespace std;

int main()
{
	ShowConsoleCursor(FALSE);
	Observer ElevatorManager;
	ElevatorManager.setElevators(15);
	ElevatorManager.printElevators();
	ElevatorManager.CommandListener();
	return 0;
}

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