#include "Declarator.h"
#include "Comparser.h"
#include <vector>

class Converter 
{
private:
	//Вектор содержит исходное число
	vector<int> a;
	//Исходная система счисления
	int iriginal;
public:
	//Конструктор, содержит 2 параметра: строка исходного числа, исходная система счисления
	Converter(string str, int original) {
		this->iriginal = original;
		//Заносит числа исходного числа в вектор
		for (int i = 0; i < str.length(); i++) {
			this->a.push_back(charToInt(str[i]));
		}
	}
	//Переводит символ в число, вместо некорректных символов возвращает -1
	int charToInt(char c) {
		if (c >= '0' && c <= '9' && (c - '0') < this->iriginal) {
			return c - '0';
		}
		else {
			if (c >= 'A' && c <= 'Z' && (c - 'A') < this->iriginal) {
				return c - 'A' + 10;
			}
			else {
				return -1;
			}
		}
	}
	//Переводит число в символ
	char intToChar(int c) {
		if (c >= 0 && c <= 9) {
			return c + '0';
		}
		else {
			return c + 'A' - 10;
		}
	}
	//Получает следующую цифру числа в новой системе счисления
	int nextNumber(int final) {
		int temp = 0;
		for (int i = 0; i < this->a.size(); i++) {
			temp = temp * this->iriginal + this->a[i];
			a[i] = temp / final;
			temp = temp % final;
		}
		return temp;
	}
	//Возвращает true - если массив состоит из одних нулей и false в противном случае
	bool zero() {
		for (int i = 0; i < this->a.size(); i++) {
			if (a[i] != 0) {
				return false;
			}
		}
		return true;
	}
	//Конвертирует исходное число в заданную систему счисления
	string convertTo(int final) {
		vector<int> b;
		int size = 0;
		do {
			b.push_back(this->nextNumber(final));
			size++;
		} while (!this->zero());

		string sTemp = "";
		for (int i = b.size() - 1; i >= 0; i--) {
			sTemp += intToChar(b[i]);
		}
		return sTemp;
	}
};

Comparser::Comparser()
{
	left = NULL;
	right = NULL;
	answer = NULL;
	op = NULL;
}

int Comparser::getAnswer()
{
	return answer;
}

void Comparser::setAnswer()
{
	if (op == '+')
		answer = left + right;
	else if (op == '-')
		answer = left - right;
	else if (op == '*')
		answer = left * right;
	else if (op == '/')
		answer = left / right;
}

void Comparser::setAnswer_CS()
{
	int currentSystem = -1;
	char* strnumber = new char[32];
	_itoa_s(left, strnumber, 32, 10);
	
	for (int i = 0; i < strlen(strnumber); i++)
	{
		int digit = strnumber[i] - '0';
		if (digit > currentSystem)
			currentSystem = digit;
	}

	string str = strnumber;
	Converter cvt(str, currentSystem + 1);
	
	string answer = cvt.convertTo(10);
	
	char* buffer = (char*)answer.c_str();
	this->answer = atoi(buffer);
	delete[] strnumber;
}

int _cdecl Comparser::CountOfDigits(int a)
{
	if (a == 0)
	{
		return 1;
	}
	int count = 0;
	while (a != 0)
	{
		count += 1;
		a = a / 10;
	}
	return count;
}

int _cdecl Comparser::strContain(char* strToFind, char* baseStr)
{
	int strlenOfToFind = strlen(strToFind);
	int strlenOfBaseStr = strlen(baseStr);
	int count = 0;
	int flag = -1;
	for (int i = 0; i < strlenOfBaseStr; i++)
	{
		if (strToFind[0] == baseStr[i])
		{
			flag = i;
			int z = i;
			for (int j = 0; j < strlenOfToFind; j++, z++)
			{
				if (strToFind[j] == baseStr[z])
				{
					count++;
					if (count == strlenOfToFind)
					{
						return flag;
					}
				}
				else
				{
					flag = -1;
					count = 0;
					break;
				}
			}
		}
	}
	return flag;
}

bool _cdecl Comparser::findOperation_Math(char* str)
{
	int size = strlen(str);
	int countOfSigns = 0;

	for (int i = 0; i < size; i++)
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			countOfSigns++;
			op = i;
		}
	}
	if (countOfSigns == 0)
	{
		op = NULL;
		return false;
	}
	else
	{
		return true;
	}
}

int _cdecl Comparser::isHeroCanChange()
{
	Game* myGame = Singleton::getGame();

	if ((myGame->equalSign->coordinate.X - 1 == myGame->Hero->coordinate.X) && (myGame->equalSign->coordinate.Y == myGame->Hero->coordinate.Y) && myGame->isContainObject(myGame->equalSign->coordinate.Y, myGame->equalSign->coordinate.X + 1))
	{
		return -1; // Hero staying on left from equal sign.
	}
	else if ((myGame->equalSign->coordinate.X + 1 == myGame->Hero->coordinate.X) && (myGame->equalSign->coordinate.Y == myGame->Hero->coordinate.Y) && myGame->isContainObject(myGame->equalSign->coordinate.Y, myGame->equalSign->coordinate.X - 1))
	{
		return 1; // Hero staying on right from equal sign.
	}
	else return 0; // Nothing
}

bool _cdecl Comparser::retrieveNumbers_CS(char* str)
{
	int totalCountOfNumbers = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		if (isdigit(str[i]))
		{
			int j = i;
			int charptr = 0;
			while (1)
			{
				if (isdigit(str[j]))
				{
					j++;
					charptr++;
				}
				else
				{
					totalCountOfNumbers++;
					break;
				}
			}
			i += charptr;
		}
	}

	if (totalCountOfNumbers == 1)
	{
		char** numbers = new char* [totalCountOfNumbers];
		for (int i = 0; i < totalCountOfNumbers; i++)
		{
			numbers[i] = new char[32];
		}
		int strorder = 0;
		for (int i = 0; i < strlen(str); i++)
		{
			if (isdigit(str[i]))
			{
				int j = i;
				int charptr = 0;
				while (1)
				{
					if (isdigit(str[j]))
					{
						numbers[strorder][charptr] = str[j];
						j++;
						charptr++;
					}
					else
					{
						numbers[strorder][charptr] = '\0';
						strorder++;
						break;
					}
				}
				i += charptr;
			}
		}

		int strIndexOfFirstNumber = (this->strContain(numbers[0], str));

		if (str[(strIndexOfFirstNumber + strlen(numbers[0]))] != '=')
		{
			for (int i = 0; i < totalCountOfNumbers; i++)
			{
				delete[] numbers[i];
			}
			delete[] numbers;
			return false;
		}
		else
		{
			left = atoi(numbers[0]);

			for (int i = 0; i < totalCountOfNumbers; i++)
			{
				delete[]numbers[i];
			}
			delete[] numbers;
			return true;
		}
	}
	else return false;
}

bool _cdecl Comparser::retrieveNumbers_Math(char* str)
{
	int totalCountOfNumbers = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		if (isdigit(str[i]))
		{
			int j = i;
			int charptr = 0;
			while (1)
			{
				if (isdigit(str[j]))
				{
					j++;
					charptr++;
				}
				else
				{
					totalCountOfNumbers++;
					break;
				}
			}
			i += charptr;
		}
	}

	if (totalCountOfNumbers > 1)
	{
		char** numbers = new char* [totalCountOfNumbers];
		for (int i = 0; i < totalCountOfNumbers; i++)
		{
			numbers[i] = new char[32];
		}
		int strorder = 0;
		for (int i = 0; i < strlen(str); i++)
		{
			if (isdigit(str[i]))
			{
				int j = i;
				int charptr = 0;
				while (1)
				{
					if (isdigit(str[j]))
					{
						numbers[strorder][charptr] = str[j];
						j++;
						charptr++;
					}
					else
					{
						numbers[strorder][charptr] = '\0';
						strorder++;
						break;
					}
				}
				i += charptr;
			}
		}

		int strIndexOfFirstNumber = (this->strContain(numbers[0], str));
		int strIndexOfSecondNumber = (this->strContain(numbers[1], str + strIndexOfFirstNumber + strlen(numbers[0]))) + strIndexOfFirstNumber + strlen(numbers[0]);

		//if ( (this->strContain(numbers[0], str) + strlen(numbers[0]) != op) || (this->strContain(numbers[1], (str + strlen(numbers[0]) + (this->strContain(numbers[0], str)))) - 1 != op) || (str[this->strContain(numbers[1], str) + strlen(numbers[1])] != '=')	)
		if ((strIndexOfFirstNumber + strlen(numbers[0]) != op) || (strIndexOfSecondNumber - 1 != op) || (str[strIndexOfSecondNumber + strlen(numbers[1])] != '='))
		{
			for (int i = 0; i < totalCountOfNumbers; i++)
			{
				delete[]numbers[i];
			}
			delete[] numbers;
			return false;
		}
		else
		{
			op = str[op];
			left = atoi(numbers[0]);
			right = atoi(numbers[1]);

			for (int i = 0; i < totalCountOfNumbers; i++)
			{
				delete[]numbers[i];
			}
			delete[] numbers;
			return true;
		}
	}
	else return false;
}

//void Comparser::addObject(char c, int row, int column, bool _isMoveable)
//{
//	if (Game::getPointerField()->getField()[row][column] == ' ')
//	{
//		Object* obj = new Object(c, row, column, _isMoveable);
//		/*if (c == '=')
//		{
//
//		}*/
//		Singleton::getList()->push_back(obj);
//	}
//}

void Comparser::addResultObjects(Object* equalSign, int countOfColumns)
{
	int size = countOfColumns - equalSign->coordinate.X - 1;
	if (size < CountOfDigits(answer))
	{
		return;
	}
	else
	{
		bool clear = true;
		size = CountOfDigits(answer);
		char* mass = new char[size + 1];
		mass[size] = '\0';
		for (int i = size - 1; i >= 0; i--)
		{
			mass[i] = (answer % 10) + '0';
			answer /= 10;
		}

		for (int i = 1; i <= size; i++)
		{
			if (Singleton::getGame()->isContainObject(equalSign->coordinate.Y, equalSign->coordinate.X + i))
			{
				clear = false;
			}
		}
		if (clear)
		{
			for (int i = 0; i < size; i++)
			{
				Singleton::getGame()->addObject(mass[i], equalSign->coordinate.Y, equalSign->coordinate.X + 1 + i, true);
			}
		}


		delete[] mass;
	}
}