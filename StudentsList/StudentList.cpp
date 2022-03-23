#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "StudentsList.hpp"

using namespace std;

extern int _cdecl strContain(const char* strToFind, const char* baseStr);

/* Student class */

Student::Student(const char* name, const char* surname, const char* group, const char* phone, short age, short* marks)
{
	this->age = age;
	this->name = name;
	this->surname = surname;
	this->group = group;
	this->phone = phone;
	this->marks[0] = marks[0];
	this->marks[1] = marks[1];
	this->marks[2] = marks[2];
	this->marks[3] = marks[3];
}

Student::~Student()
{
	delete[] this->name;
	delete[] this->surname;
	delete[] this->group;
	delete[] this->phone;
}

void Student::printInfo()
{
	cout << surname << " " << name << ", " << age << endl;
	cout << "Group:\t" << group << endl;
	cout << "Phonenumber:\t" << phone << endl;
}

void Student::printConstructedInfo()
{
	cout << surname << " " << name << ", " << age << endl;
	cout << "Group:\t" << group << endl;
	cout << "Phonenumber:\t" << phone << endl;
	cout << "Marks: " << endl;
	cout << "\tIT: " << this->marks[0] << endl;
	cout << "\tMATAN: " << this->marks[1] << endl;
	cout << "\tGeometry: " << this->marks[2] << endl;
	cout << "\tAlgebra: " << this->marks[3] << endl;
}

void Student::changeMarks(short* marks)
{
	this->marks[0] = marks[0];
	this->marks[1] = marks[1];
	this->marks[2] = marks[2];
	this->marks[3] = marks[3];
}

const char* Student::getName()
{
	return this->name;
}

const char* Student::getSurname()
{
	return this->surname;
}

const char* Student::getGroup()
{
	return this->group;
}

short* Student::getMarks()
{
	return marks;
}


















/* List class */

List::List()
{
	this->root = new Node;
	this->listCapacity = 1;
	this->current = root;
}

List::~List()
{
	Node* backptr = this->root;
	Node* forwardptr = this->root;
	while (forwardptr != 0)
	{
		forwardptr = forwardptr->next;
		delete backptr;
		backptr = forwardptr;
	}
}

void List::addStudent(const char* name, const char* surname, const char* group, const char* phone, short age, short* marks)
{
	if (!this->root->isContain())
	{
		//this->current->addStudent(name, surname, group, phone, age, marks);
		this->root->addStudent(name, surname, group, phone, age, marks);
	}
	else
	{
		Node* ptr = this->root;
		while (ptr->next != 0)
		{
			if (!ptr->next->isContain())
			{
				/*Node* tmp = ptr->next;
				ptr->next = ptr->next->next;
				delete tmp;*/

				ptr->next->addStudent(name, surname, group, phone, age, marks);
				return;
			}
			ptr = ptr->next;
		}

		this->current->next = new Node;
		this->current->next->addStudent(name, surname, group, phone, age, marks);
		this->current = current->next;
		this->listCapacity++;
	}
}

void List::printDynamicList(const char* surname)
{
	Node* ptr = root;

	bool found = false;

	int number = 1;
	while (1)
	{
		if (ptr->isContain() && (strContain(surname, ptr->getStudent()->getSurname()) >= 0))
		{
			found = true;
			cout << number << ") " << ends;
			number++;
			ptr->getStudent()->printConstructedInfo();
			cout << endl;
		}
		if (ptr->next == 0)
		{
			break;
		}
		ptr = ptr->next;
	}
	if (!found)
	{
		cout << "Not found." << endl;
	}
}


void List::printList()
{
	Node* ptr = root;

	int number = 1;
	while (1)
	{
		cout << number << ") " << ends;
		number++;
		if (ptr->isContain())
		{
			ptr->getStudent()->printInfo();
			cout << endl;
		}
		else
		{
			cout << "This position is clear." << endl;
			cout << endl;
		}
		if (ptr->next == 0)
		{
			break;
		}
		ptr = ptr->next;
	}
}

void List::printList(const char* group)
{
	Node* ptr = root;

	int number = 1;
	while (1)
	{
		if (ptr->isContain() && !strcmp(ptr->getStudent()->getGroup(), group))
		{
			cout << number << ") " << ends;
			number++;
			ptr->getStudent()->printConstructedInfo();
			cout << endl;
		}
		if (ptr->next == 0)
		{
			break;
		}
		ptr = ptr->next;
	}
}

void List::printList(float morethanmark)
{
	Node* ptr = root;

	int number = 1;
	while (1)
	{

		if (ptr->isContain())
		{
			float sum = ptr->getStudent()->getMarks()[0] + ptr->getStudent()->getMarks()[1] + ptr->getStudent()->getMarks()[2] + ptr->getStudent()->getMarks()[3];
			if ((sum/4) >= morethanmark)
			{
				cout << number << ") " << ends;
				number++;
				ptr->getStudent()->printConstructedInfo();
				cout << endl;
			}
		}
		if (ptr->next == 0)
		{
			break;
		}
		ptr = ptr->next;
	}
}

void List::clearStudent(int id)
{
	int ID = id - 1;
	if (ID < 0)
	{
		throw WrongInputException("Exception: Invalid list ID.\n");
		//cout << "Exception: Invalid list ID." << endl;
		return;
	}
	Node* ptr = root;
	for (int i = 0; i < ID; i++)
	{
		if (ptr == 0)
		{
			throw WrongInputException("Exception: ID out of bounds.\n");
			//cout << "Exception: Out of bounds." << endl;
			return;
		}
		ptr = ptr->next;
	}

	if (ptr == 0)
	{
		throw WrongInputException("Exception: ID out of bounds.\n");
		//cout << "Exception: Out of bounds." << endl;
		return;
	}

	if (ptr->isContain())
	{
		cout << "Info about student " << ptr->getStudent()->getSurname() << " " << ptr->getStudent()->getName() << " was been cleared." << endl;
		ptr->deleteStudent();
	}
	else
	{
		cout << "\nStudent not found." << endl;
	}
}

void List::clearStudent(float lessthanmark)
{
	Node* ptr = root;

	while (ptr != 0)
	{
		if (ptr->isContain())
		{
			float sum = ptr->getStudent()->getMarks()[0] + ptr->getStudent()->getMarks()[1] + ptr->getStudent()->getMarks()[2] + ptr->getStudent()->getMarks()[3];
			if ((sum / 4) < lessthanmark)
			{
				cout << "Info about student " << ptr->getStudent()->getSurname() << " " << ptr->getStudent()->getName() << " was been cleared." << endl;
				ptr->deleteStudent();
			}
		}
		ptr = ptr->next;
	}
}

void List::clearStudent(const char* surname, const char* group)
{
	Node* ptr = root;

	while (ptr->next != 0)
	{
		if (ptr->isContain())
		{
			if ((!strcmp(ptr->getStudent()->getSurname(), surname)) & !strcmp(ptr->getStudent()->getGroup(), group))
			{
				cout << "Info about student " << ptr->getStudent()->getSurname() << " " << ptr->getStudent()->getName() << " was been cleared." << endl;
				ptr->deleteStudent();
				return;
			}
		}
		ptr = ptr->next;
	}
	cout << "\nStudent not found." << endl;
}

void List::deleteStudent(int id)
{
	int ID = id - 1;
	if (ID < 0)
	{
		throw WrongInputException("Exception: Invalid list ID.\n");
		//cout << "Exception: Invalid list ID." << endl;
		return;
	}
	Node* ptr = root;
	Node* rememberptr = root;
	for (int i = 0; i < ID; i++)
	{
		if (ptr == 0)
		{
			throw WrongInputException("Exception: ID out of bounds.\n");
			//cout << "Exception: Out of bounds." << endl;
			return;
		}
		ptr = ptr->next;
		rememberptr = ptr;
	}

	if (ptr == 0)
	{
		throw WrongInputException("Exception: ID out of bounds.\n");
		//cout << "Exception: Out of bounds." << endl;
		return;
	}
	
	if (ptr->isContain())
	{
		cout << "Student " << ptr->getStudent()->getSurname() << " " << ptr->getStudent()->getName() << " was been deleted." << endl;
		ptr->deleteStudent();
	}
	else
	{
		cout << "\nStudent not found." << endl;
		return;
	}
	ptr = root;
	while (ptr->next != 0)
	{
		if (ptr->next == rememberptr)
		{
			ptr->next = rememberptr->next;
			delete rememberptr;
			break;
		}
		ptr = ptr->next;
	}
	if (!root->isContain())
	{
		Node* tmp = root;
		this->root = tmp->next;
		delete tmp;
	}
}

void List::deleteStudent(const char* surname, const char* group)
{
	Node* ptr = root;
	Node* rememberptr = root;
	bool find = false;

	while (ptr->next != 0)
	{
		if (ptr->isContain())
		{
			if ((!strcmp(ptr->getStudent()->getSurname(), surname)) & !strcmp(ptr->getStudent()->getGroup(), group))
			{
				rememberptr = ptr;
				cout << "Student " << ptr->getStudent()->getSurname() << " " << ptr->getStudent()->getName() << " was been deleted." << endl;
				ptr->deleteStudent();
				find = true;
			}
		}
		ptr = ptr->next;
	}
	ptr = root;
	while (ptr->next != 0)
	{
		if (ptr->next == rememberptr)
		{
			ptr->next = rememberptr->next;
			delete rememberptr;
			break;
		}
		ptr = ptr->next;
	}
	if (!root->isContain())
	{
		Node* tmp = root;
		this->root = tmp->next;
		delete tmp;
	}

	if (!find)
	{
		cout << "\nStudent not found." << endl;
	}
}

void List::deleteStudent(float lessthanmark)
{
	this->clearStudent(lessthanmark);
	this->GarbageCollector();
}

void List::GarbageCollector()
{
	Node* ptr = root;

	while (ptr->next != 0)
	{
		/*if (ptr == 0)
		{
			break;
		}*/
		if (!ptr->next->isContain())
		{
			Node* tmp = ptr->next;
			ptr->next = ptr->next->next;
			delete tmp;
			continue;
		}
		ptr = ptr->next;
	}
	if (!root->isContain())
	{
		Node* tmp = root;
		this->root = tmp->next;
		delete tmp;
	}
}

























/* Node class */

Node::Node()
{
	this->student = 0;
}

Student* Node::getStudent()
{
	return this->student;
}

void Node::deleteStudent()
{
	delete this->student;
	this->student = 0;
}

void Node::addStudent(const char* name, const char* surname, const char* group, const char* phone, short age, short* marks)
{
	this->student = new Student(name, surname, group, phone, age, marks);
}

bool Node::isContain()
{
	if (this->student != 0)
	{
		return true;
	}
	else return false;
}
