#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "common.h"

const char* octetos_core_Semver_setBuild(struct octetos_core_Semver* version,const char* build)
{
	if(version->build)
	{
		free((void*)version->build);
	}
	if(build)
	{
		version->build = (const char*)malloc(strlen(build));
		strcpy((char*)version->build,build);
	}
	
	return version->build;
}
const char* octetos_core_Semver_setPrerelease(struct octetos_core_Semver* version,const char* prerelease)
{
	if(version->prerelease)
	{
		free((void*)version->prerelease);
	}
	if(prerelease)
	{
		version->prerelease = (const char*)malloc(strlen(prerelease));
		strcpy((char*)version->prerelease,prerelease);
	}
	
	return version->prerelease;
}
void octetos_core_Semver_init(struct octetos_core_Semver* version)
{
	version->major = -1;
	version->minor = -1;
	version->patch = -1;
	version->prerelease = NULL;
	version->build = NULL;
}

const char* octetos_core_Semver_toString(const struct octetos_core_Semver* version,enum octetos_core_Semver_FormatString formato)
{
	char* numberStr  = NULL;	
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
		free((void*)numberStr);
		return numberStr;
	}
		
	int prereleaseLeng = version->prerelease ? strlen(version->prerelease) : 0;//se agrega la longitus de stage mas el espacio del guion
	int buildLeng = version->build ? strlen(version->build) : 0;

	int verstrLeng = numberLeng + prereleaseLeng + 1;//terminalcion NULL
	verstrLeng += version->prerelease ? 1 : 0;//mas guion
	verstrLeng += version->build ? 1 : 0;// mas '+'

	char* verstr = malloc(verstrLeng);
	strcpy(verstr,numberStr);
	if(prereleaseLeng > 0)
	{
		strcat(verstr,"-");
		strcat(verstr,(char*)version->prerelease);
	}
	if(buildLeng > 0)
	{
		strcat(verstr,"+");
		strcat(verstr,(char*)version->build);
	}

	free((void*)numberStr);

	return verstr;
}


