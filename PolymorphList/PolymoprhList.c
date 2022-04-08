#include "PolymorphList.h"

// Для проверки работы компоновки списка включите макрос
//#define _DEBUG_ 

List* CreateList()
{
	List* newList = (List*)malloc(sizeof(List));
	newList->capacity = 1;
	newList->head = (Node*)malloc(sizeof(Node));
	newList->head->data = NULL;
	newList->current = newList->head;
	newList->head->next = NULL;
	newList->head->previous = NULL;
	return newList;
}

void DeleteList(List* thisList)
{
	Node* ptr = thisList->head;
	Node* fast = thisList->head->next;
	while (fast != 0)
	{
		free(ptr);
		ptr = fast;
		fast = fast->next;
	}
	free(ptr);
	thisList->capacity = 0;
	thisList->head = 0;
	thisList->current = 0;
	thisList = 0;
}

void forEach(List* thislist, ListAction* action)
{
	Node* tmpPtr = thislist->head;
	while (tmpPtr != 0)
	{
		action(&tmpPtr->data);
		tmpPtr = tmpPtr->next;
	}
}

void popBack(List* thislist, ListAction* clearaction)
{
	Node* tmpPtr = thislist->head;
	while (tmpPtr->next != 0)
	{
		tmpPtr = tmpPtr->next;
	}
	clearaction(&tmpPtr->data);
	if (tmpPtr == thislist->head)
	{
		return;
	}
	tmpPtr = tmpPtr->previous;
	free(tmpPtr->next);
	tmpPtr->next = NULL;
	thislist->capacity--;
}

void Refresh(List* thisList)
{
	Node* tmpPtr = thisList->head;
	while (tmpPtr != 0)
	{
		if (tmpPtr->data == NULL)
		{
			Node* nextone = tmpPtr->next;
			Node* previousone = tmpPtr->previous;
			free(tmpPtr);
			previousone->next = nextone;
			nextone->previous = previousone;
			tmpPtr = nextone;
			thisList->capacity--;
			//tmpPtr->next = nodeafterone;
			//nodeafterone->previous = tmpPtr;
		}
		else tmpPtr = tmpPtr->next;
	}
}

void addElement(List* thislist, void* elem, NodeDataDuplicate* dataCreate)
{
	if (thislist->head->data == 0)
	{
		thislist->head->data = dataCreate(elem);
	}
	else
	{
		thislist->current->next = (Node*)malloc(sizeof(Node)); // Создали элемент
		thislist->current->next->previous = thislist->current; // Назначили связь новосозданного элемента с текущим

		thislist->current = thislist->current->next;		   // Прыгнули в новосозданный
		thislist->current->data = dataCreate(elem);			   // Задали значение

		thislist->current->next = NULL;					       // Следующий указатель нулевой

		thislist->capacity++;
	}
}

ListFunctions* RegistrateListFunctions(ListAction* printElements, ListAction* clearElement, NodeDataDuplicate* NodeDataDuplicate)
{
	ListFunctions* lf = (ListFunctions*)malloc(sizeof(ListFunctions));
	lf->clearElement = clearElement;
	lf->printElements = printElements;
	lf->DuplicateFunction = NodeDataDuplicate;

	lf->addElement = addElement;
	lf->forEach = forEach;
	lf->popBack = popBack;
	lf->DeleteListFunction = DeleteList;
	lf->RefreshList = Refresh;
}

List* ListCompose(List* thisList, NodeDataDuplicate* duplicateAction, ListAction* clearAction)
{
	size_t oldcapacity = thisList->capacity;
	Node* nodemass = (Node**)malloc(oldcapacity * sizeof(Node));
	Node* tmpPtr = thisList->head;
	for (int i = 0; i < oldcapacity; i++)
	{
		nodemass[i].data = (char*)duplicateAction(tmpPtr->data);
		tmpPtr = tmpPtr->next;
	}

	tmpPtr = thisList->head;
	while (tmpPtr != 0)
	{
		clearAction(&tmpPtr->data);
		tmpPtr = tmpPtr->next;
	}
	DeleteList(thisList);

	List* newList = (List*)malloc(sizeof(List));

	nodemass[0].previous = NULL;
	nodemass[oldcapacity - 1].next = NULL;

	for (int i = 0; i < oldcapacity - 1; i++)
	{
		nodemass[i].next = &nodemass[i + 1];
	}

	for (int i = oldcapacity - 1; i > 0; i--)
	{
		nodemass[i].previous = &nodemass[i - 1];
	}

	newList->head = &nodemass[0];
	newList->current = &nodemass[oldcapacity - 1];

#ifdef _DEBUG_
	//Debug
	printf("Printing from Mass:\n");
	for (int i = 0; i < oldcapacity; i++)
	{
		printf("%s ", (char*)nodemass[i].data);
	}

	// Debug
	printf("\nPrinting from List:\n");
	tmpPtr = newList->head;

	while (tmpPtr != 0)
	{
		printf("%s ", (char*)tmpPtr->data);
		tmpPtr = tmpPtr->next;
	}
	tmpPtr = newList->head;


	// Memory address debugging
	printf("\n\nAddress check:\n\n");
	for (int i = 0; i < oldcapacity; i++)
	{
		printf("nodemass[%d] = %p = %s\n", i, &nodemass[i], (char*)nodemass[i].data);
	}

	printf("\n\n");

	int i = 0;
	while (tmpPtr != 0)
	{
		printf("Node[%d] = %p = %s\n", i, tmpPtr, (char*)tmpPtr->data);
		tmpPtr = tmpPtr->next;
		i++;
	}

	printf("\nPrinting from List by itterations:\n");
	tmpPtr = newList->head;
	for (int i = 0; i < oldcapacity; i++)
	{
		printf("%s ", (char*)tmpPtr->data);
		tmpPtr++;
	}
#endif

	newList->capacity = oldcapacity;

	return newList;
}