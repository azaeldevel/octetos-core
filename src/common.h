#ifndef OCTETOS_CORE_COMMON_H
#define OCTETOS_CORE_COMMON_H
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


/**
* \brief Paramaetro pasado a la funcion toString para determinar el formato de texto geneerado
* */
enum octetos_core_Semver_FormatString
{
	FullString,
	OnlyNumber
};
typedef short octetos_core_semver_Number;
/**
* \brief Informacion de version
* 
**/
struct octetos_core_Semver {
	octetos_core_semver_Number major;
	octetos_core_semver_Number minor;
	octetos_core_semver_Number patch;
	const char* prerelease;
	octetos_core_semver_Number prNumber;
	const char* build;
};

#ifdef __cplusplus  
extern "C" {
#endif 
	const char* octetos_core_Semver_toString(const struct octetos_core_Semver* version,enum octetos_core_Semver_FormatString);
	void octetos_core_Semver_init(struct octetos_core_Semver* version);
	const char* octetos_core_Semver_setPrerelease(struct octetos_core_Semver* version,const char*);
	const char* octetos_core_Semver_setBuild(struct octetos_core_Semver* version,const char*);	
#ifdef __cplusplus 
}
#endif

#endif
