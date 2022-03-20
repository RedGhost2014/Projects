#ifndef _BIGINT
#define _BIGINT

//#define DEBUG

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <exception>

using namespace std;

class MsgException : public exception {
public:

	explicit MsgException(const char* what)
	{
		whatStr = (char*)what;
	}

	const char* what() const noexcept override
	{
		return whatStr;
	}

private:
	char* whatStr;
};

class WrongInputException : public MsgException
{
public:
	explicit WrongInputException(const char* what) : MsgException(what) { }
};

class BigInteger
{
public:
	BigInteger(const char* str);
	BigInteger() = delete;
	//BigInteger() {};
	BigInteger(const BigInteger& value);
	~BigInteger();

	void printNumber();
	void printNumberMass();

	// Math
	void add(BigInteger& value);
	void subtract(BigInteger& value);
	void multiply(BigInteger& value);
	void divide(BigInteger& value);
	friend BigInteger& abs(BigInteger& value);
	static int BItoi(const BigInteger& value);

	// Ops
	static void swap(BigInteger* left, BigInteger* right);

	void operator=(const BigInteger& value);
	bool operator<(const BigInteger& value);
	bool operator>(const BigInteger& value);
	bool operator==(const BigInteger& value);

	void operator=(const char* str);
	bool operator<(const char* str);
	bool operator>(const char* str);
	bool operator==(const char* str);

	friend BigInteger& operator+(BigInteger& left, BigInteger& right);
	friend BigInteger& operator-(BigInteger& left, BigInteger& right);
	friend BigInteger& operator*(BigInteger& left, BigInteger& right);
	friend BigInteger& operator/(BigInteger& left, BigInteger& right);

	friend BigInteger& operator+(BigInteger& left, const char* str);
	friend BigInteger& operator-(BigInteger& left, const char* str);
	friend BigInteger& operator*(BigInteger& left, const char* str);
	friend BigInteger& operator/(BigInteger& left, const char* str);

	friend std::ostream& operator<<(std::ostream& out, const BigInteger& value);

private:

	struct Value
	{
		short character : 6;
		//short character;
	};

	void containOnlyDigits() throw (WrongInputException);
	void toMass();

	char* charnumber;
	short charlen;	
	short countOfDigits;

	bool negative;
	Value* number;
};

#endif // !_BIGIN