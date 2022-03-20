#include "BigInt.h"
#include <math.h>
//#include <cstdio>

BigInteger& abs(BigInteger& value)
{
	if (value.negative)
	{
		/*char* memstr = new char[value.charlen + 1];
		short i = 0;
		for (; i < value.charlen - 1; i++)
		{
			memstr[i] = value.charnumber[i + 1];
		}
		memstr[i] = '\0';*/

		BigInteger* tmp = new BigInteger(value);
		//delete[] memstr;
		tmp->negative = false;
		return *tmp;
	}
	else
	{
		/*char* memstr = new char[value.charlen + 1];
		short i = 0;
		for (; i < value.charlen; i++)
		{
			memstr[i] = value.charnumber[i];
		}
		memstr[i] = '\0';
		BigInteger* tmp = new BigInteger(memstr);
		delete[] memstr;
		return *tmp;*/
		BigInteger* tmp = new BigInteger(value);
		return *tmp;
	}
}

void BigInteger::add(BigInteger& value)
{
	// Если два числа равны
	if (*this == value)
	{
		for (short i = this->countOfDigits - 1; i >= 0; i--)
		{
			this->number[i].character += value.number[i].character;
		}

		for (short i = this->countOfDigits - 1; i >= 1; i--)
		{
			if (this->number[i].character >= 10)
			{
				this->number[i].character -= 10;
				this->number[i - 1].character += 1;
			}
		}
		if (this->number[0].character >= 10)
		{

			Value* clearmass = new Value[countOfDigits + 1];
			clearmass[0].character = 1;
			this->number[0].character -= 10;
			for (short i = 1; i < countOfDigits + 1; i++)
			{
				clearmass[i].character = this->number[i - 1].character;
			}
			delete[] this->number;
			this->number = clearmass;
			this->countOfDigits += 1;
		}
	}
	// Если они положительны
	else if (!this->negative && !value.negative)
	{
		if (*this < value)
		{
			Value* tmpmass = new Value[value.countOfDigits];
			for (short i = value.countOfDigits - 1, j = this->countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = this->number[j].character + value.number[i].character;
				}
				else
				{
					tmpmass[i].character = value.number[i].character;
				}
			}

			for (short i = value.countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character >= 10)
				{
					tmpmass[i].character -= 10;
					tmpmass[i - 1].character += 1;
				}
			}

			if (tmpmass[0].character >= 10)
			{
				Value* clearmass = new Value[value.countOfDigits + 1];
				clearmass[0].character = 1;
				tmpmass[0].character -= 10;
				for (short i = 1; i < countOfDigits + 1; i++)
				{
					clearmass[i].character = tmpmass[i - 1].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->number = clearmass;
				this->countOfDigits = value.countOfDigits + 1;
			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
				this->countOfDigits = value.countOfDigits;
			}
		}
		else if (*this > value)
		{
			Value* tmpmass = new Value[this->countOfDigits];
			for (short i = this->countOfDigits - 1, j = value.countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = this->number[i].character + value.number[j].character;
				}
				else
				{
					tmpmass[i].character = this->number[i].character;
				}
			}

			for (short i = this->countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character >= 10)
				{
					tmpmass[i].character -= 10;
					tmpmass[i - 1].character += 1;
				}
			}

			if (tmpmass[0].character >= 10)
			{
				Value* clearmass = new Value[this->countOfDigits + 1];
				clearmass[0].character = 1;
				tmpmass[0].character -= 10;
				for (short i = 1; i < this->countOfDigits + 1; i++)
				{
					clearmass[i].character = tmpmass[i - 1].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->number = clearmass;
				this->countOfDigits = this->countOfDigits + 1;
			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
			}
		}
		
	}
	// Если они отрицательны
	else if (this->negative && value.negative)
	{
		if (*this < value)
		{
			Value* tmpmass = new Value[this->countOfDigits];
			for (short i = this->countOfDigits - 1, j = value.countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = this->number[i].character + value.number[j].character;
				}
				else
				{
					tmpmass[i].character = this->number[i].character;
				}
			}

			for (short i = this->countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character >= 10)
				{
					tmpmass[i].character -= 10;
					tmpmass[i - 1].character += 1;
				}
			}

			if (tmpmass[0].character >= 10)
			{
				Value* clearmass = new Value[this->countOfDigits + 1];
				clearmass[0].character = 1;
				tmpmass[0].character -= 10;
				for (short i = 1; i < this->countOfDigits + 1; i++)
				{
					clearmass[i].character = tmpmass[i - 1].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->number = clearmass;
				this->countOfDigits = this->countOfDigits + 1;
			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
			}
		}
		else if (*this > value)
		{
			Value* tmpmass = new Value[value.countOfDigits];
			for (short i = value.countOfDigits - 1, j = this->countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = this->number[j].character + value.number[i].character;
				}
				else
				{
					tmpmass[i].character = value.number[i].character;
				}
			}

			for (short i = value.countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character >= 10)
				{
					tmpmass[i].character -= 10;
					tmpmass[i - 1].character += 1;
				}
			}

			if (tmpmass[0].character >= 10)
			{
				Value* clearmass = new Value[value.countOfDigits + 1];
				clearmass[0].character = 1;
				tmpmass[0].character -= 10;
				for (short i = 1; i < countOfDigits + 1; i++)
				{
					clearmass[i].character = tmpmass[i - 1].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->number = clearmass;
				this->countOfDigits = value.countOfDigits + 1;
			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
				this->countOfDigits = value.countOfDigits;
			}
		}
	}


	else if (!this->negative && value.negative)
	{
		if (this->countOfDigits > value.countOfDigits)
		{
			Value* tmpmass = new Value[this->countOfDigits];

			for (short i = this->countOfDigits - 1, j = value.countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = this->number[i].character - value.number[j].character;
				}
				else
				{
					tmpmass[i].character = this->number[i].character;
				}
			}

			for (short i = this->countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character < 0)
				{
					tmpmass[i].character += 10;
					tmpmass[i - 1].character -= 1;
				}
			}

			if (tmpmass[0].character <= 0)
			{
				short counter = 0;
				while (tmpmass[counter].character == 0 && counter < this->countOfDigits)
				{
					counter++;
				}

				Value* clearmass = new Value[this->countOfDigits - counter];

				for (short i = 0; i < this->countOfDigits - counter; i++)
				{
					clearmass[i].character = tmpmass[i + counter].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->number = clearmass;
				this->countOfDigits = this->countOfDigits - counter;
				
			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
			}
		}
		else if (this->countOfDigits < value.countOfDigits)
		{
			this->negative = true;
			BigInteger& tmpabs = abs(value);
			Value* tmpmass = new Value[tmpabs.countOfDigits];

			for (short i = tmpabs.countOfDigits - 1, j = this->countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = tmpabs.number[i].character - this->number[j].character;
				}
				else
				{
					tmpmass[i].character = tmpabs.number[i].character;
				}
			}

			for (short i = tmpabs.countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character < 0)
				{
					tmpmass[i].character += 10;
					tmpmass[i - 1].character -= 1;
				}
			}

			if (tmpmass[0].character <= 0)
			{
				short counter = 0;
				while (tmpmass[counter].character <= 0 && (counter < tmpabs.countOfDigits))
				{
					counter++;
				}

				Value* clearmass = new Value[tmpabs.countOfDigits - counter];

				for (short i = 0; i < tmpabs.countOfDigits - counter; i++)
				{
					clearmass[i].character = tmpmass[i + counter].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->countOfDigits = tmpabs.countOfDigits - counter;
				this->number = clearmass;
			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
				this->countOfDigits = tmpabs.countOfDigits;
			}
			delete& tmpabs;
		}
		else
		{
			BigInteger& tmpabs = abs(value);
			if (*this < tmpabs)
			{
				this->negative = true;
				//BigInteger& tmpabs = abs(value);
				Value* tmpmass = new Value[tmpabs.countOfDigits];

				for (short i = tmpabs.countOfDigits - 1, j = this->countOfDigits - 1; i >= 0; i--, j--)
				{
					if (j >= 0)
					{
						tmpmass[i].character = tmpabs.number[i].character - this->number[j].character;
					}
					else
					{
						tmpmass[i].character = tmpabs.number[i].character;
					}
				}

				for (short i = tmpabs.countOfDigits - 1; i >= 1; i--)
				{
					if (tmpmass[i].character < 0)
					{
						tmpmass[i].character += 10;
						tmpmass[i - 1].character -= 1;
					}
				}

				if (tmpmass[0].character <= 0)
				{
					short counter = 0;
					while (tmpmass[counter].character <= 0 && (counter < tmpabs.countOfDigits))
					{
						counter++;
					}

					Value* clearmass = new Value[tmpabs.countOfDigits - counter];

					for (short i = 0; i < tmpabs.countOfDigits - counter; i++)
					{
						clearmass[i].character = tmpmass[i + counter].character;
					}
					delete[] this->number;
					delete[] tmpmass;
					this->countOfDigits = tmpabs.countOfDigits - counter;
					this->number = clearmass;
				}
				else
				{
					delete[] this->number;
					this->number = tmpmass;
					this->countOfDigits = tmpabs.countOfDigits;
				}
			}
			else
			{
				Value* tmpmass = new Value[this->countOfDigits];

				for (short i = this->countOfDigits - 1, j = value.countOfDigits - 1; i >= 0; i--, j--)
				{
					if (j >= 0)
					{
						tmpmass[i].character = this->number[i].character - value.number[j].character;
					}
					else
					{
						tmpmass[i].character = this->number[i].character;
					}
				}

				for (short i = this->countOfDigits - 1; i >= 1; i--)
				{
					if (tmpmass[i].character < 0)
					{
						tmpmass[i].character += 10;
						tmpmass[i - 1].character -= 1;
					}
				}

				if (tmpmass[0].character <= 0)
				{
					short counter = 0;
					while (tmpmass[counter].character == 0 && counter < this->countOfDigits)
					{
						counter++;
					}

					Value* clearmass = new Value[this->countOfDigits - counter];

					for (short i = 0; i < this->countOfDigits - counter; i++)
					{
						clearmass[i].character = tmpmass[i + counter].character;
					}
					delete[] this->number;
					delete[] tmpmass;
					this->number = clearmass;
					this->countOfDigits = this->countOfDigits - counter;

				}
				else
				{
					delete[] this->number;
					this->number = tmpmass;
				}
			}
			delete &tmpabs;
		}
	}
	else if (this->negative && !value.negative)
	{
		if (this->countOfDigits > value.countOfDigits)
		{
			Value* tmpmass = new Value[this->countOfDigits];

			for (short i = this->countOfDigits - 1, j = value.countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = this->number[i].character - value.number[j].character;
				}
				else
				{
					tmpmass[i].character = this->number[i].character;
				}
			}

			for (short i = this->countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character < 0)
				{
					tmpmass[i].character += 10;
					tmpmass[i - 1].character -= 1;
				}
			}

			if (tmpmass[0].character <= 0)
			{
				short counter = 0;
				while (tmpmass[counter].character == 0 && counter < this->countOfDigits)
				{
					counter++;
				}

				Value* clearmass = new Value[this->countOfDigits - counter];

				for (short i = 0; i < this->countOfDigits - counter; i++)
				{
					clearmass[i].character = tmpmass[i + counter].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->number = clearmass;
				this->countOfDigits = this->countOfDigits - counter;

			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
			}
		}

		else if (this->countOfDigits < value.countOfDigits)
		{
			this->negative = false;
			BigInteger& tmpabs = abs(*this);
			Value* tmpmass = new Value[value.countOfDigits];

			for (short i = value.countOfDigits - 1, j = tmpabs.countOfDigits - 1; i >= 0; i--, j--)
			{
				if (j >= 0)
				{
					tmpmass[i].character = value.number[i].character - tmpabs.number[j].character;
				}
				else
				{
					tmpmass[i].character = value.number[i].character;
				}
			}

			for (short i = value.countOfDigits - 1; i >= 1; i--)
			{
				if (tmpmass[i].character < 0)
				{
					tmpmass[i].character += 10;
					tmpmass[i - 1].character -= 1;
				}
			}

			if (tmpmass[0].character <= 0)
			{
				short counter = 0;
				while (tmpmass[counter].character <= 0 && (counter < value.countOfDigits))
				{
					counter++;
				}

				Value* clearmass = new Value[value.countOfDigits - counter];

				for (short i = 0; i < value.countOfDigits - counter; i++)
				{
					clearmass[i].character = tmpmass[i + counter].character;
				}
				delete[] this->number;
				delete[] tmpmass;
				this->countOfDigits = value.countOfDigits - counter;
				this->number = clearmass;
			}
			else
			{
				delete[] this->number;
				this->number = tmpmass;
				this->countOfDigits = value.countOfDigits;
			}
			delete& tmpabs;
		}
		else
		{
			BigInteger& tmpabs = abs(*this);
			if (value < tmpabs)
			{
				this->negative = true;
				Value* tmpmass = new Value[tmpabs.countOfDigits];

				for (short i = tmpabs.countOfDigits - 1, j = value.countOfDigits - 1; i >= 0; i--, j--)
				{
					if (j >= 0)
					{
						tmpmass[i].character = tmpabs.number[i].character - value.number[j].character;
					}
					else
					{
						tmpmass[i].character = tmpabs.number[i].character;
					}
				}

				for (short i = tmpabs.countOfDigits - 1; i >= 1; i--)
				{
					if (tmpmass[i].character < 0)
					{
						tmpmass[i].character += 10;
						tmpmass[i - 1].character -= 1;
					}
				}

				if (tmpmass[0].character <= 0)
				{
					short counter = 0;
					while (tmpmass[counter].character <= 0 && (counter < tmpabs.countOfDigits))
					{
						counter++;
					}

					Value* clearmass = new Value[tmpabs.countOfDigits - counter];

					for (short i = 0; i < tmpabs.countOfDigits - counter; i++)
					{
						clearmass[i].character = tmpmass[i + counter].character;
					}
					delete[] this->number;
					delete[] tmpmass;
					this->countOfDigits = tmpabs.countOfDigits - counter;
					this->number = clearmass;
				}
				else
				{
					delete[] this->number;
					this->number = tmpmass;
					this->countOfDigits = tmpabs.countOfDigits;
				}
			}
			else
			{
				this->negative = false;
				Value* tmpmass = new Value[this->countOfDigits];

				for (short i = value.countOfDigits - 1, j = tmpabs.countOfDigits - 1; i >= 0; i--, j--)
				{
					if (j >= 0)
					{
						tmpmass[i].character = value.number[i].character - tmpabs.number[j].character;
					}
					else
					{
						tmpmass[i].character = value.number[i].character;
					}
				}

				for (short i = this->countOfDigits - 1; i >= 1; i--)
				{
					if (tmpmass[i].character < 0)
					{
						tmpmass[i].character += 10;
						tmpmass[i - 1].character -= 1;
					}
				}

				if (tmpmass[0].character <= 0)
				{
					short counter = 0;
					while (tmpmass[counter].character == 0 && counter < this->countOfDigits)
					{
						counter++;
					}

					Value* clearmass = new Value[this->countOfDigits - counter];

					for (short i = 0; i < this->countOfDigits - counter; i++)
					{
						clearmass[i].character = tmpmass[i + counter].character;
					}
					delete[] this->number;
					delete[] tmpmass;
					this->number = clearmass;
					this->countOfDigits = this->countOfDigits - counter;

				}
				else
				{
					delete[] this->number;
					this->number = tmpmass;
				}
			}
			delete& tmpabs;
		}
	}
}

void BigInteger::subtract(BigInteger& value)
{
	BigInteger* a = 0;
	BigInteger* b = 0;

	if ((!this->negative && !value.negative))
	{
		a = new BigInteger(abs(*this));
		b = new BigInteger(abs(value));

		if (*a > *b)
		{
			b->negative = true;
			a->add(*b);

			delete[] this->charnumber;
			delete[] this->number;

			this->charlen = a->charlen;
			this->charnumber = a->charnumber;
			this->countOfDigits = a->countOfDigits;
			this->negative = false;
			this->number = a->number;
			delete b;
		}
		else
		{
			a->negative = true;
			b->add(*a);

			delete[] this->charnumber;
			delete[] this->number;

			this->charlen = b->charlen;
			this->charnumber = b->charnumber;
			this->countOfDigits = b->countOfDigits;
			this->negative = true;
			this->number = b->number;
			delete a;
		}
	}
	else if (this->negative && value.negative)
	{
		a = new BigInteger(abs(*this));
		b = new BigInteger(abs(value));

		if (*b > *a)
		{
			a->negative = true;
			b->add(*a);

			delete[] this->charnumber;
			delete[] this->number;

			this->charlen = b->charlen;
			this->charnumber = b->charnumber;
			this->countOfDigits = b->countOfDigits;
			this->negative = false;
			this->number = b->number;
			delete a;
		}
		else
		{
			b->negative = true;
			a->add(*b);

			delete[] this->charnumber;
			delete[] this->number;

			this->charlen = a->charlen;
			this->charnumber = a->charnumber;
			this->countOfDigits = a->countOfDigits;
			this->negative = true;
			this->number = a->number;
			delete b;
		}
	}
	else
	{
		if (*this > value)
		{
			a = new BigInteger(abs(*this));
			b = new BigInteger(abs(value));
			a->add(*b);

			delete[] this->charnumber;
			delete[] this->number;

			this->charlen = a->charlen;
			this->charnumber = a->charnumber;
			this->countOfDigits = a->countOfDigits;
			this->negative = a->negative;
			this->number = a->number;
			delete b;
		}
		else
		{
			a = new BigInteger(abs(*this));
			b = new BigInteger(abs(value));
			a->add(*b);
			a->negative = true;


			delete[] this->charnumber;
			delete[] this->number;

			this->charlen = a->charlen;
			this->charnumber = a->charnumber;
			this->countOfDigits = a->countOfDigits;
			this->negative = a->negative;
			this->number = a->number;
			delete b;
		}
	}
}

void BigInteger::multiply(BigInteger& value)
{
	BigInteger* thisabs = new BigInteger(abs(*this));
	BigInteger* valueabs = new BigInteger(abs(value));
	BigInteger* addvalue = 0;

	if (*thisabs < *valueabs)
	{
		addvalue = new BigInteger(*valueabs);
		int counter = BItoi(*thisabs);
		for (int i = 0; i < counter - 1; i++)
		{
			valueabs->add(*addvalue);
		}

		delete[] this->charnumber;
		delete[] this->number;

		if ((this->negative && value.negative) || (!this->negative && !value.negative))
		{
			this->negative = false;
		}
		else
		{
			this->negative = true;
		}

		this->charlen = valueabs->charlen;
		this->charnumber = valueabs->charnumber;
		this->countOfDigits = valueabs->countOfDigits;
		this->number = valueabs->number;
		delete addvalue;
		delete thisabs;
	}
	else
	{
		addvalue = new BigInteger(*thisabs);
		int counter = BItoi(*valueabs);
		for (int i = 0; i < counter - 1; i++)
		{
			thisabs->add(*addvalue);
		}

		delete[] this->charnumber;
		delete[] this->number;

		if ((this->negative && value.negative) || (!this->negative && !value.negative))
		{
			this->negative = false;
		}
		else
		{
			this->negative = true;
		}

		this->charlen = thisabs->charlen;
		this->charnumber = thisabs->charnumber;
		this->countOfDigits = thisabs->countOfDigits;
		this->number = thisabs->number;
		delete addvalue;
		delete valueabs;
	}
}

void BigInteger::divide(BigInteger& value)
{
	BigInteger* thisabs = new BigInteger(abs(*this));
	BigInteger* valueabs = new BigInteger(abs(value));
	BigInteger* answer = 0;

	if ((*this < value && !this->negative) || (*this > value && this->negative))
	{
		answer = new BigInteger("0");

		delete[] this->charnumber;
		delete[] this->number;

		this->charlen = answer->charlen;
		this->charnumber = answer->charnumber;
		this->countOfDigits = answer->countOfDigits;
		this->number = answer->number;
		delete valueabs;
		delete thisabs;
		return;
	}
	else
	{
		BigInteger subtractValue = abs(value);

		answer = new BigInteger("0");
		BigInteger* one = new BigInteger("1");

		BigInteger left = *thisabs;

		while (left > subtractValue || left == subtractValue)
		{
			BigInteger tmp = left - subtractValue;
			left = tmp;
			answer->add(*one);
		}
		

		if ((this->negative && value.negative) || (!this->negative && !value.negative))
		{
			this->negative = false;
		}
		else
		{
			this->negative = true;
		}

		delete[] this->charnumber;
		delete[] this->number;

		this->charlen = answer->charlen;
		this->charnumber = answer->charnumber;
		this->countOfDigits = answer->countOfDigits;
		this->number = answer->number;

		delete thisabs;
		delete one;
		delete valueabs;
	}
}