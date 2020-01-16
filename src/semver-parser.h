#ifndef OCTETOS_CORE_SEMVER_PARSER_H
#define OCTETOS_CORE_SEMVER_PARSER_H

#include "common.h"

struct octetos_core_Tray
{
	struct octetos_core_Semver* version;
    int dysplay_erro;
};

#ifdef __cplusplus  
extern "C" {
#endif 
    int parse_string(struct octetos_core_Tray* ty, const char* in);
#ifdef __cplusplus 
} 
#endif

#endif

 
