#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "StudentsList.hpp"
#include "Header.hpp"

using namespace std;

List* mainList = 0;

int main()
{
	srand((unsigned int)time(0));
	char* str = new char[1];
	str[0] = '.';

	while (str[0] != '0')
	{
		delete[] str;
		cout << "\tMain menu:" << endl;
		cout << "0) Exit" << endl;
		cout << "1) Create List" << endl;
		cout << "2) Delete List" << endl;
		cout << "3) Open List" << endl;
		cout << "> " << ends;
		str = strGet();
		
		if (!strcmp(str, "cls"))
		{
			system("cls");
		}
		else if (str[0] == '1' && strlen(str) == 1)
		{
			if (!mainList)
			{
				mainList = new List();
				cout << "\nYour List was created.\n" << endl;
			}
			else
			{
				cout << "\nException: List was already created.\n" << endl;
			}
		}
		else if (str[0] == '2' && strlen(str) == 1)
		{
			if (mainList)
			{
				delete mainList;
				cout << "\nYour List was deleted.\n" << endl;
				mainList = 0;
			}
			else
			{
				cout << "\nException: List not created yet.\n" << endl;
			}
		}
		else if (str[0] == '3' && strlen(str) == 1)
		{
			if (mainList)
			{
				system("cls");
				ListAction();
			}
			else
			{
				cout << "\nException: List not created yet.\n" << endl;
			}
		}
		else if (strlen(str) > 1)
		{
			cout << "\nException: Wrong command.\n" << endl;
		}
		//delete[] str;
	}
	delete mainList;
	delete[] str;
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
	char* dinamic = (char*)malloc(128 * sizeof(char));
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

char* _cdecl strGetNumber()
{
	char* dinamic = 0;
	bool exitBool = false;
	while (!exitBool)
	{
		dinamic = strGet();
		bool error = false;
		if (dinamic[0] == '\0')
		{
			printf("\aException: Wrong input.\n");
		}
		int i = 0;
		for (int i = (dinamic[0] == '-' ? 1 : 0); i < strlen(dinamic); i++)
		{
			if (dinamic[i] < '0' || dinamic[i] > '9')
			{
				printf("\aException: Founded not only numbers.\n");
				error = true;
				break;
			}
		}
		if (!error)
		{
			exitBool = true;
			break;
		}
		delete[] dinamic;
	}
	return dinamic;
}

int _cdecl strContain(const char* strToFind, const char* baseStr)
{
	int strlenOfToFind = strlen(strToFind);
	int strlenOfBaseStr = strlen(baseStr);
	int count = 0;
	int flag = -1;
	for (int i = 0; i < strlenOfBaseStr; i++)
	{
		if (strToFind[0] == baseStr[i])
		{
			flag = i;
			int z = i;
			for (int j = 0; j < strlenOfToFind; j++, z++)
			{
				if (strToFind[j] == baseStr[z])
				{
					count++;
					if (count == strlenOfToFind)
					{
						return flag;
					}
				}
				else
				{
					flag = -1;
					count = 0;
					break;
				}
			}
		}
	}
	return flag;
}

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}