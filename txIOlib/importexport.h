#ifndef TXSIO_DLL_EXPORTS_HEADERFILE
#define TXSIO_DLL_EXPORTS_HEADERFILE

#ifdef TXSIO_DLL_EXPORTS
	#define TXSIO_API __declspec(dllexport)
#else
	#define TXSIO_API __declspec(dllimport)
#endif

#endif
