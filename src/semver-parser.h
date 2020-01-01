#ifndef OCTETOS_CORE_VERSION_READER_DRIVER_H
#define OCTETOS_CORE_VERSION_READER_DRIVER_H

#include "common.h"

struct octetos_Tray
{
	struct octetos_Semver* version;
    int dysplay_erro;
};

#ifdef __cplusplus  
extern "C" {
#endif 
    int parse_string(struct octetos_Tray* ty,const char* in);
#ifdef __cplusplus 
} 
#endif

#endif

 
