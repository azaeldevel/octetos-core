

#ifndef OCTETOS_CORE_TESTS_V3_HH
#define OCTETOS_CORE_TESTS_V3_HH


#include <CUnit/Basic.h>


//#include "tests.hh"
#if defined(__linux__)
    #include <core/3/Exception.hh>
#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

int v3_init(void);
int v3_clean(void);
void v3_developing();
void v3_array();
void v3_tree();


#endif
