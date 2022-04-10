/*
*****************************************************************
*                                                               *
*   strEx.h                                                     *
*                                                               *
*   C/C++ String Extended Library made up by Fedrushkov Denis   *
*                                                               *
*   Version: 1.0                                                *
*                                                               *
*   This library was made as way to upgrade quality of life     *
*   when using strings as char arrays in C/C++.                 *
*                                                               *
*****************************************************************


*************************************************************************************
*                                                                                   *
*   Description and notes about library:                                            *
*                                                                                   *
*   This library uses exceptions as debug method in C++                             *
*   and asserts & errno.h as debug method in C.                                     *
*   Library uses SAL annotations to to make her easier to understand and use        *
*   and have integrated documentation about all functions.                          *
*                                                                                   *
*   Provided exceptions type:                                                       *
*                                                                                   *
*   Out of bounds - declared as MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS                   *
*   Null-pointer - declared as MSG_EXCEPTION_NULL_POINTER                           *
*   Memory allocation - declared as MSG_EXCEPTION_OUT_OF_MEMORY                     *
*                                                                                   *
*   P.S: Also this library was not completely unit-tested                           *
*   so you can leave unhandled errors to fix and tips for improvement library       *
*   on https://github.com/RedGhost2014.                                             *
*                                                                                   *
*************************************************************************************
*/


#ifndef _STREX_
#define _STREX_

#ifdef __cplusplus

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <cstdarg>

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <crtdbg.h>
#include <stdbool.h>
#include <ctype.h>
#endif

#include <sal.h>
#include "strEx_def.h"

#ifdef __cplusplus

namespace strEx
{
	class MsgException : public std::exception
	{
	public:

		explicit MsgException(const char* what);

		const char* what() const noexcept override;

	private:
		char* whatStr;
	};

	class MemoryAllocationException : public MsgException
	{
	public:
		explicit MemoryAllocationException(const char* what) : MsgException(what) { }
	};

	class OutOfBoundsException : public MsgException
	{
	public:
		explicit OutOfBoundsException(const char* what) : MsgException(what) { }
	};

	class NullPointerException : public MsgException
	{
	public:
		explicit NullPointerException(const char* what) : MsgException(what) { }
	};

	class STREX_DLLIMPORT StringExtended
	{
	public:
#endif

#ifndef STREX_NO_WARNINGS
		STREX_DEPRECATED_REASON(Uncontrolled memory allocation., strGet_s)
#endif
		/*
		*	Gets a string from stdin.
		* 
		* 	Note: better use strGet_s because of hardcoded size of allocated memory to buffer.
		*	Hardcoded size declaration is STREX_BASE_ALLOC.
		* 	
		* 	Returned value:
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code. 
		*	CPP:	throws an exception.
		*
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strGet(
		void
		);

		/*
		*	Gets a string from stdin. A more secure version of strGet.
		* 	
		*	Parametres:
		*		
		*		[in] allocatedMemory: 
		*			Size in bytes allocating to string.
		*		
		* 	Returned value:
		*	
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*	
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*	
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strGet_s(
			_In_ size_t allocatedMemory
		);

		/*
		*	Copies a string.
		*
		*	Parametres:
		*
		*		[in] strsrc:
		*			Source string to copy.
		*
		* 	Returned value:
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strCopy(
			_In_z_ const char* strsrc
		);

		/*
		*	Concatinates strings into one.
		*
		*	Parametres:
		*
		*		[in] firstStr:
		*			Source string to start from.
		*
		*	Note:
		*		To mark down end of concatinate use empty or only nullterminated string: "" or "\\0".
		*		Not using this will cause undefind behavior.
		*
		* 	Returned value:
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strConcat(
			_In_z_ const char* firstStr, 
			...
		);

		/*
		*	Checks whether the string A is contained in string B.
		*
		*	Parametres:
		*
		*		[in] strToFind:
		*			String to found.
		*		[in] strsrc:
		*			Source string.
		* 
		* 	Returned value:
		*
		*	Returns a character pointer of foundeable string if string was found eiher -1 if she was not found,
		*	if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*/
		STREX_DLLIMPORT STREX_TYPE(int) strContain(
			_In_z_ const char* strToFind,
			_In_z_ const char* strsrc
		);

		/*
		*	Counts the number of occurrences of string A in string B.
		*
		*	Parametres:
		*
		*		[in] strToFind:
		*			String to found.
		*		[in] strsrc:
		*			Source string.
		*
		* 	Returned value:
		*
		*	Returns a number of occurrences of string A in string B if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*/
		STREX_DLLIMPORT STREX_TYPE(size_t) strContainCount(
			_In_ const char* strToFind,
			_In_ const char* strsrc
		);

		/*
		*	Erases string A from string B.
		*
		*	Parametres:
		*
		*		[in] whatStr:
		*			String to erase.
		*		[in] strsrc:
		*			Source string.
		*
		* 	Returned value:
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*	Usage example:
		*	Input: strErase("orl", "Hello world");
		*	Output: "Hello wd"
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strErase(
			_In_z_ const char* whatStr,
			_In_z_ const char* strsrc
		);

		/*
		*	Erases content between borders from string not including them. 
		*
		*	Parametres:
		*
		*		[in] leftBorder:
		*			Left string border.
		*		[in] rightBorder:
		*			Right string border.
		*		[in] strsrc:
		*			Source string.
		*
		* 	Returned value:
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*	Usage example:
		*	Input: strEraseInRange("el", "rl", "Hello world");
		*	Output: "Helrld"
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strEraseInRange(
			_In_z_ const char* leftBorder,
			_In_z_ const char* rightBorder,
			_In_z_ const char* strsrc
		);

		/*
		*	Cuts content between borders from string not including them.
		*
		*	Parametres:
		*
		*		[in] leftBorder:
		*			Left string border.
		*		[in] rightBorder:
		*			Right string border.
		*		[in] strsrc:
		*			Source string.
		*
		* 	Returned value:
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*	Usage example:
		*	Input: strCutInRange("el", "rl", "Hello world");
		*	Output: "lo wo"
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strCutInRange(
			_In_z_ const char* leftBorder,
			_In_z_ const char* rightBorder,
			_In_z_ const char* strsrc
		);

		/*
		*	Splits a string into an array of strings by string-parser.
		*
		*	Parametres:
		*
		*		[in] strsrc:
		*			Source string.
		*		[in] splittingStr:
		*			String-parser used to split source string.
		*		[out] stringsCount:
		*			Pointer to a variable that will get resulted count of strings.
		*
		* 	Returned value:
		*
		*	Returns a pointer to strings array in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*	Usage examples:
		* 
		*	Input: 
		*		strSplitByParser("Hello World and another world", " ", &countOfSubstrings);
		*	Output: 
		*	"Hello"
		*	"World"
		*	"and"
		*	"another"
		*	"world"
		* 
		*	Input:
		*		strSplitByParser("Hello World and another world", "rl", &countOfSubstrings);
		* 	Output: 
		*	"Hello Wo"
		*	"d and another wo"
		*	"d"
		*/
		STREX_DLLIMPORT STREX_TYPE(char**) strSplitByParser(
			_In_z_ const char* strsrc, 
			_In_z_ const char* splittingStr, 
			_Out_ size_t* stringsCount
		);

		/*
		*	Splits a string into an array of strings by tokens.
		*
		*	Parametres:
		*
		*		[in] strsrc:
		*			Source string.
		*		[in] strToken:
		*			String which contains tokens.
		*		[out] stringsCount:
		*			Pointer to a variable that will get resulted count of strings.
		*
		* 	Returned value:
		*
		*	Returns a pointer to strings array in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*
		*	Usage examples:
		*
		*	Input:
		*		strSplitByToken("Hello!World and,another world", "!,", &countOfSubstrings);
		*	Output:
		*	"Hello"
		*	"World and"
		*	"another world"
		* 
		*/
		STREX_DLLIMPORT STREX_TYPE(char**) strSplitByToken(
			_In_z_ const char* strsrc,
			_In_z_ const char* strToken,
			_Out_ size_t* stringsCount
		);

		/*
		*	Sorts strings array lexicographically from A to Z.
		*
		*	Parametres:
		*
		*		[in, out] arraysrc:
		*			Source of strings array.
		*		[in] size:
		*			Count of strings in array.
		*		[in] case_sensetive:
		*			Condition to sort.
		*			If true - sort will be case sensetive.
		*
		*	Returns none if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*/
		STREX_DLLIMPORT STREX_TYPE(void) strSort_AtoZ(
			_Inout_ const char** arraysrc,
			_In_ size_t size,
			_In_ bool case_sensetive
		);

		/*
		*	Sorts strings array lexicographically from Z to A.
		*
		*	Parametres:
		*
		*		[in, out] arraysrc:
		*			Source of strings array.
		*		[in] size:
		*			Count of strings in array.
		*		[in] case_sensetive:
		*			Condition to sort.
		*			If true - sort will be case sensetive.
		*
		*	Returns none if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*/
		STREX_DLLIMPORT STREX_TYPE(void) strSort_ZtoA(
			_Inout_ const char** arraysrc,
			_In_ size_t size,
			_In_ bool case_sensetive
		);

		/*
		*	Sorts strings array by lengths increase.
		*
		*	Parametres:
		*
		*		[in, out] arraysrc:
		*			Source of strings array.
		*		[in] size:
		*			Count of strings in array.
		*
		*	Returns none if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*/
		STREX_DLLIMPORT STREX_TYPE(void) strSort_LenIncrease(
			_Inout_ const char** arraysrc,
			_In_ size_t size
		);

		/*
		*	Sorts strings array by lengths decrease.
		*
		*	Parametres:
		*
		*		[in, out] arraysrc:
		*			Source of strings array.
		*		[in] size:
		*			Count of strings in array.
		*
		*	Returns none if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*/
		STREX_DLLIMPORT STREX_TYPE(void) strSort_LenDecrease(
			_Inout_ const char** arraysrc,
			_In_ size_t size
		);

		/*
		*	Ñonverts source string to upper case.
		*
		*	Parametres:
		*
		*		[in] strsource:
		*			Source string.
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strToUpperCase(
			_In_z_ const char* strsrc
		);

		/*
		*	Ñonverts source string to lower case.
		*
		*	Parametres:
		*
		*		[in] strsource:
		*			Source string.
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strToLowerCase(
			_In_z_ const char* strsrc
		);

		/*
		*	Replace string A on string B in Source string.
		*
		*	Parametres:
		*
		*		[in] strsrc:
		*			Source string.
		*		[in] strReplaceable:
		*			String that will be replaced.
		*		[in] strReplaceOn:
		*			String that will be placed instead strReplaceable.
		*
		*	Returns a pointer to string in heap if execute was succesfull, else:
		*
		*	C:		returns error code and set errno value to error code.
		*	CPP:	throws an exception.
		*/
		STREX_DLLIMPORT STREX_TYPE(char*) strReplace(
			_In_z_ const char* strsrc,
			_In_z_ const char* strReplaceable,
			_In_z_ const char* strReplaceOn
		);


#ifdef __cplusplus
	};
}
#endif

#endif // !_STREX_

