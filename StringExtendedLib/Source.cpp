//#include <cstdio>
//#include <cstdlib>
//#include <iostream>
//#define STREX_NO_WARNINGS
#include "strEx.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus

using namespace std;
using namespace strEx;

int StringSortTests();
int StringFunctionsTest();

#endif // __cplusplus

int main()
{
	StringFunctionsTest();

	/*size_t size = 0;
	char** mass = strSplitByToken("Hello!World and,another.world,  s !sad", "!,", &size);

	for (size_t i = 0; i < size; i++)
	{
		printf("mass[%d] = %s\n", i, mass[i]);
	}

	for (size_t i = 0; i < size; i++)
	{
		STREX_DEALLOC(mass[i]);
	}
	STREX_DEALLOC(mass);*/
	//strSplitByParser
	//char* str = 
	//char* str = StringExtended::();

	/*size_t countOfSubstrings = 0;
	char** array = StringExtended::strSplitByParser("ststrsr", "str", &countOfSubstrings);

	for (int i = 0; i < countOfSubstrings; i++)
	{
		cout << "array[" << i << "] = " << array[i] << endl;
	}

	for (int i = 0; i < countOfSubstrings; i++)
	{
		STREX_DEALLOC(array[i]);
	}
	STREX_DEALLOC(array);

	return 0;
	const char* str = "Hello world";
	cout << "Basic str = " << str << endl;
	char* erasedStr = StringExtended::strErase("orl", str);


	cout << "\nstrErase test = " << erasedStr << endl;*/

}

#ifdef __cplusplus


int StringFunctionsTest()
{
	const char* str = "Hello World and another world";

	cout << "Basic str = " << str << endl;

	char* erasedStr = StringExtended::strErase(" and ", str);

	cout << "\nerasedStr = " <<  "strErase(\" and \", str) test: = " << erasedStr << endl;

	size_t size = 0;
	char** mass = StringExtended::strSplitByParser(erasedStr, "o", &size);

	cout << "\nstrSplit(erasedStr, \"o\") test:\n" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "mass[" << i << "] = " << mass[i] << endl;
	}

	cout << "\nstrConcat(mass[i], \" | \", mass[i + 1], \"\") test:\n" << endl;
	for (int i = 0; i < size - 1; i++)
	{
		mass[i] = StringExtended::strConcat(mass[i], "|", mass[i + 1], "");
	}
	for (int i = 0; i < size; i++)
	{
		cout << "mass[" << i << "] = " << mass[i] << endl;
	}

	cout << "\nstrReplace(mass[i], \"|\", \"QWERTY\") test:\n" << endl;

	for (int i = 0; i < size - 1; i++)
	{
		mass[i] = StringExtended::strReplace(mass[i], "|", "QWERTY");
	}
	for (int i = 0; i < size; i++)
	{
		cout << "mass[" << i << "] = " << mass[i] << endl;
	}

	for (int i = 0; i < size; i++)
	{
		STREX_DEALLOC(mass[i]);
	}
	STREX_DEALLOC(mass);
	STREX_DEALLOC(erasedStr);

	return 0;
}

int StringSortTests()
{
	const char* mass[] = { "Hello", "world", "And", "ANOTHER", "World" };

	cout << "Static string mass:\n" << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << "mass[" << i << "] = " << mass[i] << endl;
	}

	cout << "\nAfter sort AtoZ case_sensetive = false:\n" << endl;
	StringExtended::strSort_AtoZ(mass, 5, false);

	for (int i = 0; i < 5; i++)
	{
		cout << "mass[" << i << "] = " << mass[i] << endl;
	}

	cout << "\nAfter sort AtoZ case_sensetive = true:\n" << endl;
	StringExtended::strSort_AtoZ(mass, 5, true);

	for (int i = 0; i < 5; i++)
	{
		cout << "mass[" << i << "] = " << mass[i] << endl;
	}
	cout << endl;

	// Random Strings sort test
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int len = strlen(alphabet);

	int stringscount = 10;	 // Variables to play
	int stringsLen = 20;	 //

	char** strmass = STREX_ALLOC(char*, stringscount);
	for (int i = 0; i < stringscount; i++)
	{
		int localsize = (rand() % stringsLen) + 2;
		strmass[i] = STREX_ALLOC(char, localsize + 1);
		strmass[i][localsize] = '\0';


		for (int j = 0; j < localsize; j++)
		{
			strmass[i][j] = alphabet[rand() % len + 1];
		}
	}

	cout << "\n\n\n" << endl;
	cout << "Random strings:\n" << endl;

	for (int i = 0; i < stringscount; i++)
	{
		cout << i << ") " << strmass[i] << endl;
	}

	StringExtended::strSort_AtoZ((const char**)strmass, stringscount, false);

	cout << "\n\n" << endl;
	cout << "Random strings after sort AtoZ case_sensetive = false:\n" << endl;

	for (int i = 0; i < stringscount; i++)
	{
		cout << i << ") " << strmass[i] << endl;
	}

	StringExtended::strSort_AtoZ((const char**)strmass, stringscount, true);

	cout << "\n\n" << endl;
	cout << "Random strings after sort AtoZ case_sensetive = true:\n" << endl;

	for (int i = 0; i < stringscount; i++)
	{
		cout << i << ") " << strmass[i] << endl;
	}

	StringExtended::strSort_LenIncrease((const char**)strmass, stringscount);

	cout << "\n\n" << endl;
	cout << "Random strings after sort LenIncrease:\n" << endl;

	for (int i = 0; i < stringscount; i++)
	{
		cout << i << ") " << strmass[i] << endl;
	}


	for (int i = 0; i < stringscount; i++)
	{
		STREX_DEALLOC(strmass[i]);
	}
	STREX_DEALLOC(strmass);
	return 0;
}

#endif // __cplusplus