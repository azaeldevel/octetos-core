

#ifndef OCTETOS_CORE_BUFFER_V3_HH
#define OCTETOS_CORE_BUFFER_V3_HH


/*
 * Copyright (C) 2022 Azael Reyes Martinez. <azael.devel@gmail.com>
 * All rights reserved
 */


#include <filesystem>
#include <list>
#include <fstream>
#include <iostream>

#include "Exception-v3.hh"



namespace oct::core::v3
{


template<typename C> size_t length(const C* str)
{
	if(not str) return 0;
	size_t i = 0;
	while(str[i] != (C)0)
	{
		i++;
	}
	return i;
}

template<typename C> size_t copy(const C* origin, size_t leng,C** dest)
{
	if(origin[leng] != (C)0) return 0;
	if(not origin) return 0;
	if(not dest) return 0;
	
	size_t i = 0;
	for(;i < leng; i++)
	{
		(*dest)[i] = origin[i];
		//std::cout << "C : " << (*dest)[i] << "\n";
	}
	(*dest)[leng] = (C)0;

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
	
	class Exception : public v3::Exception
	{
	public:

	public:
		Exception()
		{
		}
		Exception(const Exception& e) : v3::Exception(e)
		{
		}

		//>>>pereferecia
		Exception(const char* s) : v3::Exception(s)
		{
		}
		Exception(const char* m,const char* fn, unsigned int l) : v3::Exception(m,fn,l)
		{
		}
		
		virtual ~Exception()
		{
		}
		
		
		virtual const char* what() const throw ()
		{	
			return _message;
		}

	protected:
		
	private:

	};

public:
	Buffer(const std::filesystem::path& file)
	{
		if(not std::filesystem::exists(file)) throw Exception("Not found the file to load on Buffer",__FILE__,__LINE__);

		_size = std::filesystem::file_size(file);
		if(_size == 0) return;

		buffer = new T[_size + 1];

		std::ifstream ifs(file, std::ifstream::binary);
		pbuf = ifs.rdbuf();
		pbuf->sgetn (buffer,_size);
	}
	Buffer(const T* string)
	{
		_size = length(string);
		if(_size > 0)
		{
			buffer = new T[_size + 1];
			copy(string,_size,&buffer);
		}
		else
		{
			buffer = NULL;
		}
	}
	~Buffer()
	{
		if(sfile.is_open()) sfile.close();
		if(buffer) delete[] buffer;
	}
	explicit operator const T*()const
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
	T* buffer;
	std::uintmax_t _size;
	std::filebuf* pbuf;
	std::ifstream sfile;
};


}

#endif