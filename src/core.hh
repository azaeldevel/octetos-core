
#ifndef OCTETOS_CORE_CORE_HH
#define OCTETOS_CORE_CORE_HH

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

#include <string>
#include <concepts>
#if defined(__linux__)
	#include <execinfo.h>
	#include <csignal>
	#include "defines.hh"
#elif defined(_WIN32) || defined(_WIN64)
	#include <core/src/defines.hh>
#else
	#error "Plataforma desconocida"
#endif


namespace oct
{

#if defined(__linux__)
    void print_backtrace(const char* msg,int code);
	void signal_exception(int s);
	void signal_abort(int s);
	void signal_segmentv(int s);
#elif defined(_WIN32) || defined(_WIN64)

#else
    #error "Plataforma desconocida"
#endif

typedef unsigned long long int Word;//deve coincidir con los bits de la plataforma

}
namespace oct::core::v2
{
	/**
	*\brief Genera un numero para identificar la hora
	*/
	OCTETOS_CORE_DECLSPCE_DLL unsigned int getTimeID();
	/**
	*\brief Genera un numero para identificar el dia
	*/
	OCTETOS_CORE_DECLSPCE_DLL unsigned int getDayID();

	/**
	*\brief Genera un numero al azar entre (0,1]
	*/
	OCTETOS_CORE_DECLSPCE_DLL double randNumber();
	/**
	*\brief Genera un numero al azar entre (0,max]
	*/
	OCTETOS_CORE_DECLSPCE_DLL double randNumber(double max);
	/**
	*\brief Genera un numero al azar entre (min,max]
	*/
	OCTETOS_CORE_DECLSPCE_DLL double randNumber(double min, double max);

}

namespace oct::core
{
	//using namespace oct::core::v2;
}



#endif
