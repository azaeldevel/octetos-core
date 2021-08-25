#ifndef OCTETOS_CORE_EXECPTION_HH
#define OCTETOS_CORE_EXECPTION_HH

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

namespace oct::core
{

class DECLSPCE_DLL Exception : public std::exception
{
protected:
    int line;
    const char* filename;
    std::string message;
    std::string text;
	
public:
	Exception();
    Exception(const char* fn,int line, const std::string& msg);
    Exception(const std::string& msg,const char* fn,int line);
    Exception(const std::string& msg);

	//getter
	const std::string& getMessage()const;
	const char* getFilename()const;
	int getLine()const;

	//functions
    virtual const char* what () const throw ();
};



}

namespace octetos::core
{
	typedef oct::core::Exception Exception DEPRECATED;
}

#endif
