#ifndef OCTETOS_CORE_MD5SUM
#define OCTETOS_CORE_MD5SUM

#include <string>

namespace octetos::core
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

	//funtions
	void set(const std::string& str);

};


}

#endif