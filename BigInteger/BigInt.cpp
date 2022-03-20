#include "BigInt.h"

/* Base create functions */

BigInteger::BigInteger(const char* str)
{
#ifdef DEBUG
	cout << "Constructor called by " << this << ends;
#endif //!DEBUG

	charlen = strlen(str);

	charnumber = new char[charlen + 1];
	int i = 0;
	for (i = 0; i < charlen; i++)
	{
		charnumber[i] = str[i];
	}
	charnumber[i] = '\0';

	negative = false;
	countOfDigits = charlen;
	if (charnumber[0] == '-')
	{
		negative = true;
		countOfDigits--;
	}

	try
	{
		this->containOnlyDigits();
	}
	catch (const WrongInputException& e)
	{
		cerr << "Object at " << this << " from Class:BigInteger says: " << e.what() << endl;
		exit(1);
	}
	this->toMass();
#ifdef DEBUG
	cout << " and create \"";
	for (short i = 0; i < this->countOfDigits; i++)
	{
		cout << this->number[i].character;
	}
	cout << "\"" << endl;;
#endif //!DEBUG
}

BigInteger::BigInteger(const BigInteger& value)
{
#ifdef DEBUG
	cout << "Constructor called by " << this << ends;
#endif //!DEBUG
	this->charlen = value.charlen;
	this->countOfDigits = value.countOfDigits;

	this->negative = value.negative;
	this->charnumber = new char[this->charlen + 1];
	int i = 0;
	for (; i < charlen; i++)
	{
		this->charnumber[i] = value.charnumber[i];
	}
	this->charnumber[i] = '\0';

	i = 0;
	this->number = new Value[this->countOfDigits];
	for (i = 0; i < this->countOfDigits; i++)
	{
		this->number[i].character = value.number[i].character;
	}

#ifdef DEBUG
	cout << " and create \"";
	for (short i = 0; i < this->countOfDigits; i++)
	{
		cout << this->number[i].character;
	}
	cout << "\"" << endl;
#endif //!DEBUG
}

BigInteger::~BigInteger()
{
#ifdef DEBUG
	cout << "Destructor called by " << this << " and destroy \"";
	for (short i = 0; i < this->countOfDigits; i++)
	{
		cout << this->number[i].character;
	}
	cout << "\"" << endl;
#endif //!DEBUG
	delete[] this->number;
	delete[] this->charnumber;
}

/* Utility functions */

void BigInteger::containOnlyDigits()
{
	if (charnumber[0] == '\0')
	{
		throw WrongInputException("Exception: Value contain nothing.");
	}
	if (negative)
	{
		if (charnumber[1] == '0')
		{
			for (int i = 1; i < charlen; i++)
			{
				if (charnumber[i] != '0')
				{
					throw WrongInputException("Exception: Value starts with zero.");
				}
			}
		}
		for (int i = 1; i < charlen; i++)
		{
			if (!isdigit(charnumber[i]))
			{
				throw WrongInputException("Exception: Value contain not only digits.");
			}
		}
	}
	else if (!negative)
	{
		if (charnumber[0] == '0')
		{
			for (int i = 0; i < charlen; i++)
			{
				if (charnumber[i] != '0')
				{
					throw WrongInputException("Exception: Value starts with zero.");
				}
			}
		}
		for (int i = 0; i < charlen; i++)
		{
			if (!isdigit(charnumber[i]))
			{
				throw WrongInputException("Exception: Value contain not only digits.");
			}
		}
	}
}

int BigInteger::BItoi(const BigInteger& value)
{
	int bitoi = 0;
	int multiplier = 1;
	for (short i = value.countOfDigits - 1; i >= 0; i--)
	{
		bitoi = bitoi + (value.number[i].character * multiplier);
		multiplier *= 10;
	}
	return bitoi;
	//return atoi(value.charnumber);
}

void BigInteger::toMass()
{
	number = new Value[countOfDigits];
	if (negative)
	{
		for (int i = 0; i < countOfDigits; i++)
		{
			number[i].character = charnumber[i + 1] - '0';
		}
	}
	else if (!negative)
	{
		for (int i = 0; i < countOfDigits; i++)
		{
			number[i].character = charnumber[i] - '0';
		}
	}
}

void BigInteger::swap(BigInteger* left, BigInteger* right)
{
	BigInteger tmpleft = *left;
	BigInteger tmpright = *right;
	*right = tmpleft;
	*left = tmpright;
	//*left = *right;
	//*right = tmp;
}

void BigInteger::printNumber()
{
	if (negative)
	{
		cout << '-';
	}
	for (int i = 0; i < countOfDigits; i++)
	{
		cout << number[i].character;
	}
	cout << endl;
}

void BigInteger::printNumberMass()
{
	if (negative)
	{
		cout << '-';
	}
	for (int i = 0; i < countOfDigits; i++)
	{
		cout << number[i].character << " ";
	}
	cout << endl;
}

/* Operators */

void BigInteger::operator=(const BigInteger& value)
{
	this->charlen = value.charlen;
	this->countOfDigits = value.countOfDigits;

	this->negative = value.negative;

	delete[] this->charnumber;
	delete[] this->number;

	this->charnumber = new char[charlen + 1];
	int i = 0;
	for (i = 0; i < charlen; i++)
	{
		this->charnumber[i] = value.charnumber[i];
	}
	this->charnumber[i] = '\0';

	i = 0;
	this->number = new Value[countOfDigits];
	for (i = 0; i < countOfDigits; i++)
	{
		this->number[i].character = value.number[i].character;
	}
}

bool BigInteger::operator<(const BigInteger& value)
{
	// Если одно отрицательное, а второе положительное
	if (!this->negative && value.negative)
	{
		return false;
	}
	else if (this->negative && !value.negative)
	{
		return true;
	}

	// Если оба положительны
	if (!this->negative && !value.negative)
	{
		if (this->countOfDigits < value.countOfDigits)
		{
			return true;
		}
		else if (this->countOfDigits > value.countOfDigits)
		{
			return false;
		}
		else if (this->countOfDigits == value.countOfDigits)
		{
			for (int i = 0; i < this->countOfDigits; i++)
			{
				if (this->number[i].character < value.number[i].character)
				{
					return true;
				}
				else if (this->number[i].character > value.number[i].character)
				{
					return false;
				}
			}
			return false;
		}
	}
	// Если оба отрицательны
	else if (this->negative && value.negative)
	{
		if (this->countOfDigits > value.countOfDigits)
		{
			return true;
		}
		else if (this->countOfDigits < value.countOfDigits)
		{
			return false;
		}
		else if (this->countOfDigits == value.countOfDigits)
		{
			for (int i = 0; i < this->charlen; i++)
			{
				if (this->number[i].character > value.number[i].character)
				{
					return true;
				}
				else if (this->number[i].character > value.number[i].character)
				{
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

bool BigInteger::operator>(const BigInteger& value)
{
	// Если одно отрицательное, а второе положительное
	if (!this->negative && value.negative)
	{
		return true;
	}
	else if (this->negative && !value.negative)
	{
		return false;
	}
	
	// Если оба положительны
	if (!this->negative && !value.negative)
	{
		if (this->countOfDigits > value.countOfDigits)
		{
			return true;
		}
		else if (this->countOfDigits < value.countOfDigits)
		{
			return false;
		}
		else if (this->countOfDigits == value.countOfDigits)
		{
			for (int i = 0; i < this->countOfDigits; i++)
			{
				if (this->number[i].character > value.number[i].character)
				{
					return true;
				}
				else if (this->number[i].character < value.number[i].character)
				{
					return false;
				}
			}
			return false;
		}
	}
	// Если оба отрицательны
	else if (this->negative && value.negative)
	{
		if (this->countOfDigits > value.countOfDigits)
		{
			return false;
		}
		else if (this->countOfDigits < value.countOfDigits)
		{
			return true;
		}
		else if (this->countOfDigits == value.countOfDigits)
		{
			for (int i = 0; i < this->countOfDigits; i++)
			{
				if (this->number[i].character > value.number[i].character)
				{
					return false;
				}
				else if (this->number[i].character < value.number[i].character)
				{
					return true;
				}
			}
			return true;
		}
	}
	return false;
}

bool BigInteger::operator==(const BigInteger& value)
{
	if (!this->negative && value.negative)
	{
		return false;
	}
	else if (this->negative && !value.negative)
	{
		return false;
	}

	if (this->countOfDigits != value.countOfDigits)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->countOfDigits; i++)
		{
			if (this->number[i].character != value.number[i].character)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& out, const BigInteger& value)
{
	out << value.charnumber << ends;
	return out;
}

bool BigInteger::operator==(const char* str)
{
	BigInteger tmp = str;
	bool answer = (*this == tmp);
	return answer;
}

bool BigInteger::operator>(const char* str)
{
	BigInteger tmp = str;
	bool answer = (*this > tmp);
	return answer;
}

bool BigInteger::operator<(const char* str)
{
	BigInteger tmp = str;
	bool answer = (*this < tmp);
	return answer;
}

void BigInteger::operator=(const char* str)
{
	BigInteger* b = new BigInteger(str);
	
	delete[] this->charnumber;
	delete[] this->number;

	this->charlen = b->charlen;
	this->charnumber = b->charnumber;
	this->countOfDigits = b->countOfDigits;
	this->negative = b->negative;
	this->number = b->number;
}

BigInteger& operator+(BigInteger& left, BigInteger& right)
{
	BigInteger* b = new BigInteger(left);
	b->add(right);
	return *b;
}

BigInteger& operator-(BigInteger& left, BigInteger& right)
{
	BigInteger* b = new BigInteger(left);
	b->subtract(right);
	return *b;
}

BigInteger& operator*(BigInteger& left, BigInteger& right)
{
	BigInteger* b = new BigInteger(left);
	b->multiply(right);
	return *b;
}

BigInteger& operator/(BigInteger& left, BigInteger& right)
{
	BigInteger* b = new BigInteger(left);
	b->divide(right);
	return *b;
}

BigInteger& operator+(BigInteger& left, const char* str)
{
	BigInteger tmp = str;
	BigInteger* b = new BigInteger(left);
	b->add(tmp);
	return *b;
}

BigInteger& operator-(BigInteger& left, const char* str)
{
	BigInteger tmp = str;
	BigInteger* b = new BigInteger(left);
	b->subtract(tmp);
	return *b;
}

BigInteger& operator*(BigInteger& left, const char* str)
{
	BigInteger tmp = str;
	BigInteger* b = new BigInteger(left);
	b->multiply(tmp);
	return *b;
}

BigInteger& operator/(BigInteger& left, const char* str)
{
	BigInteger tmp = str;
	BigInteger* b = new BigInteger(left);
	b->divide(tmp);
	return *b;
}