

#ifndef OCTETOS_CORE_TESTS_V2_HH
#define OCTETOS_CORE_TESTS_V2_HH

#include <CUnit/Basic.h>

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <unistd.h>
#include <limits.h>
#include <list>
#include <algorithm>

#if defined(__linux__) && defined IDE_CODEBLOCKS

#elif defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

#include "../src/Artifact-v2.hh"
#include "../src/Error.hh"

static std::string bdir;

int v2_init(void);
int v2_clean(void);
void v2_testImports_v100();
void v2_testParseString_v100();
void v2_testParseString_v200();
void v2_testComparators_v100();
void v2_testOperations_v100();
void v2_reduced_parser();
void v2_developing();

#endif
