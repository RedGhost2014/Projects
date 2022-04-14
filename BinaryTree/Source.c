#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define _CONSOLEGRAPHIC_
#ifdef _CONSOLEGRAPHIC_

#include <Windows.h>
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

int _cdecl printf_slow(const char* str, int sleep, ...)
{
	if (sleep < 0)
		return 1;
	va_list argptr;
	va_start(argptr, sleep);
	int tmpInt;
	char* tmpStr;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '%' && str[i + 1] == 'd')
		{
			tmpInt = va_arg(argptr, int);
			char* tmpIntItoa = (char*)malloc(128 * sizeof(char));
			_itoa_s(tmpInt, tmpIntItoa, 128, 10);
			for (int j = 0; j < strlen(tmpIntItoa); j++)
			{
				printf("%c", tmpIntItoa[j]);
				if (!_kbhit())
				{
					Sleep(sleep);
				}
			}
			free(tmpIntItoa);
			i++;
			continue;
		}
		if (str[i] == '%' && str[i + 1] == 's')
		{
			tmpStr = va_arg(argptr, char*);
			for (int j = 0; j < strlen(tmpStr); j++)
			{
				printf("%c", tmpStr[j]);
				if (!_kbhit())
				{
					Sleep(sleep);
				}
			}
			i++;
			continue;
		}
		if (!_kbhit())
		{
			printf("%c", str[i]);
			Sleep(sleep);
		}
		else 
		{
			printf("%c", str[i]);
		}
	}
	va_end(argptr);
	return 0;
}

#endif // _CONSOLEGRAPHIC_


// Визуализация направления
#define FROM_LEFT_TO_RIGHT
#ifndef FROM_LEFT_TO_RIGHT

#define FROM_RIGHT_TO_LEFT

#endif 

// Визуализация порядка (взаимоисключающие флажки)
//#define NOWPRINT
//#define MIDDLEPRINT
#define AFTERPRINT

typedef struct Node
{
	struct Node* left;
	struct Node* right;
	void* value;
} Node;

typedef struct Tree
{
	Node* root;
} Tree;

int numbertoprint = 0;
COORD placetoprint = { 0, 0 };

Tree* createTree(char* string)
{
	Tree* newTree = (Tree*)malloc(sizeof(Tree));
	newTree->root = (Node*)malloc(sizeof(Node));

	char* str = (char*)malloc((strlen(string) + 1) * sizeof(char));
	str[strlen(string)] = '\0';
	for (size_t i = 0; i < strlen(string); i++)
	{
		str[i] = string[i];
	}
	newTree->root->value = (char*)str;
	newTree->root->left = NULL;
	newTree->root->right = NULL;
	return newTree;
}

void DeleteTree(Node* thisnode)
{
	if (thisnode->left != NULL)
	{
		DeleteTree(thisnode->left);
	}
	if (thisnode->right != NULL)
	{
		DeleteTree(thisnode->right);
	}
	if (thisnode->value != NULL)
	{
		char* str = (char*)thisnode->value;
		free(str);
		thisnode->value = NULL;
	}
	if (thisnode != NULL)
	{
		free(thisnode);
		thisnode = NULL;
	}
}

int addElement(Tree* thistree, char* newelement)
{
	Node* newnode = thistree->root;
	Node* previous = thistree->root;

	bool wasleft = false;
	bool wasright = false;

	while (newnode != NULL)
	{
		if ((strlen(newelement) > strlen((char*)newnode->value)))
		{
			newnode = newnode->right;
			wasleft = false;
			wasright = true;
			if (newnode == NULL)
			{
				break;
			}
			previous = previous->right;
		}
		else if ((strlen(newelement) < strlen((char*)newnode->value)))
		{
			newnode = newnode->left;
			wasleft = true;
			wasright = false;
			if (newnode == NULL)
			{
				break;
			}
			previous = previous->left;
		}
		else if (_stricmp(newelement, (char*)newnode->value) > 0)
		{
			newnode = newnode->right;
			wasleft = false;
			wasright = true;
			if (newnode == NULL)
			{
				break;
			}
			previous = previous->right;
		}
		else if (_stricmp(newelement, (char*)newnode->value) < 0)
		{
			newnode = newnode->left;
			wasleft = true;
			wasright = false;
			if (newnode == NULL)
			{
				break;
			}
			previous = previous->left;
		}
		else return 1;
	}

	newnode = (Node*)malloc(sizeof(Node));
	newnode->left = NULL;
	newnode->right = NULL;

	char* thisstr = (char*)newelement;

	char* str = (char*)malloc((strlen(thisstr) + 1) * sizeof(char));
	str[strlen(thisstr)] = '\0';
	for (size_t i = 0; i < strlen(thisstr); i++)
	{
		str[i] = thisstr[i];
	}
	newnode->value = (char*)str;
	if (wasleft)
		previous->left = newnode;
	else if (wasright)
		previous->right = newnode;
	return 0;
}

#ifdef FROM_LEFT_TO_RIGHT

void printTree(Node* thisnode)
{
#ifdef NOWPRINT

	gotoxy(placetoprint.X - 3, placetoprint.Y);
	printf_slow("%d) %s", 1, numbertoprint, (char*)thisnode->value);
	Sleep(500);
	numbertoprint++;

#endif // NOWPRINT
	if (thisnode->left != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y++;
			placetoprint.X--;
			placetoprint.X--;
			placetoprint.X--;
			gotoxy(placetoprint.X, placetoprint.Y);
			printf(".");
			Sleep(1);
		}
		printTree(thisnode->left);
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y--;
			placetoprint.X++;
			placetoprint.X++;
			placetoprint.X++;
			gotoxy(placetoprint.X, placetoprint.Y);
			Sleep(1);
		}
		Sleep(500);
	}

#ifdef MIDDLEPRINT

	gotoxy(placetoprint.X /*- (strlen((char*)thisnode->value) / 2)*/ - 3, placetoprint.Y);
	printf_slow("%d) %s", 1, numbertoprint, (char*)thisnode->value);
	Sleep(500);
	numbertoprint++;

#endif // MIDDLEPRINT

	if (thisnode->right != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y++;
			placetoprint.X++;
			placetoprint.X++;
			placetoprint.X++;
			gotoxy(placetoprint.X, placetoprint.Y);
			printf(".");
			Sleep(1);
		}
		printTree(thisnode->right);
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y--;
			placetoprint.X--;
			placetoprint.X--;
			placetoprint.X--;
			gotoxy(placetoprint.X, placetoprint.Y);
			Sleep(1);
		}
		Sleep(500);
	}
#ifdef AFTERPRINT

	gotoxy(placetoprint.X /*- (strlen((char*)thisnode->value) / 2)*/ - 3, placetoprint.Y);
	printf_slow("%d) %s", 1, numbertoprint, (char*)thisnode->value);
	Sleep(500);
	numbertoprint++;

#endif // AFTERPRINT
}

#endif // FROM_LEFT_TO_RIGHT

#ifdef FROM_RIGHT_TO_LEFT

void printTree(Node* thisnode)
{
#ifdef NOWPRINT

	gotoxy(placetoprint.X - 3, placetoprint.Y);
	printf_slow("%d) %s", 1, numbertoprint, (char*)thisnode->value);
	Sleep(500);
	numbertoprint++;

#endif // NOWPRINT
	
	if (thisnode->right != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y++;
			placetoprint.X++;
			placetoprint.X++;
			placetoprint.X++;
			gotoxy(placetoprint.X, placetoprint.Y);
			printf(".");
			Sleep(1);
		}
		printTree(thisnode->right);
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y--;
			placetoprint.X--;
			placetoprint.X--;
			placetoprint.X--;
			gotoxy(placetoprint.X, placetoprint.Y);
			Sleep(1);
		}
		Sleep(500);
	}

#ifdef MIDDLEPRINT

	gotoxy(placetoprint.X /*- (strlen((char*)thisnode->value) / 2)*/ - 3, placetoprint.Y);
	printf_slow("%d) %s", 1, numbertoprint, (char*)thisnode->value);
	Sleep(500);
	numbertoprint++;

#endif // AFTERPRINT

	if (thisnode->left != NULL)
	{
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y++;
			placetoprint.X--;
			placetoprint.X--;
			placetoprint.X--;
			gotoxy(placetoprint.X, placetoprint.Y);
			printf(".");
			Sleep(1);
		}
		printTree(thisnode->left);
		for (int i = 0; i < 4; i++)
		{
			placetoprint.Y--;
			placetoprint.X++;
			placetoprint.X++;
			placetoprint.X++;
			gotoxy(placetoprint.X, placetoprint.Y);
			Sleep(1);
		}
		Sleep(500);
	}
#ifdef AFTERPRINT

	gotoxy(placetoprint.X /*- (strlen((char*)thisnode->value) / 2)*/ - 3, placetoprint.Y);
	printf_slow("%d) %s", 1, numbertoprint, (char*)thisnode->value);
	Sleep(500);
	numbertoprint++;

#endif // AFTERPRINT
}

#endif // FROM_LEFT_TO_RIGHT

int main()
{
	HANDLE hconsole = GetConsoleWindow();
	ShowWindow(hconsole, SW_MAXIMIZE);
	system("pause");
	system("cls");
	Tree* myTree = createTree("string");
	
	addElement(myTree, "hello");
	addElement(myTree, "alarm");
	addElement(myTree, "privet");
	addElement(myTree, "privet");
	addElement(myTree, "privet");
	addElement(myTree, "privet");
	addElement(myTree, "hamlet");
	addElement(myTree, "hbrush");
	addElement(myTree, "whisky");
	addElement(myTree, "AD");
	addElement(myTree, "a");
	addElement(myTree, "A");
	addElement(myTree, "Da");
	addElement(myTree, "looooooong string");
	addElement(myTree, "little string");
	addElement(myTree, "another loooooooooong string");
	addElement(myTree, "a string a bit less");
	addElement(myTree, "ooooooooooooooooooooooooooooooooooooooooooooo");

	placetoprint.X = (240/ 3) - (strlen((char*)myTree->root->value) / 2);
	placetoprint.Y = 2;
	gotoxy(placetoprint.X, placetoprint.Y);
	printTree(myTree->root);
	numbertoprint = 0;
	gotoxy(0, 30);
	system("pause");
	DeleteTree(myTree->root);
	free(myTree);
	return 0;
}