#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef void (PrintElement)(void* elem);
typedef void (ClearElement)(void* elem);
typedef void* (CopyElement)(void* elem);

typedef struct Class
{
	const char* classname;
	PrintElement* printElement;
	ClearElement* clearElement;
	CopyElement* copyElement;
} Class;

typedef struct ClassNode
{
	struct ClassNode* next;
	struct ClassNode* previous;
	Class* Class;
} ClassNode;

typedef struct ClassList
{
	ClassNode* head;
	ClassNode* current;

} ClassList;

ClassList* CreateClassList();
void DeleteClassList(ClassList* thisclasslist);
void addClassToClassList(
	ClassList* classlist, const char* classname, 
	ClearElement* clearFunction, PrintElement* printFunction, CopyElement* copyFunction);

void printClassesFromClassList(ClassList* classlist);
bool isClassExist(ClassList* classlist, const char* classname);
Class* findClass(ClassList* classlist, const char* classname);