/**
 *
 *  This file is part of octetos-core.
 *  octetos-core is a core C/C++ Octeto's library.
 *  Copyright (C) 2018  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"


void octetos_core_Semver_init(struct octetos_core_Semver* version)
{
	version->major = -1;
	version->minor = -1;
	version->patch = -1;
	version->prerelease = NULL;
	version->build = NULL;
}
const char* octetos_core_Semver_setBuild(struct octetos_core_Semver* version, const char* build)
{
	if (build)//si el parametro es un puntero valido
	{
		if (version->build)free((void*)version->build);//si hay datos escritos actualmente en el contenedor
		version->build = (const char*)malloc(strlen(build) + 1);
		strcpy((char*)version->build, build);
	}

	return version->build;
}
const char* octetos_core_Semver_setPrerelease(struct octetos_core_Semver* version, const char* prerelease)
{
	if (prerelease) free((void*)version->prerelease);//si el parametro es un puntero valido
	
	//si hay datos escritos actualmente en el contenedor
	version->prerelease = (const char*)malloc(strlen(prerelease) + 1);
	strcpy((char*)version->prerelease, prerelease);
	
	return version->prerelease;
}

const char* octetos_core_Semver_toString(const struct octetos_core_Semver* version, enum octetos_core_Semver_FormatString formato)
{
	char* numberStr = NULL;
	unsigned int buffer_leng = 20;
	char* buffer = NULL;
	if (version->major > -1 && version->minor > -1 && version->patch > -1)
	{
		buffer = malloc(buffer_leng);
		int leng = sprintf(buffer, "%d.%d.%d", version->major, version->minor, version->patch);
		numberStr = malloc(leng + 1);
		strcpy(numberStr, buffer);
	}
	else if (version->major > -1 && version->minor > -1)
	{
		buffer = malloc(buffer_leng);
		int leng = sprintf(buffer, "%d.%d", version->major, version->minor);
		numberStr = malloc(leng + 1);
		strcpy(numberStr, buffer);
	}
	else if (version->major > -1)
	{
		buffer = malloc(buffer_leng);
		int leng = sprintf(buffer, "%d", version->major);
		numberStr = malloc(leng + 1);
		strcpy(numberStr, buffer);
	}
	else
	{
		return NULL;
	}
	free(buffer);
	int numberLeng = strlen(numberStr);
	if (formato == OnlyNumber)
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
	strcpy(verstr, numberStr);
	if (prereleaseLeng > 0)
	{
		strcat(verstr, "-");
		strcat(verstr, (char*)version->prerelease);
	}
	if (buildLeng > 0)
	{
		strcat(verstr, "+");
		strcat(verstr, (char*)version->build);
	}

	free((void*)numberStr);

	return verstr;
}
