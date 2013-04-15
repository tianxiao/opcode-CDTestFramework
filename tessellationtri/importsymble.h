#ifdef SUBDIVISIONTESSELL_DLL_EXPORTS
	#define SUBDIVISIONTESSELL_API __declspec(dllexport)
#else
	#define SUBDIVISIONTESSELL_API __declspec(dllimport)
#endif
