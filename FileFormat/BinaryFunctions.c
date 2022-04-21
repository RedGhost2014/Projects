#include "BinaryFunctions.h"
#include "Matrix.h"

BYTE* createChunk(const char* type, void* data, size_t* sizeofchunk)
{
	char* chunkName = "alDn";
	if (!strcmp("Matrix", type))
	{
		Matrix* mtrx = (Matrix*)data;
		int matrixData = (mtrx->rows * mtrx->columns) + 2;

		int alloc = ((matrixData + 1) * 4) + strlen(type) + strlen(chunkName);

		BYTE* chunkwithoutLenAndCRC = (BYTE*)malloc(alloc * sizeof(BYTE));

		int chunkptr = 0;
		for (int i = 0; i < 4; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = chunkName[i];
			chunkptr++;
		}
		BYTE* lenOfClass = intToByteMass(strlen(type));
		for (int i = 0; i < 4; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = lenOfClass[i];
			chunkptr++;
		}
		for (int i = 0; i < strlen(type); i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = type[i];
			chunkptr++;
		}
		size_t sizeofmatrixInBytes = 0;
		BYTE* matrixInBytes = matrixToBinary(mtrx, &sizeofmatrixInBytes);
		for (int i = 0; i < sizeofmatrixInBytes; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = matrixInBytes[i];
			chunkptr++;
		}

		chunkptr = 0;

		BYTE* finalchunk = createFullChunk(chunkwithoutLenAndCRC, alloc);
		*sizeofchunk = (alloc + 8);

		free(chunkwithoutLenAndCRC);
		free(lenOfClass);
		free(matrixInBytes);

		return finalchunk;

	}
	else if (!strcmp("String", type))
	{
		// *len* alDn 6 String Hello world (crc)
		// len(4) class(4) lenoftype(4) type(6) Albert(6)
		char* string = (char*)data;
		int stringData = strlen(string);

		int alloc = 4 + stringData + strlen(type) + strlen(chunkName);
		BYTE* chunkwithoutLenAndCRC = (BYTE*)malloc(alloc * sizeof(BYTE));
		int chunkptr = 0;
		for (int i = 0; i < 4; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = chunkName[i];
			chunkptr++;
		}
		BYTE* lenOfClass = intToByteMass(strlen(type));
		for (int i = 0; i < 4; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = lenOfClass[i];
			chunkptr++;
		}
		for (int i = 0; i < strlen(type); i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = type[i];
			chunkptr++;
		}
		BYTE* data = stringToByteMass(string);
		for (int i = 0; i < strlen(string); i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = data[i];
			chunkptr++;
		}
		BYTE* finalchunk = createFullChunk(chunkwithoutLenAndCRC, alloc);
		*sizeofchunk = (alloc + 8);
		free(chunkwithoutLenAndCRC);
		free(lenOfClass);

		return finalchunk;
	}
	else if (!strcmp("Raw", type))
	{
		BYTE* mass = (BYTE*)data;
		int alloc = 4 + strlen(type) + strlen(chunkName) + *sizeofchunk;
		BYTE* chunkwithoutLenAndCRC = (BYTE*)malloc(alloc * sizeof(BYTE));
		int chunkptr = 0;
		for (int i = 0; i < 4; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = chunkName[i];
			chunkptr++;
		}
		BYTE* lenOfClass = intToByteMass(strlen(type));
		for (int i = 0; i < 4; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = lenOfClass[i];
			chunkptr++;
		}
		for (int i = 0; i < strlen(type); i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = type[i];
			chunkptr++;
		}
		for (int i = 0; i < *sizeofchunk; i++)
		{
			chunkwithoutLenAndCRC[chunkptr] = mass[i];
			chunkptr++;
		}
		BYTE* finalchunk = createFullChunk(chunkwithoutLenAndCRC, alloc);
		*sizeofchunk = alloc + 8;
		free(chunkwithoutLenAndCRC);
		free(lenOfClass);

		return finalchunk;
	}
	else return 0;
}

BYTE* createFullChunk(BYTE* chunk, size_t sizeofchunk)
{
	size_t size = sizeofchunk;
	BYTE* mainlenofdata = intToByteMass(size - 4);
	uint32_t crcfortype = crc32(0, chunk, size);
	BYTE* crcfortypeByte = intToByteMass(crcfortype);

	BYTE* finalchunk = (BYTE*)malloc((size + 8) * sizeof(BYTE));
	int finalchunkptr = 0;
	for (int i = 0; i < 4; i++)
	{
		finalchunk[finalchunkptr] = mainlenofdata[i];
		finalchunkptr++;
	}
	for (int i = 0; i < size; i++)
	{
		finalchunk[finalchunkptr] = chunk[i];
		finalchunkptr++;
	}
	for (int i = 0; i < 4; i++)
	{
		finalchunk[finalchunkptr] = crcfortypeByte[i];
		finalchunkptr++;
	}

	/*for (int i = 0; i < size + 8; i++)
	{
		printf("%2x ", finalchunk[i]);
	}
	printf("\n\n");
	for (int i = 0; i < size + 8; i++)
	{
		printf("%c  ", finalchunk[i]);
	}*/
	free(crcfortypeByte);
	free(mainlenofdata);
	return finalchunk;
}

BYTE* matrixToBinary(Matrix* data, size_t* resultedsize)
{
	Matrix* mtrx = (Matrix*)data;
	size_t size = (mtrx->rows * mtrx->columns + 2) * sizeof(int);
	*resultedsize = size;
	BYTE* mass = (BYTE*)malloc(size * sizeof(BYTE));
	BYTE* rows = intToByteMass(mtrx->rows);
	BYTE* columns = intToByteMass(mtrx->columns);

	int massptr = 0;
	for (int i = 0; i < 4; i++)
	{
		mass[massptr] = rows[i];
		massptr++;
	}
	for (int i = 0; i < 4; i++)
	{
		mass[massptr] = columns[i];
		massptr++;
	}
	for (int i = 0; i < mtrx->rows; i++)
	{
		for (int j = 0; j < mtrx->columns; j++)
		{
			BYTE* intToWrite = intToByteMass(mtrx->matrix[i][j]);
			for (int counter = 0; counter < 4; counter++)
			{
				mass[massptr] = intToWrite[counter];
				massptr++;
			}
			free(intToWrite);
		}
	}
	free(rows);
	free(columns);
	return mass;
}

BYTE* intToByteMass(int a)
{
	BYTE* mass = (BYTE*)malloc(4 * sizeof(BYTE));

	for (int i = 3; i >= 0; i--)
	{
		mass[i] = a & 0xFF;
		a = a >> 8;
	}
	return mass;
}

int byteMassToInt(BYTE* mass)
{
	int answer = 0;

	for (int i = 0; i < 4; i++)
	{
		int tmp = mass[i] & 0xFF;
		answer = answer | tmp;
		if (i != 3)
			answer = answer << 8;
	}
	return answer;
}

char* byteMassToString(BYTE* mass, size_t len)
{
	char* str = (char*)malloc((len + 1) * sizeof(char));
	str[len] = '\0';
	for (int i = 0; i < len; i++)
	{
		str[i] = mass[i];
	}
	return str;
}

BYTE* stringToByteMass(char* str)
{
	BYTE* mass = (BYTE*)malloc(strlen(str) * sizeof(BYTE));
	mass[strlen(str)] = '\0';
	for (int i = 0; i < strlen(str); i++)
	{
		mass[i] = str[i];
	}
	return mass;
}


BYTE* getBinaryFile(const char* name, size_t* size)
{
	FILE* file = NULL;
	int err = fopen_s(&file, name, "rb");
	if (err)
		return 0;
	BYTE c = NULL;
	int x = 0;

	size_t countOfBytes = 0;

	while (!feof(file))
	{
		size_t i = fread_s(&c, 1, sizeof(char), 1, file);
		if (i == 0)
			break;
		countOfBytes++;
	}
	fclose(file);

	BYTE* mass = (BYTE*)malloc((countOfBytes + 1) * sizeof(BYTE));
	mass[countOfBytes] = '\0';
	fopen_s(&file, name, "rb");
	fread_s((BYTE*)mass, countOfBytes, sizeof(BYTE), countOfBytes, file);
	fclose(file);

	*size = countOfBytes;
	return mass;
}

int* findAllChunkByType(BYTE* file, size_t sizeoffile, char* classchunk, size_t* resultedsizeofchunks)
{
	BYTE check[4] = { 0 };
	int curreintposition = 0;
	int ptrtofindinsertplace = 0;
	for (int i = 0; i < sizeoffile - 4; i++)
	{
		check[0] = file[i];
		check[1] = file[i + 1];
		check[2] = file[i + 2];
		check[3] = file[i + 3];
		if (check[0] == classchunk[0] && check[1] == classchunk[1] && check[2] == classchunk[2] && check[3] == classchunk[3])
		{
			curreintposition++;
		}
	}
	if (curreintposition == 0)
		return 0;

	int* mass = (int*)malloc(curreintposition * sizeof(int));
	*resultedsizeofchunks = curreintposition;
	int massptr = 0;
	for (int i = 0; i < sizeoffile - 4; i++)
	{
		check[0] = file[i];
		check[1] = file[i + 1];
		check[2] = file[i + 2];
		check[3] = file[i + 3];
		if (check[0] == classchunk[0] && check[1] == classchunk[1] && check[2] == classchunk[2] && check[3] == classchunk[3])
		{
			ptrtofindinsertplace = i - 4;
			mass[massptr] = ptrtofindinsertplace;
			massptr++;
		}
	}
	return mass;
}

int findFirstChunkByType(BYTE* file, size_t sizeoffile, char* classchunk)
{
	BYTE check[4] = { 0 };
	int ptrtofindinsertplace = 0;
	for (int i = 0; i < sizeoffile - 4; i++)
	{
		check[0] = file[i];
		check[1] = file[i + 1];
		check[2] = file[i + 2];
		check[3] = file[i + 3];
		if (check[0] == classchunk[0] && check[1] == classchunk[1] && check[2] == classchunk[2] && check[3] == classchunk[3])
		{
			ptrtofindinsertplace = i - 4;
			return ptrtofindinsertplace;
		}
	}
	return -1;
}

int* getAllStandartChunks(BYTE* file, size_t sizeoffile, size_t* resultedsize)
{
	char* stantdartchunks[] = { "IHDR", "IEND", "IDAT", "PLTE", "bKGD", "cHRM", "gAMA", "hIST", "iCCP", "iTXt", "pHYs", "sBIT", "sPLT", "sRGB", "sTER", "tEXt", "tIME", "tRNS", "zTXt" };
	BYTE check[4] = { 0 };
	size_t count = 0;
	for (size_t i = 0; i < sizeoffile - 4; i++)
	{
		check[0] = file[i];
		check[1] = file[i + 1];
		check[2] = file[i + 2];
		check[3] = file[i + 3];
		for (int j = 0; j < 15; j++)
		{
			if (check[0] == stantdartchunks[j][0] && check[1] == stantdartchunks[j][1] && check[2] == stantdartchunks[j][2] && check[3] == stantdartchunks[j][3])
			{
				count++;
			}
		}
	}
	*resultedsize = count;
	int* mass = (int*)malloc(count * sizeof(int));
	int massptr = 0;
	for (size_t i = 0; i < sizeoffile - 4; i++)
	{
		check[0] = file[i];
		check[1] = file[i + 1];
		check[2] = file[i + 2];
		check[3] = file[i + 3];
		for (int j = 0; j < 15; j++)
		{
			if (check[0] == stantdartchunks[j][0] && check[1] == stantdartchunks[j][1] && check[2] == stantdartchunks[j][2] && check[3] == stantdartchunks[j][3])
			{
				mass[massptr] = i - 4;
				massptr++;
			}
		}
	}
	return mass;
}

void printAllStandartChunks(BYTE* file, size_t sizeoffile)
{
	printf("Standart chunks:\n");
	bool found = false;
	char* stantdartchunks[] = { "IHDR", "IEND", "IDAT", "PLTE", "bKGD", "cHRM", "gAMA", "hIST", "iCCP", "iTXt", "pHYs", "sBIT", "sPLT", "sRGB", "sTER", "tEXt", "tIME", "tRNS", "zTXt" };
	BYTE check[4] = { 0 };
	for (size_t i = 0; i < sizeoffile - 4; i++)
	{
		check[0] = file[i];
		check[1] = file[i + 1];
		check[2] = file[i + 2];
		check[3] = file[i + 3];
		for (int j = 0; j < 15; j++)
		{
			if (check[0] == stantdartchunks[j][0] && check[1] == stantdartchunks[j][1] && check[2] == stantdartchunks[j][2] && check[3] == stantdartchunks[j][3])
			{
				found = true;
				printf("%d) Chunk: %s\n", i - 4, stantdartchunks[j]);
			}
		}
	}
	if (!found)
	{
		printf("Standart chunks not found.\n");
	}
}

char** getStringsFromByte(BYTE* mass, size_t size, size_t* countOfStrings)
{
	size_t chunkcapacity = 0;
	int* startOfchunk = findAllChunkByType(mass, size, "alDn", &chunkcapacity);
	if (chunkcapacity == 0)
		return 0;
	*countOfStrings = chunkcapacity;
	char** strmass = (char**)malloc(chunkcapacity * sizeof(char*));

	for (int currentstring = 0; currentstring < chunkcapacity; currentstring++)
	{
		BYTE length[4] = { 0 };
		for (int i = 0; i < 4; i++)
		{
			length[i] = mass[startOfchunk[currentstring] + i];
		}
		int countOfBytes = byteMassToInt(length);

		char* str = (char*)malloc((countOfBytes - 10 + 1) * sizeof(char));
		str[countOfBytes - 10] = '\0';
		for (int i = 0; i < (countOfBytes - 10); i++)
		{
			str[i] = mass[startOfchunk[currentstring] + 18 + i];
		}
		strmass[currentstring] = str;
	}


	return strmass;
}

BYTE* insertStringToByte(const char* string, const BYTE* mass, size_t* size, int id)
{
	char* encrypt = VigenereCypher(string, "alDnString");

	size_t encryptByteSize = 0;
	BYTE* encryptByte = createChunk("String", encrypt, &encryptByteSize);

	BYTE* result = (BYTE*)malloc((*size + encryptByteSize + 1) * sizeof(BYTE));
	result[*size + encryptByteSize] = '\0';
	BYTE countofbytestogap[4] = { 0 };
	countofbytestogap[0] = mass[id];
	countofbytestogap[1] = mass[id + 1];
	countofbytestogap[2] = mass[id + 2];
	countofbytestogap[3] = mass[id + 3];

	int gap = byteMassToInt(countofbytestogap);
	gap += 4; // +countofbytestogap integer
	gap += 4; // +chunkname
	gap += 4; // +crc

	// Writing PNG type 
	int resultptr = 0;
	for (int i = 0; i < id + gap; i++)
	{
		result[resultptr] = mass[i];
		resultptr++;
	}

	// Writing insert string chunk
	for (int i = 0; i < encryptByteSize; i++)
	{
		result[resultptr] = encryptByte[i];
		resultptr++;
	}
	// Writing everything else
	for (int i = id + gap; i < *size; i++)
	{
		result[resultptr] = mass[i];
		resultptr++;
	}
	int tmpsize = (*size + encryptByteSize);
	*size = tmpsize;
	free(encryptByte);
	free(encrypt);
	return result;
}

int getRawChunk(BYTE* file, size_t sizeoffile)
{
	char* classchunk = "alDn";
	BYTE check[4] = { 0 };
	for (int i = 0; i < sizeoffile - 4; i++)
	{
		check[0] = file[i];
		check[1] = file[i + 1];
		check[2] = file[i + 2];
		check[3] = file[i + 3];
		if (check[0] == classchunk[0] && check[1] == classchunk[1] && check[2] == classchunk[2] && check[3] == classchunk[3])
		{
			BYTE lenbyte[4] = { 0 };
			lenbyte[0] = file[i + 4];
			lenbyte[1] = file[i + 5];
			lenbyte[2] = file[i + 6];
			lenbyte[3] = file[i + 7];
			size_t len = byteMassToInt(lenbyte);
			char* type = (char*)malloc((len + 1) * sizeof(char));
			type[len] = '\0';
			for (int j = 0; j < len; j++)
			{
				type[j] = file[i + 8 + j];
			}
			if (!strcmp("Raw", type))
			{
				free(type);
				return i - 4;
			}
			free(type);
		}
	}
	return -1;
}

BYTE* deleteAllChunks(BYTE* mass, size_t sizeofmass, size_t* resultedsize)
{
	BYTE* deletedmass = (BYTE*)malloc(sizeofmass * sizeof(BYTE));
	BYTE check[5] = { 0 };
	int ptr = 0;
	for (int i = 0; i < sizeofmass; i++)
	{
		check[0] = mass[i + 5];
		check[1] = mass[i + 6];
		check[2] = mass[i + 7];
		check[3] = mass[i + 8];
		check[4] = '\0';
		if (!strcmp("alDn", check))
		{
			BYTE lenbyte[4] = { 0 };
			lenbyte[0] = mass[i + 1];
			lenbyte[1] = mass[i + 2];
			lenbyte[2] = mass[i + 3];
			lenbyte[3] = mass[i + 4];
			int len = byteMassToInt(lenbyte);
			i += (len + 4 + 4 + 4); //bytes of crc + chunk + len herself
			i--; // step back
		}
		else
		{
			deletedmass[ptr] = mass[i];
			ptr++;
		}
	}
	BYTE* rightmass = (BYTE*)malloc(ptr * sizeof(BYTE));
	for (int i = 0; i < ptr; i++)
	{
		rightmass[i] = deletedmass[i];
	}
	free(deletedmass);
	*resultedsize = ptr;
	return rightmass;
}

static uint32_t crc32_tab[] =
{
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

uint32_t crc32(uint32_t crc, const void* buf, size_t size)
{
	const uint8_t* p;

	p = buf;
	crc = crc ^ ~0U;

	while (size--)
		crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

	return crc ^ ~0U;
}


char* _cdecl VigenereCypher(char* encodingStr, char* codename)
{
	char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\n\\<>()=[]*_\"&;{},	. '";

	char* encryptedstr = (char*)malloc((strlen(encodingStr) + 1) * sizeof(char));
	char* reapeatedCode = (char*)malloc((strlen(encodingStr) + 1) * sizeof(char));

	encryptedstr[strlen(encodingStr)] = '\0';
	reapeatedCode[strlen(encodingStr)] = '\0';

	int i, j;
	for (i = 0, j = 0; i < (strlen(encodingStr)); i++, j++)
	{
		if (j == (strlen(codename)))
		{
			j = 0;
		}
		reapeatedCode[i] = codename[j];
	}

	int symbols = 0;
	for (symbols = 0; symbols < strlen(encodingStr); symbols++)
	{
		int rows;
		int columns;
		bool flag = false;
		for (rows = 0; rows < strlen(alphabet); rows++)
		{
			flag = false;
			if (reapeatedCode[symbols] == alphabet[rows])
			{
				for (columns = 0; columns < strlen(alphabet); columns++)
				{
					if (encodingStr[symbols] == alphabet[columns])
					{
						flag = true;
						int x = ((columns + rows) % strlen(alphabet));
						encryptedstr[symbols] = alphabet[x];
					}
					if (flag)
						break;
				}
			}
			if (flag)
				break;
			else if (!flag)
			{
				encryptedstr[symbols] = encodingStr[symbols];
			}
		}
	}
	free(reapeatedCode);
	//encryptedstr[symbols] = '\0';
	return encryptedstr;
}

char* _cdecl VigenereCypherDecrypt(char* encryptedStr, char* codename)
{
	char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890\n\\<>()=[]*_\"&;{},	. '";

	char* encodingStr = (char*)malloc((strlen(encryptedStr) + 1) * sizeof(char));
	char* reapeatedCode = (char*)malloc((strlen(encryptedStr) + 1) * sizeof(char));
	encodingStr[strlen(encryptedStr)] = '\0';
	reapeatedCode[strlen(encryptedStr)] = '\0';

	int i, j;
	for (i = 0, j = 0; i < (strlen(encryptedStr)); i++, j++)
	{
		if (j == (strlen(codename)))
		{
			j = 0;
		}
		reapeatedCode[i] = codename[j];
	}
	int symbols = 0;
	for (symbols = 0; symbols < strlen(encryptedStr); symbols++)
	{
		int rows;
		int columns;
		bool flag = false;
		for (rows = 0; rows < strlen(alphabet); rows++)
		{
			flag = false;
			if (reapeatedCode[symbols] == alphabet[rows])
			{
				for (columns = 0; columns < strlen(alphabet); columns++)
				{
					if (encryptedStr[symbols] == alphabet[columns])
					{
						flag = true;
						int x = ((columns - rows + strlen(alphabet)) % strlen(alphabet));
						encodingStr[symbols] = alphabet[x];
					}
					if (flag)
						break;
				}
			}
			if (flag)
				break;
			else if (!flag)
			{
				encodingStr[symbols] = encryptedStr[symbols];
			}
		}
	}
	free(reapeatedCode);
	//encodingStr[symbols] = '\0';
	return encodingStr;
}