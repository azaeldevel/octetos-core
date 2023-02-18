
#ifndef OCTETOS_CORE_EXCEPTION_V3_HH
#define OCTETOS_CORE_EXCEPTION_V3_HH

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
#include <source_location>

#include "core.hh"

namespace oct::core::v3
{

class OCTETOS_CORE_DECLSPCE_DLL Exception : public std::exception
{
public:
	typedef unsigned int Code;

public:
	Exception()noexcept;
	Exception(const Exception&)noexcept;
	Exception(Exception&&) noexcept;

	Exception(unsigned int code)noexcept;
	Exception(unsigned int code,const char* filename, unsigned int line)noexcept;

	Exception(unsigned int code,const char* message)noexcept;
	Exception(unsigned int code,const char* message,const char* filename, unsigned int line)noexcept;

	Exception(const std::string& message)noexcept;
	Exception(const std::string& message,const char* filename, unsigned int line)noexcept;

	Exception(unsigned int code,const std::string& message)noexcept;
	Exception(unsigned int code,const std::string& message,const char* filename, unsigned int line)noexcept;
	//>>>pereferecia
	Exception(const char* message)noexcept;
	Exception(const char* message,const char* filename, unsigned int line)noexcept;

	virtual ~Exception()noexcept;

	unsigned int code()const;
	const char* filename()const;
	unsigned int line()const;
	const char* subject()const;

	//virtual const char* what() const noexcept;
	virtual std::string describe() const noexcept;

protected:
	unsigned int _code;
	const char* _filename;
	unsigned int _line;
	const char* _message;
private:
	bool autofree;
	void copy(const std::string&);
	void copy(const char*);
};

class exception : public std::exception
{
public:
	typedef int errono;
	static const errono err_none = 0;

public:
	exception(const exception&)noexcept = default;
	exception(exception&&) noexcept = default;


	exception(const std::source_location& location = std::source_location::current())noexcept : _code(err_none), _code_flag(false), _location(location)
	{
	}
	exception(errono code, const std::source_location& location = std::source_location::current())noexcept : _code(code), _code_flag(true), _location(location)
	{
	}
	exception(errono code, const std::string& message, const std::source_location& location = std::source_location::current())noexcept : _code(code), _code_flag(true), _message(message), _location(location)
	{
	}
	exception(const std::string& message, const std::source_location& location = std::source_location::current())noexcept : _code(err_none), _code_flag(false), _message(message), _location(location)
	{
	}
	virtual ~exception()noexcept
	{
	}

	inline errono code()const
	{
		return _code;
	}

	virtual const char* what() const noexcept
	{
		if (description.empty())
		{
			description = _location.file_name();
			description += ":";
			description += std::to_string(_location.line()) + " ";
			if (_code_flag) description += "- " + std::to_string(_code);
			if (not _message.empty()) description += "\n\t" + _message;
		}

		return description.c_str();
	}

protected:
	errono _code;
	bool _code_flag;
	std::string _message;
	std::source_location _location;

private:
	mutable std::string description;
};


}

#endif
