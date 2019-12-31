#include <stdio.h>

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

const char* octetos_Semver_toString(const struct octetos_Semver* version,enum octetos_Semver_FormatString formato)
{
	const char* numberStr  = NULL;	
	if(version->major > -1 && version->minor > -1 && version->patch > -1)
	{
		char* buffer[20];
		int leng = sprintf(buffer,"%d.%d.%d",version->major,version->minor,version->patch);
		numberStr = malloc(leng +1);
		strcpy(numberStr, buffer);
	}	
	else if(version->major > -1 && version->minor > -1)
	{
		char* buffer[15];
		int leng = sprintf(buffer,"%d.%d",version->major,version->minor);
		numberStr = malloc(leng +1);
		strcpy(numberStr, buffer);
	}	
	else if(version->major > -1)
	{
		char* buffer[7];
		int leng = sprintf(buffer,"%d",version->major);
		numberStr = malloc(leng +1);
		strcpy(numberStr, buffer);
	}
	else
	{
		return NULL;
	}
	int numberLeng = strlen(numberStr);
	if(formato == OnlyNumber) 
	{
		free(numberStr);
		return numberStr;
	}

	const char* stageStr = octetos_Stage_getString(version->stage);	
	int stageLeng = strlen(stageStr) + 1;//se agrega la longitus de stage mas el espacio del guion

	const char* buildStr = NULL;
	int buildLeng = 0;
	if(version->build.type == ul_e)
	{
		char* buffer[15];
		buildLeng = sprintf(buffer,"%d",version->build.value.ul);
		buildStr = malloc(buildLeng+1);//la cadena mas el signo de '+'
		strcpy(buildStr, buffer);
	}
    else if(version->build.type == string_e)
	{
		buildStr = version->build.value.string;
		buildLeng = strlen(buildStr);
	}
	else
	{
		buildLeng = 0;
	}

	int verstrLeng = numberLeng + stageLeng + buildLeng + 1;
	const char* verstr = malloc(verstrLeng);
	strcpy(verstr,numberStr);
	strcat(verstr,"-");
	strcat(verstr,stageStr);
	if(version->build.type == ul_e)
	{
		strcat(verstr,"+");
		strcat(verstr,buildStr);
	}
	else if(version->build.type == string_e)
	{
		strcat(verstr,buildStr);
	}

	free(numberStr);
	if(version->build.type == ul_e) free(buildStr);
	
	return verstr;
}


