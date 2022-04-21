#include "ClassList.h"

void DeleteClassList(ClassList* thisclasslist)
{
	ClassNode* ptr = thisclasslist->head;
	ClassNode* fast = thisclasslist->head->next;
	while (fast != 0)
	{
		free(ptr->Class->classname);
		free(ptr->Class);
		free(ptr);
		ptr = fast;
		fast = fast->next;
	}
	//ptr->Class->clearElement(ptr->data);
	free(ptr->Class->classname);
	free(ptr->Class);
	free(ptr);
	thisclasslist->head = 0;
	thisclasslist->current = 0;
	thisclasslist = 0;
}

ClassList* CreateClassList()
{
	ClassList* newClassList = (ClassList*)malloc(sizeof(ClassList));
	newClassList->head = (ClassNode*)malloc(sizeof(ClassNode));
	newClassList->head->next = NULL;
	newClassList->head->previous = NULL;
	newClassList->current = newClassList->head;
	newClassList->head->Class = (Class*)malloc(sizeof(Class));
	newClassList->head->Class->classname = NULL;
	newClassList->head->Class->clearElement = NULL;
	newClassList->head->Class->printElement = NULL;
	newClassList->head->Class->copyElement = NULL;
	return newClassList;
}

void addClassToClassList(ClassList* classlist, const char* classname, ClearElement* clearFunction, PrintElement* printFunction, CopyElement* copyFunction)
{
	if (isClassExist(classlist, classname))
	{
		printf("Exception: Addable class \"%s\" already exist.\n", classname);
		return;
	}
	char* name = (char*)malloc((strlen(classname) + 1) * sizeof(char));
	name[strlen(classname)] = '\0';
	for (size_t i = 0; i < strlen(classname); i++)
	{
		name[i] = classname[i];
	}
	if (classlist->head->Class->classname == NULL)
	{
		classlist->head->Class->classname = name;
		classlist->head->Class->clearElement = clearFunction;
		classlist->head->Class->printElement = printFunction;
		classlist->head->Class->copyElement = copyFunction;
	}
	else
	{
		classlist->current->next = (ClassNode*)malloc(sizeof(ClassNode));
		classlist->current->next->previous = classlist->current;
		classlist->current = classlist->current->next;
		classlist->current->next = NULL;

		classlist->current->Class = (Class*)malloc(sizeof(Class));
		classlist->current->Class->classname = name;
		classlist->current->Class->clearElement = clearFunction;
		classlist->current->Class->printElement = printFunction;
		classlist->current->Class->copyElement = copyFunction;
	}
}

bool isClassExist(ClassList* classlist, const char* classname)
{
	ClassNode* tmp = classlist->head;
	while (tmp != NULL)
	{
		if (tmp->Class != NULL && tmp->Class->classname != NULL)
		{
			if (!strcmp((char*)tmp->Class->classname, classname))
			{
				return true;
			}
		}
		tmp = tmp->next;
	}
	return false;
}

Class* findClass(ClassList* classlist, const char* classname)
{
	ClassNode* tmp = classlist->head;
	while (tmp != NULL)
	{
		if (tmp->Class != NULL && tmp->Class->classname != NULL)
		{
			if (!strcmp((char*)tmp->Class->classname, classname))
			{
				return tmp->Class;
			}
		}
		tmp = tmp->next;
	}
	return NULL;
}

void printClassesFromClassList(ClassList* classlist)
{
	size_t ordernumber = 0;
	ClassNode* tmp = classlist->head;
	while (tmp != NULL)
	{
		printf("%d) %s\n", ordernumber, tmp->Class->classname);
		tmp = tmp->next;
		ordernumber++;
	}
	return false;
}

void DeleteClass(ClassList* classlist, const char* classname)
{
	if (!isClassExist(classlist, classname))
	{
		printf("Exception: This class \"%s\" not exist.\n", classname);
		return;
	}

	ClassNode* tmpPtr = classlist->head;
	while (!strcmp(tmpPtr->Class->classname, classname) && tmpPtr != NULL)
	{
		tmpPtr = tmpPtr->next;
	}
	if (tmpPtr != NULL)
	{
		ClassNode* nextone = tmpPtr->next;
		ClassNode* previousone = tmpPtr->previous;
		free(tmpPtr->Class->classname);
		free(tmpPtr->Class);
		free(tmpPtr);
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
	}
}