#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "StudentsList.hpp"
#include "Header.hpp"

using namespace std;

extern List* mainList;

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

			cout << endl;
			mainList->printList();
			gotoxy(pos, 1);

			while (1)
			{
				x = _getch();
				system("cls");
				cout << "Enter the surname:" << endl;
				cout << surname;
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
						if (pos != 0)
						{
							cout << endl;
							mainList->printDynamicList(surname);
						}
					}
				}
				else if (x == VK_ESCAPE)
				{
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
				if (pos == 0)
				{
					cout << endl;
					mainList->printList();
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

	static const char* groupmass[] = { "MK101", "MK102", "MN101", "MN102", "MP101", "MP102" , "MP103", "MT101", "MT102" };

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