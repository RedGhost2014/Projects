#include "List.h"
#include "String.h"
#include "Matrix.h"
#include <time.h>

int main()
{
	srand(time(0));
	FlexibleList* myList = CreateFlexibleList();

	const char* stringClass = "string";
	const char* matrixClass = "Matrix";

	addClassToClassList(myList->ClassList, stringClass, clearString, printString, stringDuplicate);
	addClassToClassList(myList->ClassList, matrixClass, clearMatrix, printMatrix, copyMatrix);

	printf("Classes existing in myList:\n");
	printClassesFromClassList(myList->ClassList);

	char* mystring = "Hello world";

	Matrix* myMatrix = createMatrix(3, 3);
	fillRandomMatrix(myMatrix);

	Matrix* anothermyMatrix = createMatrix(4, 4);
	fillRandomMatrix(anothermyMatrix);

	addElementToList(myList, stringClass, mystring);
	addElementToList(myList, stringClass, "and another");
	addElementToList(myList, stringClass, "world");
	addElementToList(myList, matrixClass, myMatrix);
	addElementToList(myList, matrixClass, anothermyMatrix);
	addElementToList(myList, stringClass, mystring);
	addElementToList(myList, stringClass, "and another");
	addElementToList(myList, stringClass, "world");

	printf("\n\nPrinting all stuff:\n\n");
	forEachAction(myList, "print");

	//forEachInClass(myList, stringClass, findClass(myList->ClassList, stringClass)->printElement);

	forEachInClass(myList, stringClass, findClass(myList->ClassList, stringClass)->clearElement);
	//forEachInClass(myList, matrixClass, findClass(myList->ClassList, matrixClass)->clearElement);

	//printf("\n\nPrinting strings in my list after clearing:\n\n");

	//forEachInClass(myList, stringClass, findClass(myList->ClassList, stringClass)->printElement);

	printf("\n\nPrinting all stuff:\n\n");
	forEachAction(myList, "print");

	//addElementToList(myList, stringClass, mystring);
	//addElementToList(myList, stringClass, "and another");
	//addElementToList(myList, stringClass, "world");
	//printf("\n\nPrinting all stuff:\n\n");
	//forEachAction(myList, "print");

	Refresh(myList);

	printf("\n\nPrinting all stuff:\n\n");
	forEachAction(myList, "print");

	addElementToList(myList, stringClass, mystring);
	addElementToList(myList, stringClass, "and another");
	addElementToList(myList, stringClass, "world");

	printf("\n\nPrinting all stuff:\n\n");
	forEachAction(myList, "print");

	forEachInClass(myList, matrixClass, findClass(myList->ClassList, matrixClass)->clearElement);

	printf("\n\nPrinting all stuff:\n\n");
	forEachAction(myList, "print");

	Refresh(myList);
	printf("\n\nPrinting all stuff:\n\n");
	forEachAction(myList, "print");

	//printf("\n\nPrinting matrix in my list:\n\n");
	//forEachInClass(myList, matrixClass, findClass(myList->ClassList, matrixClass)->printElement);
	//printf("\n\n\n\nPrinting all stuff in my list:\n\n");
	//forEachAction(myList, "print");

	//// deleting elements section 
	//ListNodePolymorhicAction("clear", findNodeByClassAndId(myList, matrixClass, 2));
	//forEachAction(myList, "print");
	//popBack(myList);
	////popBackByClass(myList, stringClass);
	//popBackByClass(myList, matrixClass);
	//printf("\n\n\nPrinting all stuff in my list after deleting:\n\n");
	//forEachAction(myList, "print");

	DeleteFlexibleList(myList);

	/*printf("\n\nPrinting choosed element in my list:\n\n");
	ListNodePolymorhicAction("clear", findNodeByClassAndId(myList, stringClass, 3));
	ListNodePolymorhicAction("clear", findNodeByClassAndId(myList, matrixClass, 2));
	ListNodePolymorhicAction("print", findNodeByClassAndId(myList, stringClass, 3));
	ListNodePolymorhicAction("print", findNodeByClassAndId(myList, matrixClass, 2));*/
	return 0;
}