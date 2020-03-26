#ifndef OCTETOS_CORE_SEMVER_PARSER_H
#define OCTETOS_CORE_SEMVER_PARSER_H
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


#include "common.h"

struct octetos_core_Tray
{
	struct octetos_core_Semver* version;
    int dysplay_erro;
	void* buffer;
	const char* str;
	int state;
};

#ifdef __cplusplus  
extern "C" {
#endif 
    int parse_string(struct octetos_core_Tray* ty);
#ifdef __cplusplus 
} 
#endif

#endif

 
