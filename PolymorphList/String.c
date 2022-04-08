#include "String.h"

// Описанные "пользователем" функции

void clearString(void** elem)
{
	char* tmpstr = (char*)*elem;
	if (tmpstr != 0)
	{
		free(tmpstr);
		tmpstr = 0;
		*elem = 0;
	}
}

void printString(void** elem)
{
	char* tmpstr = (char*)*elem;
	if (elem == 0 || tmpstr == 0)
		printf("(null) ");
	else
		printf("%s ", tmpstr);
}

void* stringDuplicate(void* elem)
{
	char* nodestr = (char*)elem;
	char* str = (char*)malloc(strlen(nodestr) + 1 * sizeof(char));

	str[strlen(nodestr)] = '\0';

	for (int i = 0; i < strlen(nodestr); i++)
	{
		str[i] = nodestr[i];
	}
	return str;
}