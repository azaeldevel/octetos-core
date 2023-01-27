

#ifndef OCTETOS_CORE_TESTS_V3_HH
#define OCTETOS_CORE_TESTS_V3_HH


#include <CUnit/Basic.h>


//#include "tests.hh"
#if defined(__linux__)
    #include <src/Exception-v3.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <core/src/Exception-v3.hh>
#else
	#error "Plataforma desconocida"
#endif

int v3_init(void);
int v3_clean(void);
void v3_developing();
void v3_reduced_parser();
void v3_lc_innier_semver();
void v3_lc_semver();
void v3_lc_semver2();
void v3_lc_semver_rejects();

#endif