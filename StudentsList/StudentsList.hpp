//#pragma once
#ifndef _STUDENTSLIST
#define _STUDENTSLIST

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <exception>

using namespace std;

class MsgException : public exception {
public:

	explicit MsgException(const char* what)
	{
		whatStr = (char*)what;
	}

	const char* what() const noexcept override
	{
		return whatStr;
	}

private:
	char* whatStr;
};

class WrongInputException : public MsgException
{
public:
	explicit WrongInputException(const char* what) : MsgException(what) { }
};

using namespace std;

class Student
{
private:
	const char* name;
	const char* surname;
	const char* group;
	const char* phone;

	short marks[4];
	short age;
public:
	Student();
	Student(const char* name, const char* surname, const char* group, const char* phone, short age, short* marks);
	~Student();

	void printInfo();
	void printConstructedInfo();

	const char* getNumber();
	const char* getSurname();
	const char* getName();
	const char* getGroup();
	short* getMarks();

	void changeMarks(short* marks);

	//void createStudent(char* name, char* surname, char* group, char* phone, short age);

};

class Node
{
	Student* student;

public:
	Node();

	Node* next;
	void addStudent(const char* name, const char* surname, const char* group, const char* phone, short age, short* marks);
	Student* getStudent();
	void deleteStudent();
	bool isContain();
};



class List /*: public Node*/
{
private:
	int listCapacity;
	Node* root;

public:

	Node* current;
	void addStudent(const char* name, const char* surname, const char* group, const char* phone, short age, short* marks);

	void clearStudent(const char* surname, const char* group);
	void clearStudent(int id);
	void clearStudent(float lessthanmark);

	void deleteStudent(const char* surname, const char* group);
	void deleteStudent(int id);
	void deleteStudent(float lessthanmark);

	void printList();
	void printList(const char* group);
	void printList(float morethanmark);

	void printDynamicList(const char* surname);

	void GarbageCollector();
	List();
	~List();
};



#endif // !_STUDENTSLIST
