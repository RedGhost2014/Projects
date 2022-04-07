#pragma once
//#include "Declarator.h"

class Comparser
{
private:

	int left;
	int right;
	int answer;

	int op;

	int _cdecl CountOfDigits(int a);

public:
	Comparser();
	Comparser(const Comparser&) = delete;
	Comparser& operator=(const Comparser&) = delete;

	int _cdecl strContain(char* strToFind, char* baseStr);
	int _cdecl isHeroCanChange();


	// Math block
	void addResultObjects(Object* equalSign, int countOfColumns);
	bool _cdecl findOperation_Math(char* str);
	bool _cdecl retrieveNumbers_Math(char* str);
	void setAnswer();
	int getAnswer();

	// Counting Systems
	bool _cdecl retrieveNumbers_CS(char* str);
	void setAnswer_CS();
};
