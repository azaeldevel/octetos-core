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
#include <iostream> //test


#include "Error.hh"


namespace octetos
{
namespace core
{	
	const Error* Error::see()
	{
		return error;
	}
	Error::operator const std::string&()
	{
		return full;
	}
	const Error* Error::error = NULL;
        
        Error Error::get()
        {
                if(error != NULL)
                {
                        Error e(*error);
                        delete error;
                        error = NULL;
                        return e;
                }
                else
                {
                        return Error("Usted llamo a Error::get sin que haya error,",ERROR_NOTERROR);                        
                }
        }
        bool Error::check()
        {
                if(error != NULL)return true;
                else return false;
        }
        bool Error::write(const Error& e)
        {                
                if(error != NULL)
                {
                        return false;
                }
                error = new Error(e);
                return true;
        }
	Error::Error(const Error& e) throw()
	{
		full = e.full;
		code = e.code;
	}
	Error::Error(const std::string& brief, int code,std::string filename,int lineNumber) throw()
	{
		full = filename + " : " + std::to_string(lineNumber) + ", Codigo (" + std::to_string(code) + "):" + "\n" + brief;
		this->code = code;
	}
	Error::Error(const std::string& brief) throw()
	{
		full = brief;
		this->code = Codes::NOTCODED;
	}
	Error::Error(const std::string& brief, int code) throw()
	{
		full = "Codigo (" + std::to_string(code) + "):" + "\n" + brief;
		this->code = code;
	}
	Error::~Error() throw()
	{
	}	
	const std::string& Error::describe() const throw()
   	{
		return full;               
	}
	const char* Error::what() const throw()
	{
		return this->full.c_str();
	}
	int Error::getCode()const
	{
		return code;
	}
        
}
}
