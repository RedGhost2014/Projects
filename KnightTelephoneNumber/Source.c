#include <stdio.h>
#include <stdlib.h>

//int TelefonHorses(int Num, long long unsigned int count, int Numbers, int A) {
//	if (A >= Num) 
//	{
//		--Num;
//		return count;
//	}
//	if (A <= Num) 
//	{
//		if (Numbers == 1) {
//			count = TelefonHorses(Num, count + 1, 6, A + 1);
//			count = TelefonHorses(Num, count + 1, 8, A + 1);
//		}
//		if (Numbers == 2) {
//			count = TelefonHorses(Num, count + 1, 9, A + 1);
//			count = TelefonHorses(Num, count + 1, 7, A + 1);
//		}
//		if (Numbers == 3) {
//			count = TelefonHorses(Num, count + 1, 4, A + 1);
//			count = TelefonHorses(Num, count + 1, 8, A + 1);
//		}
//		if (Numbers == 4) {
//			count = TelefonHorses(Num, count + 1, 3, A + 1);
//			count = TelefonHorses(Num, count + 1, 9, A + 1);
//			count = TelefonHorses(Num, count + 1, 0, A + 1);
//		}
//		if (Numbers == 5) {
//			return count;
//		}
//		if (Numbers == 6) {
//			count = TelefonHorses(Num, count + 1, 1, A + 1);
//			count = TelefonHorses(Num, count + 1, 7, A + 1);
//			count = TelefonHorses(Num, count + 1, 0, A + 1);
//		}
//		if (Numbers == 7) {
//			count = TelefonHorses(Num, count + 1, 2, A + 1);
//			count = TelefonHorses(Num, count + 1, 6, A + 1);
//		}
//		if (Numbers == 9) {
//			count = TelefonHorses(Num, count + 1, 2, A + 1);
//			count = TelefonHorses(Num, count + 1, 4, A + 1);
//		}
//		if (Numbers == 0) {
//			if (count == 0) { return 0; }
//			else {
//				count = TelefonHorses(Num, count + 1, 4, A + 1);
//				count = TelefonHorses(Num, count + 1, 6, A + 1);
//			}
//		}
//		if (Numbers == 8) {
//			if (count == 0) { return 0; }
//			else {
//				count = TelefonHorses(Num, count + 1, 1, A + 1);
//				count = TelefonHorses(Num, count + 1, 3, A + 1);
//			}
//		}
//	}
//	else 
//	{
//		return count;
//	}
//	return count;
//}
//
//int main() {
//	long long unsigned int Num = 0, count = 0, countHorses = 0;
//	printf_s("Enter number.\n");
//	scanf_s("%d", &Num);
//	for (int i = 0; i <= 9; ++i) {
//		count = 0;
//		count = TelefonHorses(Num, count, i, 0);
//		countHorses += count;
//	}
//	printf_s("Dima method: %llu\n", countHorses);
//	int numbers = totalCountOfNumbers(Num);
//	printf("total numbers = %d\n", numbers);
//	system("pause");
//}

int KnightMoveto(int totalMovesRemaining, int currentdigit)
{
	int totalCountOfNumbers = 0;

	if (totalMovesRemaining == 0)
		return 0;
	if (currentdigit == 5)
		return 1;
	if (currentdigit == 0)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 6);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 4);
	}
	if (currentdigit == 1)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 6);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 8);
	}
	if (currentdigit == 2)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 7);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 9);
	}
	if (currentdigit == 3)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 4);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 8);
	}
	if (currentdigit == 4)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 3);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 9);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 0);
	}
	if (currentdigit == 6)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 1);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 7);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 0);
	}
	if (currentdigit == 7)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 2);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 6);
	}
	if (currentdigit == 8)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 1);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 3);
	}
	if (currentdigit == 9)
	{
		totalCountOfNumbers++;
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 2);
		totalCountOfNumbers += KnightMoveto(totalMovesRemaining - 1, 4);
	}
	return totalCountOfNumbers;
}

int totalCountOfNumbers(int n)
{
	int count = 0;
	//count += KnightMoveto(n, 0);
	count += KnightMoveto(n, 1);
	count += KnightMoveto(n, 2);
	count += KnightMoveto(n, 3);
	count += KnightMoveto(n, 4);
	count += KnightMoveto(n, 5);
	count += KnightMoveto(n, 6);
	count += KnightMoveto(n, 7);
	//count += KnightMoveto(n, 8);
	count += KnightMoveto(n, 9);
	return count;
}

int main()
{
	int n = 0;
	printf("Enter count of digits:\n");
	scanf_s("%d", &n);

	int numbers = totalCountOfNumbers(n);
	printf("total numbers = %d\n", numbers);

	//if ()
	//if ()

}