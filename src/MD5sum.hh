#ifndef OCTETOS_CORE_MD5SUM
#define OCTETOS_CORE_MD5SUM

#include <string>


#include "defines.hh"

namespace oct::core
{

class MD5sum : public std::string
{
public:
	//contructors
	MD5sum();
	MD5sum(const std::string& md5sum);

	//operators
	const MD5sum& operator =(const MD5sum&);
	const MD5sum& operator =(const char* md5sum);
	const MD5sum& operator =(const std::string&);

	//funtions
	void set(const std::string& str);

};


}

namespace octetos::core
{
	typedef oct::core::MD5sum MD5sum DEPRECATED;
}

#endif