
#ifndef OCTETOS_CORE_EXECPTION_V3_HH
#define OCTETOS_CORE_EXECPTION_V3_HH

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

#include <exception>
#include "core.hh"

namespace oct::core::v3
{
class Exception : public std::exception
{
public:
	Exception();
	Exception(unsigned int code);
	Exception(unsigned int code,const char* subject);
	Exception(unsigned int code,const char* filename, unsigned int line);
	Exception(unsigned int code,const char* filename, unsigned int line,const char* subject);
	
	unsigned int code()const;
	const char* filename()const;
	unsigned int line()const;
	const char* subject()const;

	virtual std::string describe() const throw ();

protected:
	unsigned int _code;
	const char* _filename;
	unsigned int _line;
	const char* _subject;
};
}

#endif