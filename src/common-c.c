#include "common.h"

void octetos_Semver_init(struct octetos_Semver* version)
{
	version->major = -1;
	version->minor = -1;
	version->patch = -1;
	version->stage = unknown;
	version->stageNumber = -1;
	version->build.type = none;
	version->build.value.ul = 0;	
}
const char* octetos_Stage_getString(enum octetos_version_Stage stage)
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

const char* octetos_Semver_toString(struct octetos_Semver* version)
{
	char* verstr  = 0;
	/*if(version->major > -1)
	{
		char* verstrMa;
		asprintf(&verstrMa, "%i", version->major);
		verstr = verstrMa;
	}
	else
	{//falla devido a que no esta inicializado
		return 0;
	}
	if(version->minor > -1)
	{
		char* verstrMi;
		asprintf(&verstrMi, "%i", version->minor);
		if(verstr != 0) 
		{
			verstr = strcat(verstr,".");
			verstr = strcat(verstr,verstrMi);
		}
	}
	else
	{//falla devido a que no esta inicializado
		return 0;
	}
	if(version->patch > -1)
	{
		char* verstrPa;
		asprintf(&verstrPa, "%i", version->patch);
		if(verstr != 0) 
		{
			verstr = strcat(verstr,".");
			verstr = strcat(verstr,verstrPa);
		}
	}
	else
	{//falla devido a que no esta inicializado
		return 0;
	}
	
	if(version->stage == unknown)
	{//falla devido a que no esta inicializado
		return 0;
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
	}*/
	
	
	return verstr;
}


