#include "STREX.h"

static int _cdecl compareAtoZ(void* context, const void* str1, const void* str2);
static int _cdecl compareZtoA(void* context, const void* str1, const void* str2);
static int _cdecl compareLenIncrease(const void* str1, const void* str2);
static int _cdecl compareLenDecrease(const void* str1, const void* str2);

#ifdef __cplusplus

strEx::MsgException::MsgException(const char* what)
{
	whatStr = (char*)what;
}

const char* strEx::MsgException::what() const noexcept
{
	return whatStr;
}


char* _cdecl strEx::StringExtended::strCopy(_In_z_ const char* strsrc)
{
	if (strsrc == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	char* strcopy = STREX_ALLOC(char, (strlen(strsrc) + 1));
	
	short counterOfAllocateAttempt = 0;

	while (!strcopy)
	{
		strcopy = STREX_ALLOC(char, (strlen(strsrc) + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	strcopy[strlen(strsrc)] = '\0';

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		strcopy[i] = strsrc[i];
	}
	return strcopy;
}

char* _cdecl strEx::StringExtended::strGet(void)
{
	char* dynamic = STREX_ALLOC(char, (STREX_BASE_ALLOC + 1));

	short counterOfAllocateAttempt = 0;

	while (!dynamic)
	{
		dynamic = STREX_ALLOC(char, (STREX_BASE_ALLOC + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	fgets(dynamic, STREX_BASE_ALLOC + 1, stdin);

	if (dynamic[(strlen(dynamic)) - 1] == '\n')
		dynamic[(strlen(dynamic)) - 1] = '\0';

	char* str = strEx::StringExtended::strCopy(dynamic);

	delete[] dynamic;
	return str;
}

char* _cdecl strEx::StringExtended::strGet_s(_In_ size_t allocatedMemory)
{
	if (allocatedMemory == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
		
	char* dynamic = STREX_ALLOC(char, (allocatedMemory + 1));

	short counterOfAllocateAttempt = 0;

	while (!dynamic)
	{
		dynamic = STREX_ALLOC(char, (allocatedMemory + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	fgets(dynamic, allocatedMemory + 1, stdin);

	if (dynamic[(strlen(dynamic)) - 1] == '\n')
		dynamic[(strlen(dynamic)) - 1] = '\0';

	char* str = strCopy(dynamic);

	delete[] dynamic;
	return str;
}

char* _cdecl strEx::StringExtended::strConcat(_In_z_ const char* firstStr, ...)
{
	if (firstStr == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(firstStr) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	int mainlen = strlen(firstStr);

	va_list argptr;
	va_start(argptr, firstStr);

	char* tmpstr = (char*)" ";
	while (tmpstr[0] != '\0')
	{
		tmpstr = va_arg(argptr, char*);
		if (tmpstr == 0)
		{
			STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
		}
		mainlen += strlen(tmpstr);
	}
	va_end(argptr);

	char* returnedStr = STREX_ALLOC(char, (mainlen + 1));
	returnedStr[mainlen] = '\0';
	if (!returnedStr)
	{
		STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
	}

	int currentCharPointer = 0;
	for (size_t i = 0; i < strlen(firstStr); i++)
	{
		returnedStr[currentCharPointer] = firstStr[i];
		currentCharPointer++;
	}

	va_start(argptr, firstStr);
	tmpstr = (char*)" ";

	while (tmpstr[0] != '\0')
	{
		tmpstr = va_arg(argptr, char*);
		for (size_t i = 0; i < strlen(tmpstr); i++)
		{
			returnedStr[currentCharPointer] = tmpstr[i];
			currentCharPointer++;
		}
	}

	return returnedStr;
}

int _cdecl strEx::StringExtended::strContain(_In_z_ const char* strToFind, _In_z_ const char* strsrc)
{
	if (strToFind == 0 || strsrc == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strToFind) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	size_t strlenOfToFind = strlen(strToFind);
	size_t strlenOfBaseStr = strlen(strsrc);

	size_t count = 0;
	int flag = -1;
	for (size_t i = 0; i < strlenOfBaseStr; i++)
	{
		if (strToFind[0] == strsrc[i])
		{
			flag = i;
			size_t z = i;
			for (size_t j = 0; j < strlenOfToFind; j++, z++)
			{
				if (strToFind[j] == strsrc[z])
				{
					count++;
					if (count == strlenOfToFind)
					{
						return flag;
					}
				}
				else
				{
					flag = -1;
					count = 0;
					break;
				}
			}
		}
	}
	return flag;
}

char* _cdecl strEx::StringExtended::strErase(_In_z_ const char* whatStr, _In_z_ const char* strsrc)
{
	if (whatStr == 0 || strsrc == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(whatStr) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int positionOfWhatStr = strEx::StringExtended::strContain(whatStr, strsrc);
	if (positionOfWhatStr >= 0)
	{
		int size = strlen(strsrc) - strlen(whatStr);

		if (size <= 0)
		{
			STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}

		char* result = STREX_ALLOC(char, (size + 1));

		short counterOfAllocateAttempt = 0;

		while (!result)
		{
			result = STREX_ALLOC(char, (size + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}

		result[size] = '\0';

		for (size_t i = 0, j = 0; j < size && i < strlen(strsrc); i++, j++)
		{
			if (i == positionOfWhatStr)
			{
				i += strlen(whatStr);
			}
			result[j] = strsrc[i];
		}

		return result;
	}
	else
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
}

char* _cdecl strEx::StringExtended::strEraseInRange(_In_z_ const char* leftBorder, _In_z_ const char* rightBorder, _In_z_ const char* strsrc)
{
	if (leftBorder == 0 || rightBorder == 0|| strsrc == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(leftBorder) == 0 || strlen(rightBorder) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int positionOfLeftBorder = strEx::StringExtended::strContain(leftBorder, strsrc);
	int positionOfRightBorder = strEx::StringExtended::strContain(rightBorder, strsrc);
	if (positionOfLeftBorder >= 0 && positionOfRightBorder >= 0)
	{
		positionOfLeftBorder += strlen(leftBorder);

		size_t size = strlen(strsrc) - (positionOfRightBorder - positionOfLeftBorder);

		if (size <= 0)
		{
			STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}

		char* result = STREX_ALLOC(char, (size + 1));

		short counterOfAllocateAttempt = 0;

		while (!result)
		{
			result = STREX_ALLOC(char, (size + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}
		result[size] = '\0';

		for (size_t i = 0, j = 0; j < size && i < strlen(strsrc); i++)
		{
			if ((i < positionOfLeftBorder || i >= positionOfRightBorder))
			{
				result[j] = strsrc[i];
				j++;
			}
		}

		return result;
	}
	else
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
}

char* _cdecl strEx::StringExtended::strCutInRange(_In_z_ const char* leftBorder, _In_z_ const char* rightBorder, _In_z_ const char* strsrc)
{
	if (leftBorder == 0 || rightBorder == 0 || strsrc == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(leftBorder) == 0 || strlen(rightBorder) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int positionOfLeftBorder = strEx::StringExtended::strContain(leftBorder, strsrc);
	int positionOfRightBorder = strEx::StringExtended::strContain(rightBorder, strsrc);
	if (positionOfLeftBorder >= 0 && positionOfRightBorder >= 0)
	{
		positionOfLeftBorder += strlen(leftBorder);

		size_t size = (positionOfRightBorder - positionOfLeftBorder);

		if (positionOfLeftBorder >= positionOfRightBorder)
		{
			STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}

		char* result = STREX_ALLOC(char, (size + 1));

		short counterOfAllocateAttempt = 0;

		while (!result)
		{
			result = STREX_ALLOC(char, (size + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}

		result[size] = '\0';

		for (size_t i = 0, j = 0; j < size && i < strlen(strsrc); i++)
		{
			if ((i >= positionOfLeftBorder && i < positionOfRightBorder))
			{
				result[j] = strsrc[i];
				j++;
			}
		}

		return result;
	}
	else
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
}

void _cdecl strEx::StringExtended::strSort_AtoZ(_Inout_ const char** arraysrc, _In_ size_t size, _In_ bool case_sensetive)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}
	qsort_s(arraysrc, size, sizeof(char*), compareAtoZ, (void*)case_sensetive);
}

void _cdecl strEx::StringExtended::strSort_ZtoA(_Inout_ const char** arraysrc, _In_ size_t size, _In_ bool case_sensetive)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}

	qsort_s(arraysrc, size, sizeof(char*), compareZtoA, (void*)case_sensetive);
}

void _cdecl strEx::StringExtended::strSort_LenIncrease(_Inout_ const char** arraysrc, _In_ size_t size)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}
	qsort(arraysrc, size, sizeof(char*), compareLenIncrease);
}

void _cdecl strEx::StringExtended::strSort_LenDecrease(_Inout_ const char** arraysrc, _In_ size_t size)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}
	qsort(arraysrc, size, sizeof(char*), compareLenDecrease);
}

size_t strEx::StringExtended::strContainCount(_In_ const char* strToFind, _In_ const char* strsrc)
{
	if (strsrc == 0 || strToFind == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strToFind) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	size_t strlenOfToFind = strlen(strToFind);
	size_t strlenOfBaseStr = strlen(strsrc);
	size_t countOfRepeats = 0;
	int count = 0;
	for (int i = 0; i < strlenOfBaseStr; i++)
	{
		count = 0;
		if (strToFind[0] == strsrc[i])
		{
			int z = i;
			for (int j = 0; j < strlenOfToFind; j++, z++)
			{
				if (strToFind[j] == strsrc[z])
				{
					count++;
					if (count == strlenOfToFind)
					{
						countOfRepeats++;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	return countOfRepeats;
}

char** _cdecl strEx::StringExtended::strSplitByParser(_In_z_ const char* strsrc, _In_z_ const char* splittingStr, _Out_ size_t* stringsCount)
{
	if (strsrc == 0 || splittingStr == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0 || strlen(splittingStr) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	size_t countOfSubstring = StringExtended::strContainCount(splittingStr, strsrc);

	countOfSubstring++;

	if (stringsCount != NULL)
	{
		*stringsCount = countOfSubstring;
	}

	int* massOfLengths = STREX_ALLOC(int, (countOfSubstring));

	short counterOfAllocateAttempt = 0;

	while (!massOfLengths)
	{
		massOfLengths = STREX_ALLOC(int, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	int massOfLengthsPtr = 0;

	size_t currentLen = 0;

	int gap = 0;

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		int positionFind = StringExtended::strContain(splittingStr, strsrc + gap);
		if ((positionFind >= 0) && (positionFind == i - gap))
		{
			massOfLengths[massOfLengthsPtr] = currentLen;
			gap += strlen(splittingStr) + currentLen;
			currentLen = 0;
			massOfLengthsPtr++;

			if (strlen(splittingStr) > 1)			// Despite the fact that this was coded by me in adequate state,
				i += strlen(splittingStr) - 1;		// honestly, only god and quarter of my mind know how and why this works.
		}
		else currentLen++;
	}
	massOfLengths[massOfLengthsPtr] = currentLen;
	currentLen = 0;
	massOfLengthsPtr++;

	char** resultedmass = STREX_ALLOC(char*, (countOfSubstring));

	counterOfAllocateAttempt = 0;

	while (!massOfLengths)
	{
		resultedmass = STREX_ALLOC(char*, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	for (size_t i = 0; i < countOfSubstring; i++)
	{
		resultedmass[i] = STREX_ALLOC(char, (massOfLengths[i] + 1));
		if (!resultedmass[i])
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
		resultedmass[i][massOfLengths[i]] = '\0';
	}

	int strCharPointer = 0;
	int currentStringPointer = 0;

	gap = 0;

	for (int i = 0; i < strlen(strsrc); i++)
	{
		int positionFind = StringExtended::strContain(splittingStr, strsrc + gap);
		if ((positionFind >= 0) && (positionFind == i - gap))
		{
			gap += strlen(splittingStr) + strCharPointer;
			strCharPointer = 0;
			currentStringPointer++;

			if (strlen(splittingStr) > 1)
				i += strlen(splittingStr) - 1;
		}
		else
		{
			resultedmass[currentStringPointer][strCharPointer] = strsrc[i];
			strCharPointer++;
		}
	}
	STREX_DEALLOC(massOfLengths);
	return resultedmass;
}


char** _cdecl strEx::StringExtended::strSplitByToken(_In_z_ const char* strsrc, _In_z_ const char* strToken, _Out_ size_t* stringsCount)
{
	if (strsrc == 0 || strToken == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0 || strlen(strToken) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int countOfSubstring = 0;

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		for (size_t j = 0; j < strlen(strToken); j++)
		{
			if (strsrc[i] == strToken[j])
			{
				countOfSubstring++;
				break;
			}
		}
	}

	countOfSubstring++;

	if (stringsCount != NULL)
	{
		*stringsCount = countOfSubstring;
	}

	size_t* massOfLengths = STREX_ALLOC(size_t, (countOfSubstring));
	size_t massOfLengthsPtr = 0;
	size_t currentlen = 0;

	short counterOfAllocateAttempt = 0;
	while (!massOfLengths)
	{
		massOfLengths = STREX_ALLOC(size_t, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		bool found = false;
		for (size_t j = 0; j < strlen(strToken); j++)
		{
			if (strsrc[i] == strToken[j])
			{
				massOfLengths[massOfLengthsPtr] = currentlen;
				currentlen = 0;
				massOfLengthsPtr++;
				found = true;
				break;
			}
		}
		if (found)
			continue;
		currentlen++;
	}
	massOfLengths[massOfLengthsPtr] = currentlen;
	currentlen = 0;

	counterOfAllocateAttempt = 0;
	char** resultedmass = STREX_ALLOC(char*, countOfSubstring);
	while (!resultedmass)
	{
		resultedmass = STREX_ALLOC(char*, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	for (size_t i = 0; i < countOfSubstring; i++)
	{
		resultedmass[i] = STREX_ALLOC(char, (massOfLengths[i] + 1));
		resultedmass[i][massOfLengths[i]] = '\0';
	}

	size_t rmStringPtr = 0;
	size_t rmCharPtr = 0;

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		bool skip = false;
		for (size_t j = 0; j < strlen(strToken); j++)
		{
			if (strsrc[i] == strToken[j])
			{
				rmStringPtr++;
				rmCharPtr = 0;
				skip = true;
				break;
			}
		}
		if (skip)
			continue;
		resultedmass[rmStringPtr][rmCharPtr] = strsrc[i];
		rmCharPtr++;
	}
	STREX_DEALLOC(massOfLengths);
	return resultedmass;
}

char* _cdecl strEx::StringExtended::strToUpperCase(_In_z_ const char* strsrc)
{
	if (strsrc == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	char* result = STREX_ALLOC(char, (strlen(strsrc) + 1));

	short counterOfAllocateAttempt = 0;

	while (!result)
	{
		result = STREX_ALLOC(char, (strlen(strsrc) + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	result[strlen(strsrc)] = '\0';

	for (int i = 0; i < strlen(strsrc); i++)
	{
		result[i] = toupper(strsrc[i]);
	}
	return result;
}

char* _cdecl strEx::StringExtended::strToLowerCase(_In_z_ const char* strsrc)
{
	if (strsrc == 0)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	char* result = STREX_ALLOC(char, (strlen(strsrc) + 1));

	short counterOfAllocateAttempt = 0;

	while (!result)
	{
		result = STREX_ALLOC(char, (strlen(strsrc) + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	result[strlen(strsrc)] = '\0';

	for (int i = 0; i < strlen(strsrc); i++)
	{
		result[i] = tolower(strsrc[i]);
	}
	return result;
}

char* _cdecl strEx::StringExtended::strReplace(_In_z_ const char* strsrc, _In_z_ const char* strReplaceable, _In_z_ const char* strReplaceOn)
{
	if (strsrc == NULL || strReplaceable == NULL || strReplaceOn == NULL)
	{
		STREX_THROW_EXCEPTION(NullPointerException, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == NULL || strlen(strReplaceable) == NULL)
	{
		STREX_THROW_EXCEPTION(OutOfBoundsException, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int pointerOfReplaceable = StringExtended::strContain(strReplaceable, strsrc);

	if (pointerOfReplaceable < 0)
	{
		return StringExtended::strCopy(strsrc);
	}
	else
	{
		int lendifference = (strlen(strReplaceable) - strlen(strReplaceOn));

		size_t mainlen = (strlen(strsrc) - lendifference);

		char* returnedstr = STREX_ALLOC(char, (mainlen + 1));

		short counterOfAllocateAttempt = 0;

		while (!returnedstr)
		{
			returnedstr = STREX_ALLOC(char, (mainlen + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(MemoryAllocationException, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}

		returnedstr[mainlen] = '\0';

		int i = 0;
		for (i = 0; i < pointerOfReplaceable; i++)
		{
			returnedstr[i] = strsrc[i];
		}

		for (int j = 0; j < strlen(strReplaceOn); j++, i++)
		{
			returnedstr[i] = strReplaceOn[j];
		}

		for (i; i < mainlen; i++)
		{
			returnedstr[i] = strsrc[i + lendifference];
		}
		return returnedstr;
	}
}

#else

char* _cdecl strCopy(_In_z_ const char* strsrc)
{
	if (strsrc == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	char* strcopy = STREX_ALLOC(char, (strlen(strsrc) + 1));

	short counterOfAllocateAttempt = 0;

	while (!strcopy)
	{
		strcopy = STREX_ALLOC(char, (strlen(strsrc) + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	strcopy[strlen(strsrc)] = '\0';

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		strcopy[i] = strsrc[i];
	}
	return strcopy;
}

char* _cdecl strGet(void)
{
	char* dynamic = STREX_ALLOC(char, (STREX_BASE_ALLOC + 1));

	short counterOfAllocateAttempt = 0;

	while (!dynamic)
	{
		dynamic = STREX_ALLOC(char, (STREX_BASE_ALLOC + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	fgets(dynamic, STREX_BASE_ALLOC + 1, stdin);

	if (dynamic[(strlen(dynamic)) - 1] == '\n')
		dynamic[(strlen(dynamic)) - 1] = '\0';

	char* str = strCopy(dynamic);

	STREX_DEALLOC(dynamic);
	return str;
}

char* _cdecl strGet_s(_In_ size_t allocatedMemory)
{
	if (allocatedMemory == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	char* dynamic = STREX_ALLOC(char, (allocatedMemory + 1));


	short counterOfAllocateAttempt = 0;

	while (!dynamic)
	{
		dynamic = STREX_ALLOC(char, (allocatedMemory + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	fgets(dynamic, allocatedMemory + 1, stdin);

	if (dynamic[(strlen(dynamic)) - 1] == '\n')
		dynamic[(strlen(dynamic)) - 1] = '\0';

	char* str = strCopy(dynamic);

	STREX_DEALLOC(dynamic);
	return str;
}

char* _cdecl strConcat(_In_z_ const char* firstStr, ...)
{
	if (firstStr == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(firstStr) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	int mainlen = strlen(firstStr);

	va_list argptr;
	va_start(argptr, firstStr);

	char* tmpstr = (char*)" ";
	while (tmpstr[0] != '\0')
	{
		tmpstr = va_arg(argptr, char*);
		if (tmpstr == 0)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
		}
		mainlen += strlen(tmpstr);
	}
	va_end(argptr);

	char* returnedStr = STREX_ALLOC(char, (mainlen + 1));
	if (!returnedStr)
	{
		STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
	}
	returnedStr[mainlen] = '\0';

	int currentCharPointer = 0;
	for (size_t i = 0; i < strlen(firstStr); i++)
	{
		returnedStr[currentCharPointer] = firstStr[i];
		currentCharPointer++;
	}

	va_start(argptr, firstStr);
	tmpstr = (char*)" ";

	while (tmpstr[0] != '\0')
	{
		tmpstr = va_arg(argptr, char*);
		for (size_t i = 0; i < strlen(tmpstr); i++)
		{
			returnedStr[currentCharPointer] = tmpstr[i];
			currentCharPointer++;
		}
	}

	return returnedStr;
}

int _cdecl strContain(_In_z_ const char* strToFind, _In_z_ const char* strsrc)
{
	if (strToFind == 0 || strsrc == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strToFind) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	size_t strlenOfToFind = strlen(strToFind);
	size_t strlenOfBaseStr = strlen(strsrc);

	size_t count = 0;
	int flag = -1;
	for (size_t i = 0; i < strlenOfBaseStr; i++)
	{
		if (strToFind[0] == strsrc[i])
		{
			flag = i;
			size_t z = i;
			for (size_t j = 0; j < strlenOfToFind; j++, z++)
			{
				if (strToFind[j] == strsrc[z])
				{
					count++;
					if (count == strlenOfToFind)
					{
						return flag;
					}
				}
				else
				{
					flag = -1;
					count = 0;
					break;
				}
			}
		}
	}
	return flag;
}

char* _cdecl strErase(_In_z_ const char* whatStr, _In_z_ const char* strsrc)
{
	if (whatStr == 0 || strsrc == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(whatStr) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int positionOfWhatStr = strContain(whatStr, strsrc);
	if (positionOfWhatStr >= 0)
	{
		int size = strlen(strsrc) - strlen(whatStr);

		if (size <= 0)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}

		char* result = STREX_ALLOC(char, (size + 1));
		short counterOfAllocateAttempt = 0;

		while (!result)
		{
			result = STREX_ALLOC(char, (size + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}
		result[size] = '\0';

		for (size_t i = 0, j = 0; j < size && i < strlen(strsrc); i++, j++)
		{
			if (i == positionOfWhatStr)
			{
				i += strlen(whatStr);
			}
			result[j] = strsrc[i];
		}

		return result;
	}
	else
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
}

char* _cdecl strEraseInRange(_In_z_ const char* leftBorder, _In_z_ const char* rightBorder, _In_z_ const char* strsrc)
{
	if (leftBorder == 0 || rightBorder == 0 || strsrc == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(leftBorder) == 0 || strlen(rightBorder) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int positionOfLeftBorder = strContain(leftBorder, strsrc);
	int positionOfRightBorder = strContain(rightBorder, strsrc);
	if (positionOfLeftBorder >= 0 && positionOfRightBorder >= 0)
	{
		positionOfLeftBorder += strlen(leftBorder);

		size_t size = strlen(strsrc) - (positionOfRightBorder - positionOfLeftBorder);

		if (size <= 0)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}

		char* result = STREX_ALLOC(char, (size + 1));
		short counterOfAllocateAttempt = 0;

		while (!result)
		{
			result = STREX_ALLOC(char, (size + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}
		result[size] = '\0';

		for (size_t i = 0, j = 0; j < size && i < strlen(strsrc); i++)
		{
			if ((i < positionOfLeftBorder || i >= positionOfRightBorder))
			{
				result[j] = strsrc[i];
				j++;
			}
		}

		return result;
	}
	else
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
}

char* _cdecl strCutInRange(_In_z_ const char* leftBorder, _In_z_ const char* rightBorder, _In_z_ const char* strsrc)
{
	if (leftBorder == 0 || rightBorder == 0 || strsrc == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(leftBorder) == 0 || strlen(rightBorder) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int positionOfLeftBorder = strContain(leftBorder, strsrc);
	int positionOfRightBorder = strContain(rightBorder, strsrc);
	if (positionOfLeftBorder >= 0 && positionOfRightBorder >= 0)
	{
		positionOfLeftBorder += strlen(leftBorder);

		size_t size = (positionOfRightBorder - positionOfLeftBorder);

		if (positionOfLeftBorder >= positionOfRightBorder)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}

		char* result = STREX_ALLOC(char, (size + 1));
		short counterOfAllocateAttempt = 0;

		while (!result)
		{
			result = STREX_ALLOC(char, (size + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}
		result[size] = '\0';

		for (size_t i = 0, j = 0; j < size && i < strlen(strsrc); i++)
		{
			if ((i >= positionOfLeftBorder && i < positionOfRightBorder))
			{
				result[j] = strsrc[i];
				j++;
			}
		}

		return result;
	}
	else
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
}

void _cdecl strSort_AtoZ(_Inout_ const char** arraysrc, _In_ size_t size, _In_ bool case_sensetive)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}
	qsort_s(arraysrc, size, sizeof(char*), compareAtoZ, (void*)case_sensetive);
}

void _cdecl strSort_ZtoA(_Inout_ const char** arraysrc, _In_ size_t size, _In_ bool case_sensetive)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}

	qsort_s(arraysrc, size, sizeof(char*), compareZtoA, (void*)case_sensetive);
}

void _cdecl strSort_LenIncrease(_Inout_ const char** arraysrc, _In_ size_t size)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}
	qsort(arraysrc, size, sizeof(char*), compareLenIncrease);
}

void _cdecl strSort_LenDecrease(_Inout_ const char** arraysrc, _In_ size_t size)
{
	if (arraysrc == NULL)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	for (size_t i = 0; i < size; i++)
	{
		const char* ptr = arraysrc[i];
		if (ptr == NULL)
		{
			STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
		}
	}
	qsort(arraysrc, size, sizeof(char*), compareLenDecrease);
}

size_t _cdecl strContainCount(_In_ const char* strToFind, _In_ const char* strsrc)
{
	if (strsrc == 0 || strToFind == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strToFind) == 0 || strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	size_t strlenOfToFind = strlen(strToFind);
	size_t strlenOfBaseStr = strlen(strsrc);
	size_t countOfRepeats = 0;
	int count = 0;
	for (int i = 0; i < strlenOfBaseStr; i++)
	{
		count = 0;
		if (strToFind[0] == strsrc[i])
		{
			int z = i;
			for (int j = 0; j < strlenOfToFind; j++, z++)
			{
				if (strToFind[j] == strsrc[z])
				{
					count++;
					if (count == strlenOfToFind)
					{
						countOfRepeats++;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	return countOfRepeats;
}

char** _cdecl strSplitByParser(_In_z_ const char* strsrc, _In_z_ const char* splittingStr, _Out_ size_t* stringsCount)
{
	if (strsrc == 0 || splittingStr == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0 || strlen(splittingStr) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	size_t countOfSubstring = strContainCount(splittingStr, strsrc);

	countOfSubstring++;

	if (stringsCount != NULL)
	{
		*stringsCount = countOfSubstring;
	}

	size_t* massOfLengths = STREX_ALLOC(size_t, (countOfSubstring));
	short counterOfAllocateAttempt = 0;

	while (!massOfLengths)
	{
		massOfLengths = STREX_ALLOC(size_t, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}
	int massOfLengthsPtr = 0;

	size_t currentLen = 0;

	int gap = 0;

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		int positionFind = strContain(splittingStr, strsrc + gap);
		if ((positionFind >= 0) && (positionFind == i - gap))
		{
			massOfLengths[massOfLengthsPtr] = currentLen;
			gap += strlen(splittingStr) + currentLen;
			currentLen = 0;
			massOfLengthsPtr++;

			if (strlen(splittingStr) > 1)			// Despite the fact that this was coded by me in adequate state,
				i += strlen(splittingStr) - 1;		// honestly, only god and quarter of my mind know how and why this works.
		}
		else currentLen++;
	}
	massOfLengths[massOfLengthsPtr] = currentLen;
	currentLen = 0;
	massOfLengthsPtr++;

	char** resultedmass = STREX_ALLOC(char*, (countOfSubstring));

	counterOfAllocateAttempt = 0;

	while (!resultedmass)
	{
		resultedmass = STREX_ALLOC(char*, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	for (size_t i = 0; i < countOfSubstring; i++)
	{
		resultedmass[i] = STREX_ALLOC(char, (massOfLengths[i] + 1));
		if (!resultedmass[i])
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
		resultedmass[i][massOfLengths[i]] = '\0';
	}

	int strCharPointer = 0;
	int currentStringPointer = 0;

	gap = 0;

	for (int i = 0; i < strlen(strsrc); i++)
	{
		int positionFind = strContain(splittingStr, strsrc + gap);
		if ((positionFind >= 0) && (positionFind == i - gap))
		{
			gap += strlen(splittingStr) + strCharPointer;
			strCharPointer = 0;
			currentStringPointer++;

			if (strlen(splittingStr) > 1)
				i += strlen(splittingStr) - 1;
		}
		else
		{
			resultedmass[currentStringPointer][strCharPointer] = strsrc[i];
			strCharPointer++;
		}
	}
	STREX_DEALLOC(massOfLengths);
	return resultedmass;
}

char** _cdecl strSplitByToken(_In_z_ const char* strsrc, _In_z_ const char* strToken, _Out_ size_t* stringsCount)
{
	if (strsrc == 0 || strToken == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0 || strlen(strToken) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int countOfSubstring = 0;

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		for (size_t j = 0; j < strlen(strToken); j++)
		{
			if (strsrc[i] == strToken[j])
			{
				countOfSubstring++;
				break;
			}
		}
	}

	countOfSubstring++;

	if (stringsCount != NULL)
	{
		*stringsCount = countOfSubstring;
	}

	size_t* massOfLengths = STREX_ALLOC(size_t, (countOfSubstring));
	size_t massOfLengthsPtr = 0;
	size_t currentlen = 0;

	short counterOfAllocateAttempt = 0;
	while (!massOfLengths)
	{
		massOfLengths = STREX_ALLOC(size_t, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		bool found = false;
		for (size_t j = 0; j < strlen(strToken); j++)
		{
			if (strsrc[i] == strToken[j])
			{
				massOfLengths[massOfLengthsPtr] = currentlen;
				currentlen = 0;
				massOfLengthsPtr++;
				found = true;
				break;
			}
		}
		if (found)
			continue;
		currentlen++;
	}
	massOfLengths[massOfLengthsPtr] = currentlen;
	currentlen = 0;

	counterOfAllocateAttempt = 0;
	char** resultedmass = STREX_ALLOC(char*, countOfSubstring);
	while (!resultedmass)
	{
		resultedmass = STREX_ALLOC(char*, (countOfSubstring));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	for (size_t i = 0; i < countOfSubstring; i++)
	{
		resultedmass[i] = STREX_ALLOC(char, (massOfLengths[i] + 1));
		resultedmass[i][massOfLengths[i]] = '\0';
	}

	size_t rmStringPtr = 0;
	size_t rmCharPtr = 0;

	for (size_t i = 0; i < strlen(strsrc); i++)
	{
		bool skip = false;
		for (size_t j = 0; j < strlen(strToken); j++)
		{
			if (strsrc[i] == strToken[j])
			{
				rmStringPtr++;
				rmCharPtr = 0;
				skip = true;
				break;
			}
		}
		if (skip)
			continue;
		resultedmass[rmStringPtr][rmCharPtr] = strsrc[i];
		rmCharPtr++;
	}
	STREX_DEALLOC(massOfLengths);
	return resultedmass;
}

char* _cdecl strToUpperCase(_In_z_ const char* strsrc)
{
	if (strsrc == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	char* result = STREX_ALLOC(char, (strlen(strsrc) + 1));

	int counterOfAllocateAttempt = 0;

	while (!result)
	{
		result = STREX_ALLOC(char, (strlen(strsrc) + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	result[strlen(strsrc)] = '\0';

	for (int i = 0; i < strlen(strsrc); i++)
	{
		result[i] = toupper(strsrc[i]);
	}
	return result;
}

char* _cdecl strToLowerCase(_In_z_ const char* strsrc)
{
	if (strsrc == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == 0)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}
	char* result = STREX_ALLOC(char, (strlen(strsrc) + 1));

	int counterOfAllocateAttempt = 0;

	while (!result)
	{
		result = STREX_ALLOC(char, (strlen(strsrc) + 1));
		counterOfAllocateAttempt++;
		if (counterOfAllocateAttempt >= 5)
		{
			STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
		}
	}

	result[strlen(strsrc)] = '\0';

	for (int i = 0; i < strlen(strsrc); i++)
	{
		result[i] = tolower(strsrc[i]);
	}
	return result;
}

char* _cdecl strReplace(_In_z_ const char* strsrc, _In_z_ const char* strReplaceable, _In_z_ const char* strReplaceOn)
{
	if (strsrc == NULL || strReplaceable == NULL || strReplaceOn == NULL)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_NULL_POINTER);
	}
	else if (strlen(strsrc) == NULL || strlen(strReplaceable) == NULL)
	{
		STREX_THROW_EXCEPTION(EINVAL, MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS);
	}

	int pointerOfReplaceable = strContain(strReplaceable, strsrc);

	if (pointerOfReplaceable < 0)
	{
		return strCopy(strsrc);
	}
	else
	{
		int lendifference = (strlen(strReplaceable) - strlen(strReplaceOn));

		size_t mainlen = (strlen(strsrc) - lendifference);

		char* returnedstr = STREX_ALLOC(char, (mainlen + 1));

		int counterOfAllocateAttempt = 0;

		while (!returnedstr)
		{
			returnedstr = STREX_ALLOC(char, (mainlen + 1));
			counterOfAllocateAttempt++;
			if (counterOfAllocateAttempt >= 5)
			{
				STREX_THROW_EXCEPTION(ENOMEM, MSG_EXCEPTION_OUT_OF_MEMORY);
			}
		}

		returnedstr[mainlen] = '\0';

		int i = 0;
		for (i = 0; i < pointerOfReplaceable; i++)
		{
			returnedstr[i] = strsrc[i];
		}

		for (int j = 0; j < strlen(strReplaceOn); j++, i++)
		{
			returnedstr[i] = strReplaceOn[j];
		}

		for (i; i < mainlen; i++)
		{
			returnedstr[i] = strsrc[i + lendifference];
		}
		return returnedstr;
	}
}

#endif

static int _cdecl compareAtoZ(void* context, const void* str1, const void* str2)
{
	const char** tmpstr1 = (const char**)str1;
	const char** tmpstr2 = (const char**)str2;

	bool compare_condition = (bool*)context;

	if (compare_condition)
		return strcmp(*tmpstr1, *tmpstr2);
	else
		return _stricmp(*tmpstr1, *tmpstr2);
}

static int _cdecl compareZtoA(void* context, const void* str1, const void* str2)
{
	const char** tmpstr1 = (const char**)str1;
	const char** tmpstr2 = (const char**)str2;

	bool compare_condition = (bool*)context;

	if (compare_condition)
		return strcmp(*tmpstr2, *tmpstr1);
	else
		return _stricmp(*tmpstr2, *tmpstr1);
}

static int _cdecl compareLenIncrease(const void* str1, const void* str2)
{
	const char** tmpstr1 = (const char**)str1;
	const char** tmpstr2 = (const char**)str2;

	return strlen(*tmpstr1) - strlen(*tmpstr2);
}

static int _cdecl compareLenDecrease(const void* str1, const void* str2)
{
	const char** tmpstr1 = (const char**)str1;
	const char** tmpstr2 = (const char**)str2;

	return strlen(*tmpstr2) - strlen(*tmpstr1);
}