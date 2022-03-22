
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
 
 
#include "Exception.hh"

namespace oct::v3
{
Exception::Exception() : _code(0),_filename(NULL),_line(0)
{
}
Exception::Exception(unsigned int c) : _code(c),_filename(NULL),_line(0)
{
}
Exception::Exception(unsigned int c,const char* fn, unsigned int l) : _code(c),_filename(fn),_line(l)
{
}

unsigned int Exception::code()const
{
	return _code;
}
const char* Exception::filename()const
{
	return _filename;
}
unsigned int Exception::line()const
{
	return _line;
}
const char* Exception::subject()const
{
	return _subject;
}
	
std::string Exception::describe() const throw ()
{
	if(not _subject) return what();
	
	std::string msg = what();
	msg += "\n\t devido a ";
	msg += _subject;
	return msg;
}


}



namespace oct::core::v2
{
	
	Exception::Exception()
	{

	}
    Exception::Exception(const std::string& msg)
    {
        filename = NULL;
        line = 0;
		message = msg;
        text = msg;
    }
    Exception::Exception(const char* fn,int l, const std::string& msg)
    {
        filename = fn;
        line = l;
		message = msg;
        text = filename;
        text = text + " : "+ std::to_string(line) + " -> " + msg;
    }
	Exception::Exception( const std::string& msg,const char* fn,int l)
    {
        filename = fn;
        line = l;
		message = msg;
        text = filename;
        text = text + " : "+ std::to_string(line) + " -> " + msg;
    }

	
	//getter
	const std::string& Exception::getMessage()const
	{
		return message;
	}
	const char* Exception::getFilename()const
	{
		return filename;
	}
	int Exception::getLine()const
	{
		return line;
	}

	//functions
    const char* Exception::what () const throw ()
    {
        return text.c_str();
    }



    InternalException::InternalException() : filename(NULL),line(-1),code(-1)
    {    
    }    
    InternalException::InternalException(int c) : filename(NULL),line(-1),code(c)
    {
    
    }
    InternalException::InternalException(int c,const char* fn,int l) : filename(fn),line(l),code(c)
    {
    
    }
}