#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <stdint.h>
#include <stdbool.h>
#include "Matrix.h"

typedef struct PNGfile
{
	char* filename;
	BYTE* file;
	size_t sizeoffile;
	bool wasconnection;
} PNGfile;

PNGfile* myFile;

uint32_t crc32(uint32_t crc, const void* buf, size_t size);

BYTE* getBinaryFile(const char* name, size_t* size);
BYTE* matrixToBinary(Matrix* data, size_t* resultedsize);
BYTE* createChunk(const char* type, void* data, size_t* sizeofchunk);
BYTE* createFullChunk(BYTE* chunk, size_t sizeofchunk);
int* findAllChunkByType(BYTE* file, size_t sizeoffile, char* classchunk, size_t* resultedsizeofchunks);
int findFirstChunkByType(BYTE* file, size_t sizeoffile, char* classchunk);

BYTE* deleteAllChunks(BYTE* mass, size_t sizeofmass, size_t* resultedsize);
int* getAllStandartChunks(BYTE* file, size_t sizeoffile, size_t* resultedsize);
void printAllStandartChunks(BYTE* file, size_t sizeoffile);

BYTE* insertStringToByte(const char* string, const BYTE* mass, size_t* size, const char* chunkToInsertAfter);

char** getStringsFromByte(BYTE* mass, size_t size, size_t* countOfStrings);

int getRawChunk(BYTE* file, size_t sizeoffile);
BYTE* intToByteMass(int a);
int byteMassToInt(BYTE* mass);
char* byteMassToString(BYTE* mass, size_t len);
BYTE* stringToByteMass(char* str);

char* _cdecl VigenereCypher(char* encodingStr, char* codename);
char* _cdecl VigenereCypherDecrypt(char* encryptedStr, char* codename);