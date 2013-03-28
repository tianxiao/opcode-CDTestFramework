#ifdef GRAPHSTRUCTURE_DLL_EXPORTS
	#define GRAPHSTRUCTURE_API __declspec(dllexport)
#else
	#define GRAPHSTRUCTURE_API __declspec(dllimport)
#endif
