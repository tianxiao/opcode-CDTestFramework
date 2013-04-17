#ifndef TXMEMORYUTIL_DLL_HEADERFILE
#define TXMEMORYUTIL_DLL_HEADERFILE

#ifdef TXMEMORYUTIL_DLL_EXPORTS
	#define TXMEMORYUTIL_API __declspec(dllexport)
#else
	#define TXMEMORYUTIL_API __declspec(dllimport)
#endif

#endif