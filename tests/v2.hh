

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

#if defined(__linux__)
    #include "../src/Artifact-v2.hh"
    #include "../src/memory.hh"
    #include "../src/semver-lexer.h"
    #include "../src/data.hh"
    #include "../src/shell.hh"
#elif defined(_WIN32) || defined(_WIN64)
    #include <core/src/Artifact-v2.hh>
    #include <core/src/memory.hh>
    #include <core/src/semver-lexer.h>
    #include <core/src/data.hh>
    #include <core/src/shell.hh>
#else
	#error "Plataforma desconocida"
#endif

static std::string bdir;

int v2_init(void);
int v2_clean(void);
void v2_testImports_v100();
void v2_testParseString_v100();
void v2_testParseString_v200();
void v2_testComparators_v100();
void v2_testOperations_v100();
void v2_testMemory();
void v2_testShell();
void v2_testData();
void v2_testShell();
void v2_reduced_parser();
void v2_developing();

#endif
