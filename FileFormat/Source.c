#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>
#include "Matrix.h"
#include "BinaryFunctions.h"

void printChunk(char* str)
{
	printf("%s = ", str);
	for (int i = 0; i < strlen(str); i++)
	{
		printf("%x ", str[i]);
	}
	printf("\n");
}

void getChunk(char a, char b, char c, char d)
{
	printf("%x %x %x %x = %c%c%c%c", a, b, c, d, a, b, c, d);
	printf("\n");
}

char* _cdecl strGetFile(char* filename)
{
	FILE* file = NULL;
	if (fopen_s(&file, filename, "r"))
		return NULL;
	char c = NULL;
	int count = 0;
	fseek(file, 0, 0);
	while (!feof(file))
	{
		c = fgetc(file);
		if (c == EOF)
		{
			count++;
			break;
		}
		count++;
	}
	char* str = (char*)malloc(count * sizeof(char));
	c = NULL;
	fseek(file, 0, 0);
	int i;
	for (i = 0; i < count; i++)
	{
		c = fgetc(file);
		str[i] = c;
	}
	str[i - 1] = '\0';
	fseek(file, 0, 0);
	fclose(file);
	return str;
}

int z()
{
	//size_t sizeoffile = 0;
	//BYTE* bytefile = getBinaryFile("test.png", &sizeoffile);
	//char* resultstr = getFisrtStringFromByte(bytefile, sizeoffile);
	//char* finalresult = VigenereCypherDecrypt(resultstr, "Albert");
	//printf("%s\n\n", finalresult);
	//free(resultstr);
	//free(finalresult);
	//free(bytefile);
	////free(chunk);
	//system("pause");
	//return 0;
}

int test()
{
	size_t ducksize = 0;
	BYTE* duck = getBinaryFile("testduck.png", &ducksize);
	//findFirstChunkByType(duck, sizeof);
	//printAllStandartChunks(duck, ducksize);
	return 0;
	//printChunk("sRGB");
	//printChunk("iCCP");
	//printBinaryFile("testduck.png");
	//return 0;
	char* albert = "Albert";
	char* denis = "Denis";
	char* albertdenis = "Albert and Denis";
	char* encodedstrings[3] = { 0 };

	encodedstrings[0] = albert;
	encodedstrings[1] = denis;
	encodedstrings[2] = albertdenis;
	for (int i = 0; i < 3; i++)
	{
		encodedstrings[i] = VigenereCypher(encodedstrings[i], "alDnString");
	}

	BYTE* chunkmass[3] = { 0 };
	size_t chunkmasssizes[3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		chunkmass[i] = createChunk("String", encodedstrings[i], &chunkmasssizes[i]);
	}

	size_t sizeofBaseFile = 0;
	BYTE* baseBytefile = getBinaryFile("testduck.png", &sizeofBaseFile);
	size_t sizeofmassindex = 0;
	int* massofIndex = findAllChunkByType(baseBytefile, sizeofBaseFile, "iCCP", &sizeofmassindex);

	FILE* file = NULL;
	fopen_s(&file, "teststringsduck.png", "wb");

	fwrite(baseBytefile, sizeof(BYTE), massofIndex[0], file);
	for (int i = 0; i < 3; i++)
	{
		fwrite(chunkmass[i], sizeof(BYTE), chunkmasssizes[i], file);
	}

	for (int i = massofIndex[0]; i < sizeofBaseFile; i++)
	{
		BYTE* c = baseBytefile + i * sizeof(BYTE);
		fwrite((BYTE*)c, sizeof(BYTE), 1, file);
	}
	fclose(file);
	free(baseBytefile);

	baseBytefile = getBinaryFile("teststringsduck.png", &sizeofBaseFile);
	size_t countOfStrings = 0;
	char** massofstrings = getStringsFromByte(baseBytefile, sizeofBaseFile, &countOfStrings);
	for (int i = 0; i < countOfStrings; i++)
	{
		printf("mass[%d] = %s\n", i, massofstrings[i]);
	}

	printf("\n\nAfter decrypt:\n\n");
	for (int i = 0; i < countOfStrings; i++)
	{
		printf("mass[%d] = %s\n", i, VigenereCypherDecrypt(massofstrings[i], "alDnString"));
	}
	system("pause");
	return 0;
}

int groupStringTest()
{
	char* albert = "Albert";
	char* denis = "Denis";
	char* albertdenis = "Albert and Denis";
	char* encodedstrings[3] = {0};

	encodedstrings[0] = albert;
	encodedstrings[1] = denis;
	encodedstrings[2] = albertdenis;
	for (int i = 0; i < 3; i++)
	{
		encodedstrings[i] = VigenereCypher(encodedstrings[i], "alDnString");
	}

	BYTE* chunkmass[3] = {0};
	size_t chunkmasssizes[3] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		chunkmass[i] = createChunk("String", encodedstrings[i], &chunkmasssizes[i]);
	}

	size_t sizeofBaseFile = 0;
	BYTE* baseBytefile = getBinaryFile("123.png", &sizeofBaseFile);
	size_t sizeofmassindex = 0;
	int* massofIndex = findAllChunkByType(baseBytefile, sizeofBaseFile, "sRGB", &sizeofmassindex);

	FILE* file = NULL;
	fopen_s(&file, "teststrings.png", "wb");

	fwrite(baseBytefile, sizeof(BYTE), massofIndex[0], file);
	for (int i = 0; i < 3; i++)
	{
		fwrite(chunkmass[i], sizeof(BYTE), chunkmasssizes[i], file);
	}

	for (int i = massofIndex[0]; i < sizeofBaseFile; i++)
	{
		BYTE* c = baseBytefile + i * sizeof(BYTE);
		fwrite((BYTE*)c, sizeof(BYTE), 1, file);
	}
	fclose(file);
	free(baseBytefile);

	baseBytefile = getBinaryFile("teststrings.png", &sizeofBaseFile);
	size_t countOfStrings = 0;
	char** massofstrings = getStringsFromByte(baseBytefile, sizeofBaseFile, &countOfStrings);
	for (int i = 0; i < countOfStrings; i++)
	{
		printf("mass[%d] = %s\n", i, massofstrings[i]);
	}

	printf("\n\nAfter decrypt:\n\n");
	for (int i = 0; i < countOfStrings; i++)
	{
		printf("mass[%d] = %s\n", i, VigenereCypherDecrypt(massofstrings[i], "alDnString"));
	}
	system("pause");
	return 0;
}