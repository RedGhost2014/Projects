#ifndef _STREX_DEF_
#define _STREX_DEF_

//#define STREX_DLL_LIBRARY // Undef/Comment this to compile to dll format

#ifdef __cplusplus

	#ifdef STREX_DLL_LIBRARY
		#define STREX_DLLIMPORT [[dllimport]]
	#else
		#define STREX_DLLIMPORT 
	#endif
	#define STREX_DECLSPEC_DEPRICATED(_Text) [[deprecated(_Text)]]

	#define STREX_TYPE(_Type) static _Type _cdecl 

	#define STREX_THROW_EXCEPTION(_exceptiontype, _Text) throw _exceptiontype(_Text)

	#define STREX_ALLOC(_Type, _Size) new _Type[_Size]
	#define STREX_DEALLOC(_Arg) delete[] _Arg

	#define MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS	"Exception: Argument is out of bounds."
	#define MSG_EXCEPTION_NULL_POINTER			"Exception: Argument is null-pointer."
	#define MSG_EXCEPTION_OUT_OF_MEMORY			"Exception: Out of free memory."

#else

	#ifdef STREX_DLL_LIBRARY
		#define STREX_DLLIMPORT __declspec(dllimport)
	#else
		#define STREX_DLLIMPORT 
	#endif
	#define STREX_DECLSPEC_DEPRICATED(_Text) __declspec(deprecated(_Text))

	#define STREX_TYPE(_Type) _Type _cdecl 

	#define STREX_THROW_EXCEPTION(_Type, _Text) \
				_ASSERT_EXPR(0, _Text);         \
				_set_errno(_Type);              \
				return _Type                    \

	#define STREX_ALLOC(_Type, _Size) (_Type*)malloc(_Size * sizeof(_Type))
	#define STREX_DEALLOC(_Arg) free(_Arg)

	#define MSG_EXCEPTION_INDEX_OUT_OF_BOUNDS	L"Exception: Argument is out of bounds."
	#define MSG_EXCEPTION_NULL_POINTER			L"Exception: Argument is null-pointer."
	#define MSG_EXCEPTION_OUT_OF_MEMORY			L"Exception: Out of free memory."

#endif // __cplusplus

#define STREX_BASE_ALLOC 128

#define STREX_DEPRECATED_REASON(_reason, _alternative)          \
STREX_DECLSPEC_DEPRICATED                                       \
(                                                               \
	"This function declared as unrecommended. Reason: "         \
	#_reason                                                    \
	" Consider using "                                          \
	#_alternative                                               \
	" instead. To disable deprecation, use STREX_NO_WARNINGS."  \
)                                                               \


#endif // !_STREX_DEF_

