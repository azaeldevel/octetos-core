#ifndef OCTETOS_CORE_VERSION_READER_DRIVER_H
#define OCTETOS_CORE_VERSION_READER_DRIVER_H

#include "common.h"

struct Tray
{
	struct octetos_version_Version version;
    int dysplay_erro;
};

#ifdef __cplusplus  
extern "C" {
#endif 
    int parse_string(struct Tray* ty,const char* in);
#ifdef __cplusplus 
} 
#endif

#endif

 
