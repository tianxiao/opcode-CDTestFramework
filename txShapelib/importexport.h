#ifndef TXSHAPE_DLL_EXPORTS_HEADERFILE
#define TXSHAPE_DLL_EXPORTS_HEADERFILE

#ifdef TXSHAPE_DLL_EXPORTS
	#define TXSHAPE_API __declspec(dllexport)
#else
	#define TXSHAPE_API __declspec(dllimport)
#endif

#endif
