#include <stdio.h>
#include <stdlib.h>
#include <strEx.h>
#include <Windows.h>

bool isMZFile(WORD h)
{
	return h == IMAGE_DOS_SIGNATURE;
}

int main(int argc, char* argv[])
{
	/*if (argc < 2)
	{
		printf("Not enough arg.\n");
		return 0;
	}*/

	//char* inputexe = argv[1];
	char* inputexe = "CALC";

	if (strContain(".exe", inputexe) < 0)
	{
		inputexe = strConcat(inputexe, ".exe", "");
	}

	FILE* inpufile = NULL;
	if (fopen_s(&inpufile, inputexe, "rb"))
	{
		printf("Canno open file.\n");
		fclose(inpufile);
		return 0;
	}

	IMAGE_DOS_HEADER dosHead = {0};
	signed short s = 0x79ff;

	fread_s(&dosHead, sizeof(dosHead), sizeof(char), 0x30, inpufile);

	if (!isMZFile(dosHead.e_magic))
	{
		printf("Not an executable file.\n");
		fclose(inpufile);
		return 0;
	}

	fclose(inpufile);
	return 0;
}