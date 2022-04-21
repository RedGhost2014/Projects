#include "List.h"

void DeleteFlexibleList(FlexibleList* thisList)
{
	Node* ptr = thisList->head;
	Node* fast = thisList->head->next;
	while (fast != NULL)
	{
		ptr->Class->clearElement(&ptr->data);
		//free(ptr->Class->classname);
		//free(ptr->Class);
		free(ptr);
		ptr = fast;
		fast = fast->next;
	}
	ptr->Class->clearElement(&ptr->data);
	free(ptr);
	DeleteClassList(thisList->ClassList);
	thisList->capacity = NULL;
	thisList->head = NULL;
	thisList->current = NULL;
	thisList->ClassList = NULL;
	thisList = NULL;
	
}

FlexibleList* CreateFlexibleList()
{
	FlexibleList* newFlexibleList = (FlexibleList*)malloc(sizeof(FlexibleList));
	newFlexibleList->capacity = 1;
	newFlexibleList->head = (Node*)malloc(sizeof(Node));
	newFlexibleList->head->data = NULL;
	newFlexibleList->current = newFlexibleList->head;
	newFlexibleList->head->next = NULL;
	newFlexibleList->head->previous = NULL;
	newFlexibleList->head->Class = NULL;

	newFlexibleList->ClassList = CreateClassList();
	return newFlexibleList;
}

void forEachAction(FlexibleList* thislist, const char* action)
{
	int i = 0;
	Node* tmpPtr = thislist->head;
	if (!_stricmp(action, "print"))
	{
		while (tmpPtr != 0)
		{
			i++;
			printf("%d) ", i);
			tmpPtr->Class->printElement(&tmpPtr->data);
			/*if (tmpPtr->data != NULL)
			{
			}*/
			tmpPtr = tmpPtr->next;
		}
	}
	else if (!_stricmp(action, "clear"))
	{
		while (tmpPtr != 0)
		{
			tmpPtr->Class->clearElement(&tmpPtr->data);
			/*if (tmpPtr->data != NULL)
			{
			}*/
			tmpPtr = tmpPtr->next;
		}
	}
	else
	{
		return;
	}
	
}

void forEachInClass(FlexibleList* thislist, const char* classtype, ListAction* action)
{
	if (!isClassExist(thislist->ClassList, classtype))
	{
		printf("Exception: Class \"%s\" does not exist.\n", classtype);
		return;
	}
	Node* tmpPtr = thislist->head;
	while (tmpPtr != 0)
	{
		if (!strcmp((char*)tmpPtr->Class->classname, classtype))
			action(&tmpPtr->data);
		tmpPtr = tmpPtr->next;
	}
}

void addElementToList(FlexibleList* thislist, const char* classtype, void* element)
{
	if (!isClassExist(thislist->ClassList, classtype))
	{
		printf("Exception: Class \"%s\" does not exist.\n", classtype);
		return;
	}
	else
	{
		Class* tmpClass = findClass(thislist->ClassList, classtype);
		if (thislist->head->data == NULL)
		{
			thislist->head->data = tmpClass->copyElement(element);
			thislist->head->Class = tmpClass;
		}
		else
		{
			thislist->current->next = (Node*)malloc(sizeof(Node));		// Создали элемент
			thislist->current->next->previous = thislist->current;		// Назначили связь новосозданного элемента с текущим

			thislist->current = thislist->current->next;				// Прыгнули в новосозданный
			thislist->current->data = tmpClass->copyElement(element);	// Задали значение
			thislist->current->Class = tmpClass;
			thislist->current->next = NULL;								// Следующий указатель нулевой
			
			thislist->capacity++;
		}
	}
}

void popBack(FlexibleList* thislist)
{
	Node* tmpPtr = thislist->head;
	while (tmpPtr->next != 0)
	{
		tmpPtr = tmpPtr->next;
	}
	tmpPtr->Class->clearElement(&tmpPtr->data);
	if (tmpPtr == thislist->head)
	{
		return;
	}
	tmpPtr = tmpPtr->previous;

	free(tmpPtr->next);
	tmpPtr->next = NULL;
	thislist->current = tmpPtr;
	thislist->capacity--;
}

void popBackByClass(FlexibleList* thislist, const char* classtype)
{
	if (!isClassExist(thislist, classtype))
	{
		printf("Exception: Class \"%s\" does not exist.\n", classtype);
		return;
	}
	Node* tmpPtr = thislist->head;
	while (tmpPtr->next != 0)
	{
		tmpPtr = tmpPtr->next;
	}	
	
	while(tmpPtr->previous != 0 && strcmp(tmpPtr->Class->classname, classtype))
	{
		tmpPtr = tmpPtr->previous;
	}

	tmpPtr->Class->clearElement(&tmpPtr->data);
	if (tmpPtr == thislist->head)
	{
		return;
	}

	if (tmpPtr->next == NULL)
	{
		thislist->current = tmpPtr->previous;
		tmpPtr = tmpPtr->previous;
		free(tmpPtr->next);
		tmpPtr->next = NULL;
		thislist->capacity--;
	}
	else
	{
		tmpPtr = tmpPtr->previous;
		Node* nextto = tmpPtr->next->next;
		free(tmpPtr->next);
		tmpPtr->next = nextto;
		thislist->capacity--;
	}
}

Node* findNodeByClassAndId(FlexibleList* thislist, const char* classtype, int id)
{
	if (!isClassExist(thislist->ClassList, classtype))
	{
		printf("Exception: Class \"%s\" does not exist.\n", classtype);
		return 0;
	}
	int currentID = 0;
	Node* tmpPtr = thislist->head;
	
	while (tmpPtr != NULL)
	{
		if (!strcmp(tmpPtr->Class->classname, classtype))
		{
			currentID++;
			if (currentID == id)
				return tmpPtr;
		}
		tmpPtr = tmpPtr->next;
	}
	return 0;
}

void ListNodePolymorhicAction(const char* action, Node* element)
{
	if (element == NULL || action == NULL || strlen(action) == 0)
	{
		printf("Exception: Argument is null-pointer.\n");
		return;
	}
	if (!_stricmp(action, "print"))
	{
		element->Class->printElement(&element->data);
	}
	else if (!_stricmp(action, "clear"))
	{
		element->Class->clearElement(&element->data);
	}
	else
	{
		printf("Exception: Unexpected action.\n");
		return;
	}
}


void Refresh(FlexibleList* thisList)
{
	Node* tmpPtr = thisList->head;

	Node* headswapper = thisList->head;
	while (headswapper->data == NULL)
	{
		if (headswapper->next != NULL)
		{
			headswapper = headswapper->next;
		}
	}
	thisList->head = headswapper;

	while (tmpPtr != 0)
	{
		if (tmpPtr->data == NULL)
		{
			Node* nextone = tmpPtr->next;
			Node* previousone = tmpPtr->previous;

			if (nextone == NULL && previousone == NULL)
			{
				return;
			}
			if (nextone == NULL)
			{
				previousone->next = NULL;
			}
			if (previousone == NULL)
			{
				nextone->previous = NULL;
			}
			if ((nextone != NULL) && (previousone != NULL))
			{
				nextone->previous = previousone;
				previousone->next = nextone;
			}

			free(tmpPtr);

			/*if (nextone != NULL && previousone != NULL)
			{
				nextone->previous = previousone;
			}
			if (previousone != NULL && nextone != NULL)
			{
				previousone->next = nextone;
			}*/
			tmpPtr = nextone;
			thisList->capacity--;
			//tmpPtr->next = nodeafterone;
			//nodeafterone->previous = tmpPtr;
		}
		else tmpPtr = tmpPtr->next;
	}

	tmpPtr = thisList->head;

	while (tmpPtr->next != NULL)
	{
		tmpPtr = tmpPtr->next;
	}
	thisList->current = tmpPtr;
}