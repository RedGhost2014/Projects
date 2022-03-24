#include "BigInt.h"

void comparetest();

char* _cdecl strCopy(char* str)
{
	//char* strcopy = (char*)malloc((strlen(str) + 1) * sizeof(char));
	char* strcopy = new char[strlen(str) + 1];
	int i = 0;
	for (i = 0; i < strlen(str); i++)
	{
		strcopy[i] = str[i];
	}
	strcopy[i] = '\0';
	return strcopy;
}

char* _cdecl strGet()
{
	//char* dinamic = (char*)malloc(100 * sizeof(char));
	char* dinamic = new char[100];
	fgets(dinamic, 100, stdin);
	if (dinamic[(strlen(dinamic) - 1)] == '\n')
		dinamic[(strlen(dinamic) - 1)] = '\0';
	char* str = strCopy(dinamic);
	//free(dinamic);
	delete[] dinamic;
	/*if (dinamic[0] == '\0')
	{
		printf("\aERROR: Wrong Input.\n");
		printtime_pause();
		exit(1);
	}*/
	return str;
}

int main()
{
	setlocale(0, "Russian");
	//comparetest();

	/*cout << "First number: " << ends;
	char* charin1 = strGet();

	cout << "Second number: " << ends;
	char* charin2 = strGet();

	BigInteger Int1 = charin1;
	BigInteger Int2 = charin2;*/
	


	BigInteger Int1 = "-123456";
	BigInteger Int2 = "-132";

	BigInteger test = Int1 + Int2;
	test.printNumber();
	test = Int1 - Int2;
	test.printNumber();
	test = Int1 * Int2;
	test.printNumber();
	test = Int1 / Int2;
	test.printNumber();

	/*test = Int1 + Int2;
	test.printNumber();*/

	/*cout << "Answer: " << endl;
	Int2.printNumber();*/

	////Int2.printNumber();

	////BigInteger::swap(&Int1, &Int2);
	////Int1.printNumberMass();
	//Int1.printNumber();
	//Int2.printNumber();
}

void comparetest()
{
	BigInteger Int1 = "100";
	BigInteger Int2 = "1000";

	BigInteger Int3 = "-10";
	BigInteger Int4 = "-100";

	cout << "Int1 = " << Int1 << " > Int2 = " << Int2 << endl;
	if (Int1 > Int2)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int1 = " << Int1 << " < Int2 = " << Int2 << endl;
	if (Int1 < Int2)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << endl;

	cout << "Int1 = " << Int1 << " < Int3 = " << Int3 << endl;
	if (Int1 < Int3)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int1 = " << Int1 << " > Int3 = " << Int3 << endl;
	if (Int1 > Int3)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << endl;

	cout << "Int3 = " << Int3 << " > Int4 = " << Int4 << endl;
	if (Int3 > Int4)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int3 = " << Int3 << " < Int4 = " << Int4 << endl;
	if (Int3 < Int4)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << endl;

	cout << "Int4 = " << Int4 << " > Int3 = " << Int3 << endl;
	if (Int4 > Int3)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int4 = " << Int4 << " < Int3 = " << Int3 << endl;
	if (Int4 < Int3)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << endl;

	cout << "Int4 = " << Int4 << " > Int1 = " << Int1 << endl;
	if (Int4 > Int1)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int4 = " << Int4 << " < Int1 = " << Int1 << endl;
	if (Int4 < Int1)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << endl;

	BigInteger Int5 = "123";
	BigInteger Int6 = "123";
	BigInteger Int7 = "-123";
	BigInteger Int8 = "-123";

	cout << "Int5 = " << Int5 << " == Int6 = " << Int6 << endl;
	if (Int5 == Int6)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int5 = " << Int5 << " == Int7 = " << Int7 << endl;
	if (Int5 == Int7)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int7 = " << Int7 << " == Int5 = " << Int5 << endl;
	if (Int7 == Int5)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int7 = " << Int7 << " == Int8 = " << Int8 << endl;
	if (Int7 == Int8)
		cout << "true" << endl;
	else cout << "false" << endl;

	cout << "Int7 = " << Int7 << " == Int7 = " << Int7 << endl;
	if (Int7 == Int7)
		cout << "true" << endl;
	else cout << "false" << endl;
}