#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ClassList.h"

typedef void (ListAction)(void*);

typedef struct Node
{
	struct Node* next;
	struct Node* previous;
	void* data;
	Class* Class;
} Node;

typedef struct FlexibleList
{
	Node* head;
	Node* current;
	
	ClassList* ClassList;

	size_t capacity;
} FlexibleList;

FlexibleList* CreateFlexibleList();
void DeleteFlexibleList(FlexibleList* thisList);
void addElementToList(FlexibleList* thislist, const char* classtype, void* element);

// Очистка списка от узлов в которых нет данных
void Refresh(FlexibleList* thisList);

void forEachInClass(FlexibleList* thislist, const char* classtype, ListAction* action);
void forEachAction(FlexibleList* thislist, const char* action);
void ListNodePolymorhicAction(const char* action, Node* element);
Node* findNodeByClassAndId(FlexibleList* thislist, const char* classtype, int id);
void popBack(FlexibleList* thislist);
void popBackByClass(FlexibleList* thislist, const char* classtype);