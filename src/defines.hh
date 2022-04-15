#ifndef OCTETOS_CORE_DEFINES_HH_INCLUDED
#define OCTETOS_CORE_DEFINES_HH_INCLUDED

/**
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
 * */

#if EXPORTING_OCTETOS_CORE_DLL
	#if _MSC_VER
		#define DECLSPCE_DLL_OCTETOS_CORE __declspec(dllexport)
	#elif __GNUG__

	#endif
#elif IMPORTING_OCTETOS_CORE_DLL
	#if _MSC_VER
		#define DECLSPCE_DLL_OCTETOS_CORE __declspec(dllimport)
	#elif __GNUG__

	#endif
#else
	#define DECLSPCE_DLL_OCTETOS_CORE
#endif


#define ALPHA_PHASE_ATTRIBUTE "Not use yet, alpha phase"

#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

#endif