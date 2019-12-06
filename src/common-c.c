#include "common.h"

const char* octetos_version_getString(enum octetos_version_Stage stage)
{
	switch(stage)
	{
		case developing:	
			return "developing";
		case snapshot: 
			return "snapshot";
		case alpha:
			return "alpha";
		case beta:
			return "beta";
		case betarelease:
			return "betarelease";
		case rc:
			return "rc";
		case prerelease:
			return "prerelease";
		case release:
			return "release";
		case rtm:
			return "RTM";
		case ga:
			return "GA";
		default:
			return "unknown";
	}
}

/*const char* octetos_core_Version_toString(const struct octetos_toolkit_Version* version)
{
	char* verstr = NULL;
	if(version->major > -1)
	{
		char* verstrMa;
		asprintf(&verstrMa, "%i", version->major);
		verstr = verstrMa;
	}
	else
	{//falla devido a que no esta inicializado
		return NULL;
	}
	if(version->minor > -1)
	{
		char* verstrMi;
		asprintf(&verstrMi, "%i", version->minor);
		if(verstr != NULL) 
		{
			verstr = strcat(verstr,".");
			verstr = strcat(verstr,verstrMi);
		}
	}
	else
	{//falla devido a que no esta inicializado
		return NULL;
	}
	if(version->patch > -1)
	{
		char* verstrPa;
		asprintf(&verstrPa, "%i", version->patch);
		if(verstr != NULL) 
		{
			verstr = strcat(verstr,".");
			verstr = strcat(verstr,verstrPa);
		}
	}
	else
	{//falla devido a que no esta inicializado
		return NULL;
	}
	
	if(version->stage == unknown)
	{//falla devido a que no esta inicializado
		return NULL;
	}
	else if(version->stage == alpha)
	{
		verstr = strcat(verstr,"-alpha");		
	}
	else if(version->stage == beta)
	{
		verstr = strcat(verstr,"-beta");
	}
	else if(version->stage == release)
	{
		verstr = strcat(verstr,"-release");
	}
	
	
	return verstr;
}	*/


