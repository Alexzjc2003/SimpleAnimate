#ifdef SA_EXPORTS
#define SA_API __declspec(dllexport)
#else
#define SA_API __declspec(dllimport)
#endif