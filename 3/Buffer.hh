

#ifndef OCTETOS_CORE_BUFFER_V3_HH
#define OCTETOS_CORE_BUFFER_V3_HH


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


/*
 * Copyright (C) 2022 Azael Reyes Martinez. <azael.devel@gmail.com>
 * All rights reserved
 */


#include <filesystem>
#include <list>
#include <fstream>
#include <iostream>
#include <concepts>

#include "Exception.hh"



namespace oct::core::v3
{

template<typename T> concept CHAR = std::same_as<char, T> || std::same_as<wchar_t,T>;

template<CHAR C> constexpr size_t strlen(const C* str)
{
	if(not str) return 0;
	size_t i = 0;
	while(str[i] != C(0))
	{
		i++;
	}
	return i;
}

template<CHAR C> constexpr size_t copy(const C* origin, size_t leng,C*& dest)
{
	if(not origin) return 0;
	if(not dest) return 0;
	if(origin[leng] != (C)0) return 0;

	for(size_t i = 0;i < leng; i++)
	{
		dest[i] = origin[i];
		//std::cout << "C : " << (*dest)[i] << "\n";
	}
	dest[leng] = (C)0;

	return leng;
}


/**
*\brief
*
*/
template<typename T>
class Buffer
{
public:
	static const T EOB = T(0);

public:
	Buffer(const std::filesystem::path& file)
	{
		if(not std::filesystem::exists(file)) throw exception("Not found the file to load on Buffer");

		_size = std::filesystem::file_size(file);
		if(_size == 0) return;
		//std::cout << "Buffer size : " << _size << "\n";

		buffer = new T[_size + 1];
		std::ifstream ifs(file, std::ifstream::binary);

		std::filebuf* pbuf;
		std::ifstream sfile;
		pbuf = ifs.rdbuf();
		pbuf->sgetn (buffer,_size);
		//std::cout << "Buffer content : >>" << buffer << "<<\n";

		if (sfile.is_open()) sfile.close();
	}
	Buffer(const T* string) : _size(v3::strlen(string)),buffer(new T[_size + 1])
	{
		//std::cout << "Sieze : " << _size << "\n";
		if(_size > 0) v3::copy(string, _size, buffer);
	}
	~Buffer()
	{
		if(buffer) delete[] buffer;
	}
	operator const T*()const
	{
		return buffer;
	}
	operator T*()
	{
		return buffer;
	}
	T operator[](uintmax_t i)const
	{
		//std::cout << "if(" << i << " < " << _size << ") return " << int(buffer[i]) << "\n";
		if(i < _size) return buffer[i];

		return T(0);
	}
	std::uintmax_t size() const
	{
		return _size;
	}

protected:
	std::uintmax_t _size;
	T* buffer;
};


}

#endif
