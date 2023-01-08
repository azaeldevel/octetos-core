
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
 

#include <string.h>
#include <glibmm/i18n.h>

#include "Exception-v3.hh"

namespace oct::core::v3
{
	

Exception::Exception() : _code(0),_filename(NULL),_line(0),_message(NULL),autofree(false)
{
}
Exception::Exception(const Exception& e) : _code(e._code),_filename(e._filename),_line(e._line),autofree(e.autofree)
{
	if(autofree) copy(e._message);
}
Exception::Exception(Exception&& e) : _code(e._code),_filename(e._filename),_line(e._line),_message(e._message),autofree(e.autofree)
{
	e._message = NULL;
	e.autofree = false;
}


Exception::Exception(unsigned int c) : _code(c),_filename(NULL),_line(0),_message(NULL),autofree(false)
{
}
Exception::Exception(unsigned int c,const char* fn, unsigned int l) : _code(c),_filename(fn),_line(l),_message(NULL),autofree(false)
{
}

Exception::Exception(unsigned int c,const char* s) : _code(c),_message(s),_filename(NULL),_line(0),autofree(false)
{
}
Exception::Exception(unsigned int c,const char* s,const char* fn, unsigned int l) : _code(c),_message(s),_filename(fn),_line(l),autofree(false)
{
}

Exception::Exception(const std::string& m) : _code(0),_filename(NULL),_line(0),autofree(true)
{
	copy(m);
}
Exception::Exception(const std::string& m,const char* f, unsigned int l) : _code(0),_filename(f),_line(l),autofree(true)
{
	copy(m);
}

Exception::Exception(unsigned int c,const std::string& m) : _code(c),_filename(NULL),_line(0),autofree(true)
{
	copy(m);
}
Exception::Exception(unsigned int c,const std::string& m,const char* f, unsigned int l) : _code(c),_filename(f),_line(l),autofree(true)
{
	copy(m);
}

Exception::~Exception()
{
	if(autofree) if(_message) delete _message;
}

void Exception::copy(const std::string& m)
{
	char* msg = new char[m.size() + 1];
	strcpy(msg,m.c_str());
	_message = msg;
}
void Exception::copy(const char* m)
{
	char* msg = new char[strlen(m) + 1];
	strcpy(msg,m);
	_message = msg;
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
	return _message;
}
	
const char* Exception::what() const throw ()
{
	return _("Unknow error.");
}
std::string Exception::describe() const throw ()
{	
	std::string msg;
	if(_filename)
	{
		msg += _filename;
		msg += ":";
		msg += std::to_string(_line);
	}
	if(_code > 0)
	{
		msg += " - Codigo " + std::to_string(_code) ;
	}
	if(_message)
	{
		msg += "\n\t";
		msg += _message;
	}
	else if(_code > 0)
	{
		msg += "\n\t";
		msg += this->what();
	}
	
	return msg;
}


}


