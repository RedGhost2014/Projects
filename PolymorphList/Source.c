#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String.h"
#include "PolymorphList.h"

int main()
{
	List* myStringList = CreateList();
	ListFunctions* myStringListFunctions = RegistrateListFunctions(printString, clearString, stringDuplicate);

	char* world = "world";
	char* another = "another";

	myStringListFunctions->addElement(myStringList, "hello", myStringListFunctions->DuplicateFunction);
	myStringListFunctions->addElement(myStringList, world, myStringListFunctions->DuplicateFunction);
	myStringListFunctions->addElement(myStringList, "and", myStringListFunctions->DuplicateFunction);
	myStringListFunctions->addElement(myStringList, another, myStringListFunctions->DuplicateFunction);
	myStringListFunctions->addElement(myStringList, "world", myStringListFunctions->DuplicateFunction);
	myStringListFunctions->clearElement(&myStringList->head->next->data);
	myStringListFunctions->clearElement(&myStringList->head->next->next->next->data);

	// Очистка двух элементов и избавление от них
	myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);
	printf("\n\n");
	myStringListFunctions->RefreshList(myStringList);
	myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);

	// Action Test 
	/*myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);
	printf("\n");
	myStringListFunctions->clearElement(&myStringList->head->next->data);
	myStringListFunctions->popBack(myStringList, myStringListFunctions->clearElement);

	myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);
	printf("\n");
	myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);
	myStringListFunctions->forEach(myStringList, myStringListFunctions->clearElement);
	printf("\n");
	myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);*/


	myStringList = ListCompose(myStringList, myStringListFunctions->DuplicateFunction, myStringListFunctions->clearElement);
	printf("\nPrinting After List compose:\n");
	myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);

	printf("\nPrinting After adding elements:\n");
	myStringListFunctions->addElement(myStringList, "Some", myStringListFunctions->DuplicateFunction);
	myStringListFunctions->addElement(myStringList, "Text", myStringListFunctions->DuplicateFunction);
	myStringListFunctions->forEach(myStringList, myStringListFunctions->printElements);




	// Важно: Добавление элементов после компоновки списка начинает разделять память
	// Элементы которые объеденились в массив почистятся через обычный free(List->head);
	// Но добавленные элементы после компоновки влекут за собой потерю памяти.
	// Максимально филосовский вопрос: Как следить за этим?
	//free(myStringList->head);
	//free(myStringList);

	//myStringListFunctions->DeleteListFunction(myStringList);

	printf("\n\n");
	return 0;
}