

#ifndef OCTETOS_CORE_TESTS_V3_HH
#define OCTETOS_CORE_TESTS_V3_HH


#include <CUnit/Basic.h>

#include "../src/Exception-v3.hh"
//#include "tests.hh"


int v3_init(void);
int v3_clean(void);
void v3_developing();
void v3_reduced_parser();
void v3_lc_innier_semver();
void v3_lc_semver();

#endif