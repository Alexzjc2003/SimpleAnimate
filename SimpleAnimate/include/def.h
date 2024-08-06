#ifdef SA_EXPORTS
#define SA_API __declspec(dllexport)
#else
#define SA_API __declspec(dllimport)
#endif

#define SA_EXPERIMENTAL

#ifdef SA_EXPERIMENTAL
#define SA_USING_PROXY
#endif
