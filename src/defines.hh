#ifndef OCTETOS_CORE_DEFINES_HH_INCLUDED
#define OCTETOS_CORE_DEFINES_HH_INCLUDED

#if defined BUILDING_DLL && defined WINDOWS_MINGW
    #define DECLSPCE_DLL __declspec(dllexport)
#elif WINDOWS_MINGW
    #define DECLSPCE_DLL __declspec(dllimport)
#else
    #define DECLSPCE_DLL
#endif


#ifdef __GNUG__
	#define DEPRECATED __attribute__ ((deprecated))
#else
	#define DEPRECATED
#endif

#endif
