

#ifndef OCTETOS_CORE_TESTS_V3_HH
#define OCTETOS_CORE_TESTS_V3_HH


#include "../src/Exception-v3.hh"
#include "../src/Version-v3.hh"
#include <stdio.h>      /* printf */
#include <assert.h>

int v3_init(void);
int v3_clean(void);

void v3_developing();
void v3_reduced_parser();

#endif