#ifndef OCTETOS_CORE_MD5SUM
#define OCTETOS_CORE_MD5SUM

#include <string>


#include "defines.hh"

namespace oct::core
{

class StringMD5 : public std::string
{
public:
	//contructors
	StringMD5();
	StringMD5(const std::string& md5sum);

	//operators
	const StringMD5& operator =(const StringMD5&);
	const StringMD5& operator =(const char* md5sum);
	const StringMD5& operator =(const std::string&);

	//funtions
	void set(const std::string& str);

};

}

namespace octetos::core
{
	typedef oct::core::StringMD5 MD5sum DEPRECATED;
}


#endif