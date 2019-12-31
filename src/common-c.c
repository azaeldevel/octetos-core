#include <stdio.h>

#include "common.h"

const char* octetos_Semver_setPrerelease(struct octetos_Semver* version,const char* prerelease)
{
	if(version->prerelease)
	{
		free((void*)version->prerelease);
	}
	const char* temp = prerelease;
	version->prerelease = (const char*)malloc(strlen(temp));
	strcpy((char*)version->prerelease,temp);
}
void octetos_Semver_init(struct octetos_Semver* version)
{
	version->major = -1;
	version->minor = -1;
	version->patch = -1;
	version->prerelease = NULL;
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

		
	int prereleaseLeng = strlen(version->prerelease);//se agrega la longitus de stage mas el espacio del guion

	int verstrLeng = numberLeng + prereleaseLeng + 2;//mas guion y terminalcion NULL
	const char* verstr = malloc(verstrLeng);
	strcpy(verstr,numberStr);
	strcat(verstr,"-");
	strcat(verstr,version->prerelease);

	free(numberStr);
	
	return verstr;
}


