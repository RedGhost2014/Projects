#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <Windows.h>
#include "StudentsList.h"
#include <conio.h>

using namespace std;

char* _cdecl strCopy(char* str);
char* _cdecl strGet();
int _cdecl strContain(const char* strToFind, const char* baseStr);
char* _cdecl strGetNumber();
void gotoxy(int x, int y);

void ListAction();
void AddStudentsAction();
void DeleteAction();
void ClearAction();
void PrintAction();

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

void ListAction()
{
	char* str = new char[1];
	str[0] = '.';
	while (str[0] != '0')
	{
		delete[] str;
		cout << "\tList action:" << endl;
		cout << "0) Exit" << endl;
		cout << "1) Add student" << endl;
		cout << "2) Clear student" << endl;
		cout << "3) Delete student" << endl;
		cout << "4) Print List" << endl;
		cout << "5) Destroy gaps in List" << endl;
		cout << "> " << ends;
		str = strGet();

		if (!strcmp(str, "cls"))
		{
			system("cls");
		}
		else if (strlen(str) > 1)
		{
			cout << "\nException: Wrong command.\n" << endl;
		}
		else if (str[0] == '1' && strlen(str) == 1)
		{
			system("cls");
			AddStudentsAction();
		}
		else if (str[0] == '2' && strlen(str) == 1)
		{
			ClearAction();
		}
		else if (str[0] == '3' && strlen(str) == 1)
		{
			DeleteAction();
		}
		else if (str[0] == '4' && strlen(str) == 1)
		{
			PrintAction();
		}
		else if (str[0] == '5' && strlen(str) == 1)
		{
			mainList->GarbageCollector();
		}
	}
	delete[] str;
	system("cls");
}

void PrintAction()
{
	char* str = new char[1];
	str[0] = '.';
	while (str[0] != '0')
	{
		delete[] str;
		cout << "\tPrint action:" << endl;
		cout << "0) Exit" << endl;
		cout << "1) Print all List of students" << endl;
		cout << "2) Print all succesful students" << endl;
		cout << "3) Print students from same group" << endl;
		cout << "4) Find students by surname" << endl;
		cout << "> " << ends;
		str = strGet();

		if (!strcmp(str, "cls"))
		{
			system("cls");
		}
		else if (strlen(str) > 1)
		{
			cout << "\nException: Wrong command.\n" << endl;
		}
		else if (str[0] == '1' && strlen(str) == 1)
		{
			cout << "\nYour List:" << endl;
			mainList->printList();
		}
		else if (str[0] == '2' && strlen(str) == 1)
		{
			cout << "Enter the grade to filter up:" << endl;
			char* number = strGetNumber();
			int n = atoi(number);
			cout << "\nYour List:" << endl;
			mainList->printList((float)n);
		}
		else if (str[0] == '3' && strlen(str) == 1)
		{
			cout << "Enter the group:" << endl;
			char* group = strGet();
			cout << "\nYour List:" << endl;
			mainList->printList(group);
		}
		else if (str[0] == '4' && strlen(str) == 1)
		{
			system("cls");
			cout << "Enter the surname:" << endl;
			const int size = 20;
			char surname[size] = { 0 };

			int pos = 0;
			int x;
			while (1)
			{
				x = _getch();
				gotoxy(0, 2);
				for (int i = 0; i < 30; i++)
				{
					cout << "                                                                                              " << endl;
				}
				gotoxy(pos, 1);
				if (x == VK_BACK)
				{
					if (pos > 0)
					{
						_putch('\b');
						_putch(' ');
						_putch('\b');
						pos--;
						surname[pos] = '\0';
					}
				}
				else if (x == VK_ESCAPE)
				{
					////keybd_event(VK_RETURN, NULL, NULL, NULL);
					////password[pos] = '\0';
					//cout << endl;
					//cout << surname << "\n\n\n" << endl;
					system("cls");
					break;
				}
				else if ((pos < 19) && x != VK_LEFT && x != VK_RIGHT && x != VK_UP && x != VK_DOWN)
				{
					cout << (char)x;
					surname[pos] = (char)x;
					surname[pos + 1] = '\0';
					pos++;
					cout << endl;
					mainList->printDynamicList(surname);
					gotoxy(pos, 1);
				}
			}

		}
	}
	delete[] str;
	system("cls");
}

void DeleteAction()
{
	char* str = new char[1];
	str[0] = '.';
	while (str[0] != '0')
	{
		delete[] str;
		cout << "\tDeleting Menu:" << endl;
		cout << "0) Exit" << endl;
		cout << "1) Delete student by group & surname" << endl;
		cout << "2) Delete student by sequential number in the list" << endl;
		cout << "3) Delete the most underachieving students" << endl;
		cout << "> " << ends;
		str = strGet();

		if (!strcmp(str, "cls"))
		{
			system("cls");
		}
		else if (strlen(str) > 1)
		{
			cout << "\nException: Wrong command.\n" << endl;
		}
		else if (str[0] == '1' && strlen(str) == 1)
		{
			cout << "Enter group: " << endl;
			char* group = strGet();
			cout << "Enter surname: " << endl;
			char* surname = strGet();

			mainList->deleteStudent(surname, group);

			delete[] surname;
			delete[] group;
		}
		else if (str[0] == '2' && strlen(str) == 1)
		{
			cout << "Enter number: " << endl;
			char* number = strGetNumber();
			int n = atoi(number);

			try
			{
				mainList->deleteStudent(n);
			}
			catch (const MsgException& e)
			{
				cout << e.what() << endl;
			}

			delete[] number;
		}
		else if (str[0] == '3' && strlen(str) == 1)
		{
			cout << "Enter the grade, note that all students with an average performance below it will be deleted: " << endl;
			char* grade = strGetNumber();
			int n = atoi(grade);
			mainList->deleteStudent((float)n);

			delete[] grade;
		}
	}
	delete[] str;
	system("cls");
}

void ClearAction()
{
	char* str = new char[1];
	str[0] = '.';
	while (str[0] != '0')
	{
		delete[] str;
		cout << "\tClearing Menu:" << endl;
		cout << "0) Exit" << endl;
		cout << "1) Clear student by group & surname" << endl;
		cout << "2) Clear student by sequential number in the list" << endl;
		cout << "3) Clear the most underachieving students" << endl;
		cout << "> " << ends;
		str = strGet();

		if (!strcmp(str, "cls"))
		{
			system("cls");
		}
		else if (strlen(str) > 1)
		{
			cout << "\nException: Wrong command.\n" << endl;
		}
		else if (str[0] == '1' && strlen(str) == 1)
		{
			cout << "Enter group: " << endl;
			char* group = strGet();
			cout << "Enter surname: " << endl;
			char* surname = strGet();

			mainList->clearStudent(surname, group);

			delete[] surname;
			delete[] group;
		}
		else if (str[0] == '2' && strlen(str) == 1)
		{
			cout << "Enter number: " << endl;
			char* number = strGetNumber();
			int n = atoi(number);

			try
			{
				mainList->clearStudent(n);
			}
			catch (const MsgException& e)
			{
				cout << e.what() << endl;
			}

			delete[] number;
		}
		else if (str[0] == '3' && strlen(str) == 1)
		{
			cout << "Enter the grade, note that all students with an average performance below it will be cleared: " << endl;
			char* grade = strGetNumber();
			int n = atoi(grade);
			mainList->clearStudent((float)n);

			delete[] grade;
		}
	}
	delete[] str;
	system("cls");
}

void AddStudentsAction()
{
	static const char* boynames[] = { "Ivan" , "Denis", "Danil", "Dmitriy", "Albert", "Maxim", "Alexander", "Nikolay", "Konstantin", "Andrey", "Roman", "Vitaly", "Alexey" };
	static const char* boysurnames[] = { "Fedrushkov", "Vasiliyev", "Alimov", "Yamatin", "Korablev", "Andenkov", "Yakaev", "Trigubskiy", "Komarov", "Ivanov", "Petrov", "Sidorov", "Niskovskiy" };

	static const char* girlnames[] = { "Dana" , "Anastasiya", "Alexandra", "Ekaterina", "Darya", "Alina", "Anna", "Sofia", "Elisaveta", "Stanislava", "Maria", "Vasilisa", "Evgeniya" };
	static const char* girlsurnames[] = { "Fedrushkova", "Vasiliyeva", "Alimova", "Yamatina", "Korableva", "Andenkova", "Yakaeva", "Trigubskikh", "Komarova", "Ivanova", "Zonova", "Niskovskikh" , "Sokolova" };

	static const char* groupmass[] = { "MK101", "MK102", "MN101", "MN102", "MP101", "MP102" , "MP103", "MT101", "MT102"};

	char* str = new char[1];
	str[0] = '.';
	while (str[0] != '0')
	{
		delete[] str;
		cout << "\tAdding student:" << endl;
		cout << "0) Exit" << endl;
		cout << "1) Add student" << endl;
		cout << "2) Add random student" << endl;
		cout << "> " << ends;
		str = strGet();

		if (!strcmp(str, "cls"))
		{
			system("cls");
		}
		else if (strlen(str) > 1)
		{
			cout << "\nException: Wrong command.\n" << endl;
		}
		else if (str[0] == '1' && strlen(str) == 1)
		{
			cout << "Enter name: " << ends;;
			char* name = strGet();
			cout << "Enter surname: " << ends;;
			char* surname = strGet();
			cout << "Enter group: " << ends;;
			char* group = strGet();
			cout << "Enter age: " << ends;;
			char* tmp = strGetNumber();
			short age = atoi(tmp);
			delete[] tmp;
			short marks[4];
			cout << "Enter marks in order: IT, MatAn, Geometry, Algebra." << endl;

			for (short i = 0; i < 4; i++)
			{
				cout << i + 1 << ") " << ends;
				char* tmp = strGetNumber();
				marks[i] = atoi(tmp);
				delete[] tmp;
			}

			cout << "Enter phone number: " << ends;;
			char* phonenumber = strGetNumber();

			mainList->addStudent(name, surname, group, phonenumber, age, marks);
		}
		else if (str[0] == '2' && strlen(str) == 1)
		{
			char* name = 0;
			char* surname = 0;
			if (rand() % 2 == 0)
			{
				name = strCopy((char*)boynames[rand() % 13]);
				surname = strCopy((char*)boysurnames[rand() % 13]);
			}
			else
			{
				name = strCopy((char*)girlnames[rand() % 13]);
				surname = strCopy((char*)girlsurnames[rand() % 13]);
			}
			
			char* group = strCopy((char*)groupmass[rand() % 9]);

			char* phonenumber = new char[10 + 1];
			int i = 0;
			for (i = 0; i < 10; i++)
			{
				phonenumber[i] = rand() % 10 + '0';
			}
			phonenumber[i] = '\0';
			short age = (rand() % 3) + 18;
			short marks[4];
			for (i = 0; i < 4; i++)
			{
				marks[i] = (rand() % 4) + 2;
			}

			mainList->addStudent(name, surname, group, phonenumber, age, marks);

			cout << "Added student:" << endl;
			cout << surname << " " << name << ", " << age << endl;
			cout << "Group:\t" << group << endl;
			cout << "Phonenumber:\t" << phonenumber << endl;
			cout << endl;
		}
	}
	delete[] str;
	system("cls");
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