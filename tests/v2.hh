

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

#include "config.h"
#include "../src/Artifact.hh"
#include "../src/memory.hh"
#include "../src/semver-lexer.h"
#include "../src/data.hh"
#include "../src/shell.hh"

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
void v2_testsemverc();
void v2_testData();
void v2_testShell();

#endif