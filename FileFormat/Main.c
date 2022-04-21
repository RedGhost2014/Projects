#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include "Matrix.h"
#include "BinaryFunctions.h"
#include "strEx.h"

extern PNGfile* myFile = NULL;

void printBinaryFile(char* name)
{
	FILE* file;
	fopen_s(&file, name, "rb");
	int x = 0;
	BYTE c = NULL;
	do
	{
		if (feof(file))
			break;
		if (x % 8 == 0 && x != 0 && x % 16 != 0)
		{
			printf("  ");
		}
		if (x % 16 == 0 && x != 0)
		{
			printf("\n");
		}
		size_t i = fread_s(&c, 1, sizeof(BYTE), 1, file);
		if (i == 0)
			break;
		printf("%2x  ", c);
		x++;
	} while (!feof(file));
	fclose(file);
	printf("\n\n\n");
}

int pushAction()
{
	printf("Enter the string to push or 0 to cancel action: ");
	char* str = strGet_s(128);
	if (str[0] == '0' && strlen(str) == 1)
	{
		free(str);
		return 0;
	}
	size_t chunksIDsize = 0;
	int* chunksID = getAllStandartChunks(myFile->file, myFile->sizeoffile, &chunksIDsize);
	BYTE* tmpmass = insertStringToByte(str, myFile->file, &myFile->sizeoffile, chunksID[0]);
	free(chunksID);
	free(myFile->file);
	myFile->file = tmpmass;
	printf("\nYour string was insert to current file.\n\n");
	free(str);
	return 0;
}

int pushActionExtended()
{
	size_t chunksIDsize = 0;
	int* chunksID = getAllStandartChunks(myFile->file, myFile->sizeoffile, &chunksIDsize);
	for (int i = 0; i < chunksIDsize; i++)
	{
		char str[4 + 1] = { 0 };

		for (int j = 0; j < 4; j++)
		{
			str[j] = myFile->file[chunksID[i] + 4 + j];
		}
		printf("chunks[%d] on id %d = %s\n", i, chunksID[i], str);
	}
	printf("Print chunk id or \"Exit\" to cancel action: ");
	char* chunk = strGet_s(128);
	if (!_stricmp("Exit", chunk))
	{
		free(chunk);
		return 0;
	}
	int number = -1;
	if (strlen(chunk) == 1 && isdigit(chunk[0]))
	{
		number = atoi(chunk);
	}
	else
	{
		printf("\nException: Wrong command.\n\n");
		free(chunk);
		return 0;
	}
	printf("Enter the string or 0 to cancel action: ");
	char* str = strGet_s(128);
	if (str[0] == '0' && strlen(str) == 1)
	{
		free(chunk);
		free(str);
		return 0;
	}
	BYTE* tmpmass = insertStringToByte(str, myFile->file, &myFile->sizeoffile, chunksID[number]);
	free(myFile->file);
	myFile->file = tmpmass;
	printf("\nYour string was insert to current file.\n\n");
	free(str);
	free(chunksID);
	return 0;
}

int RawAction()
{
	size_t chunksIDsize = 0;
	int* chunksID = getAllStandartChunks(myFile->file, myFile->sizeoffile, &chunksIDsize);
	for (int i = 0; i < chunksIDsize; i++)
	{
		char str[4 + 1] = { 0 };

		for (int j = 0; j < 4; j++)
		{
			str[j] = myFile->file[chunksID[i] + 4 + j];
		}
		printf("chunks[%d] on id %d = %s\n", i, chunksID[i], str);
	}
	printf("Print chunk id or \"Exit\" to cancel action: ");
	char* chunk = strGet_s(128);
	if (!_stricmp("Exit", chunk))
	{
		free(chunksID);
		free(chunk);
		return 0;
	}
	int number = -1;
	if (strlen(chunk) == 1 && isdigit(chunk[0]))
	{
		number = atoi(chunk);
	}
	else
	{
		printf("\nException: Wrong command.\n\n");
		free(chunksID);
		free(chunk);
		return 0;
	}
	printf("Enter png name to insert in current file or \"Exit\" to cancel action: ");
	char* filename = strGet_s(128);
	if (!_stricmp("Exit", chunk))
	{
		free(chunksID);
		free(chunk);
		free(filename);
		return 0;
	}

	size_t pngsize = 0;
	BYTE* png = getBinaryFile(filename, &pngsize);
	
	BYTE* rawchunk = createChunk("Raw", png, &pngsize);
	BYTE* rightanswer = (BYTE*)malloc((myFile->sizeoffile + pngsize) * sizeof(BYTE));

	BYTE countofbytestogap[4] = { 0 };
	countofbytestogap[0] = myFile->file[chunksID[number]];
	countofbytestogap[1] = myFile->file[chunksID[number] + 1];
	countofbytestogap[2] = myFile->file[chunksID[number] + 2];
	countofbytestogap[3] = myFile->file[chunksID[number] + 3];

	int gap = byteMassToInt(countofbytestogap);
	gap += 4; // +countofbytestogap integer
	gap += 4; // +chunkname
	gap += 4; // +crc

	// Writing PNG type 
	int resultptr = 0;
	for (int i = 0; i < chunksID[number] + gap; i++)
	{
		rightanswer[resultptr] = myFile->file[i];
		resultptr++;
	}

	for (int i = 0; i < pngsize; i++)
	{
		rightanswer[resultptr] = rawchunk[i];
		resultptr++;
	}
	// Writing everything else
	for (int i = chunksID[number] + gap; i < myFile->sizeoffile; i++)
	{
		rightanswer[resultptr] = myFile->file[i];
		resultptr++;
	}
	free(myFile->file);
	free(rawchunk);
	myFile->file = rightanswer;
	myFile->sizeoffile = myFile->sizeoffile + pngsize;
	printf("%s was inserted in current file.\n", filename);
	free(chunksID);
	free(chunk);
	free(filename);
	return 0;
}

int deleteAction()
{
	size_t newSize = 0;
	BYTE* newFile = deleteAllChunks(myFile->file, myFile->sizeoffile, &newSize);
	free(myFile->file);
	myFile->sizeoffile = newSize;
	myFile->file = newFile;

	printf("\nAll hidden chunks was succesfully deleted.\n\n");

	return 0;
}

void RetrivePng()
{
	int id = getRawChunk(myFile->file, myFile->sizeoffile);

	if (id < 0)
	{
		printf("\nException: Your file does not contain any hidden images.\n\n");
		return;
	}

	BYTE countofbytestogap[4] = { 0 };
	countofbytestogap[0] = myFile->file[id];
	countofbytestogap[1] = myFile->file[id + 1];
	countofbytestogap[2] = myFile->file[id + 2];
	countofbytestogap[3] = myFile->file[id + 3];

	int countOfBytestoread = byteMassToInt(countofbytestogap);
	
	BYTE* rawpng = (BYTE*)malloc((countOfBytestoread - (4 + 3)) * sizeof(BYTE));

	for (int i = 0; i < (countOfBytestoread - (4 + 3)); i++)
	{
		rawpng[i] = myFile->file[i + id + 4 + 4 + 4 + 3];
	}

	printf("Enter file name to retrive hidden png: ");
	char* filename = strGet_s(50);
	FILE* file = NULL;
	fopen_s(&file, filename, "wb");
	fwrite(rawpng, sizeof(BYTE), (countOfBytestoread - (4 + 3)), file);
	fclose(file);
	printf("\nYour png was retrived.\n\n");
}

int pngAction()
{
	char* cmd = " ";
	while (cmd[0] != '0')
	{
		printf("Png action menu:\n\n");
		printf("0) Exit.\n1) Print standart chunks from png.\n2) Print all strings.\n3) Push string.\n4) Insert string after special chunk.\n5) Insert raw bytes (another png).\n6) Retrive hidden png from file.\n7) Delete all hidden info.\n8) Create new PNG file.\n");
		cmd = strGet_s(50);
		if (!_stricmp("cls", cmd))
		{
			system("cls");
		}
		else if (cmd[0] == '0' && strlen(cmd) == 1)
			break;
		else if (cmd[0] == '1' && strlen(cmd) == 1)
		{
			printf("\n\n");
			printAllStandartChunks(myFile->file, myFile->sizeoffile);
			printf("\n\n");
		}
		else if (cmd[0] == '2' && strlen(cmd) == 1)
		{
			size_t countofstrings = 0;
			char** strings = getStringsFromByte(myFile->file, myFile->sizeoffile, &countofstrings);
			if (strings == NULL)
			{
				printf("\nException: Strings not found.\n\n");
			}
			else
			{
				char** stringencrypted = (char**)malloc(countofstrings * sizeof(char*));
				for (int i = 0; i < countofstrings; i++)
				{
					stringencrypted[i] = VigenereCypherDecrypt(strings[i], "alDnString");
				}
				printf("\n\n");
				printf("Strings:\n");
				for (int i = 0; i < countofstrings; i++)
				{
					printf("Strings[%d] = %s\n", i, stringencrypted[i]);
				}
				printf("\n\n");
				for (int i = 0; i < countofstrings; i++)
				{
					free(strings[i]);
				}
				free(strings);
				for (int i = 0; i < countofstrings; i++)
				{
					free(stringencrypted[i]);
				}
				free(stringencrypted);
			}
		}
		else if (cmd[0] == '3' && strlen(cmd) == 1)
		{
			system("cls");
			pushAction();
		}
		else if (cmd[0] == '4' && strlen(cmd) == 1)
		{
			system("cls");
			pushActionExtended();
		}
		else if (cmd[0] == '5' && strlen(cmd) == 1)
		{
			system("cls");
			RawAction();
		}
		else if (cmd[0] == '6' && strlen(cmd) == 1)
		{
			system("cls");
			RetrivePng();
		}
		else if (cmd[0] == '7' && strlen(cmd) == 1)
		{
			system("cls");
			deleteAction();
		}
		else if (cmd[0] == '8' && strlen(cmd) == 1)
		{ 
			system("cls");
			printf("Enter file name to create a PNG: ");
			char* filename = strGet_s(50);
			FILE* file = NULL;
			fopen_s(&file, filename, "wb");
			fwrite(myFile->file, sizeof(BYTE), myFile->sizeoffile, file);
			fclose(file);
			printf("\nYour png was created.\n\n");
		}
		free(cmd);
	}
	return 0;
}


int main()
{
	myFile = (PNGfile*)malloc(sizeof(PNGfile));
	myFile->filename = NULL;
	myFile->wasconnection = false;
	myFile->file = NULL;
	myFile->sizeoffile = NULL;
	char* cmd = " ";
	while (cmd[0] != '0')
	{
		printf("Main menu:\n\n");
		printf("0) Exit.\n1) Connect to png file.\n2) Break the connection.\n3) Enter png actions mode.\n4) (DebugCommand) Print png in bytes.\n");
		cmd = strGet_s(50);
		if (!_stricmp("cls", cmd))
		{
			system("cls");
		}
		else if (cmd[0] == '0' && strlen(cmd) == 1)
			break;
		else if (cmd[0] == '1' && strlen(cmd) == 1)
		{
			if (myFile->wasconnection)
			{
				printf("\nException: File already connected.\n\n");
			}
			else
			{
				system("cls");
				printf("Enter file: ");

				char* filename = strGet_s(50);
				myFile->file = getBinaryFile(filename, &myFile->sizeoffile);
				if (myFile->file == NULL)
				{
					free(filename);
					printf("\nException: File cant be open. Wrong name?\n\n");
					continue;
				}
				else
				{
					myFile->filename = filename;
					printf("\nConnection to \"%s\" is set\n\n", myFile->filename);
					myFile->wasconnection = true;
				}
			}
		}
		else if (cmd[0] == '2' && strlen(cmd) == 1)
		{
			if (myFile->wasconnection)
			{
				printf("\nFile connection to \"%s\" was break.\n\n", myFile->filename);
				free(myFile->file);
				myFile->sizeoffile = NULL;
				myFile->wasconnection = false;
				free(myFile->filename);
				myFile->filename = NULL;
			}
			else printf("\nException: No file connect.\n\n");
		}
		else if (cmd[0] == '3' && strlen(cmd) == 1)
		{
			if (myFile->wasconnection)
			{
				system("cls");
				pngAction();
				system("cls");
			}
			else printf("\nException: No file connect.\n\n");
		}
		else if (cmd[0] == '4' && strlen(cmd) == 1)
		{
			printf("Enter filename: ");
			char* filename = strGet_s(50);
			printf("\n\n");
			printBinaryFile(filename);
			free(filename);
		}
		free(cmd);
	}
	if (cmd)
		free(cmd);
	if (myFile->file != NULL)
	{
		free(myFile->file);
	}
	if (myFile->filename != NULL)
	{
		free(myFile->filename);
	}
	return 0;
}