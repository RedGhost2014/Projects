#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	struct Node* next;
	struct Node* previous;
	void* data;

} Node;

typedef struct List
{
	Node* head;
	Node* current;
	size_t capacity;

} List;

typedef void (ListAction)(void*);
typedef void* (NodeDataDuplicate)(void*);

typedef void (AddElement)(List*, void*, NodeDataDuplicate*);
typedef void (DeleteListFunction)(List*);
typedef void (ForEachAction)(List*, ListAction*);
typedef void (PopBack)(List*, ListAction*);
typedef void (RefreshList)(List*);

typedef struct ListFunctions
{
	AddElement* addElement;
	PopBack* popBack;
	RefreshList* RefreshList;

	ListAction* printElements;
	ListAction* clearElement;

	DeleteListFunction* DeleteListFunction;
	ForEachAction* forEach;

	NodeDataDuplicate* DuplicateFunction;

} ListFunctions;

// Создаёт список
List* CreateList();
// Удаляет список
void DeleteList(List* thisList);
// Избавляет список от узлов с пустыми данными
void Refresh(List* thisList);


void forEach(List* thislist, ListAction* action);
void popBack(List* thislist, ListAction* clearaction);
void addElement(List* thislist, void* elem, NodeDataDuplicate* dataCreate);

// Регистрация фукнций для вашего списка
ListFunctions* RegistrateListFunctions(ListAction* printElements, ListAction* clearElement, NodeDataDuplicate* NodeDataDuplicate);

// Компоновка списка в массив
List* ListCompose(List* thisList, NodeDataDuplicate* duplicateAction, ListAction* clearAction);