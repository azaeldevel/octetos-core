

#include "v3.hh"

#include <string.h>
#include <iostream>
#if defined(__linux__)
    //#include <src/Exception-v3.hh>
    //#include <src/Version-v3.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <core/src/Exception-v3.hh>
    //#include <core/src/Version-v3.hh>
#else
	#error "Plataforma desconocida"
#endif


using namespace oct::core::v3;

int v3_init(void)
{
	return 0;
}

int v3_clean(void)
{
	return 0;
}


void v3_developing()
{

}

