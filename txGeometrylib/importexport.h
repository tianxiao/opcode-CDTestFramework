#ifdef TXGEOMETRY_DLL_EXPORTS
	#define TXGEOMETRY_API __declspec(dllexport)
#else
	#define TXGEOMETRY_API __declspec(dllimport)
#endif
