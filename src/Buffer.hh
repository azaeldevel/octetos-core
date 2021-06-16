#ifndef OCTETOS_CORE_BUFFER_HH
#define OCTETOS_CORE_BUFFER_HH

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




#include "defines.hh"

namespace oct::core
{

class DECLSPCE_DLL Buffer
{
private:
	char* buffer1;
	char* buffer2;
	short begin;
	short forward;
	short bsize;
	char* text;
public:
	Buffer(const char*);
	/**
	*\brief Avanca un caracter al centinela
	*/
	char next_char();
	/**
	*\brief Retucede un caracter al centinela
	*/
	void prev_char();
	char check_char(short);
	void proceed();
	void back();
	const char* get_text() const;
};


}


namespace octetos::core
{
	typedef oct::core::Buffer Buffer DEPRECATED;
}

#endif
