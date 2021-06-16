
#include <openssl/md5.h>
#include <string.h>

#include "MD5sum.hh"


namespace oct::core
{

	//contructors
	MD5sum::MD5sum()
	{

	}
	MD5sum::MD5sum(const std::string& md5sum)
	{
		set(md5sum);
	}

	//operators
	const MD5sum& MD5sum::operator =(const MD5sum& m)
	{
		std::string::operator = (m);
		return *this;
	}	
	const MD5sum& MD5sum::operator =(const char* m)
	{
		set(m);
		return *this;
	}	
	const MD5sum& MD5sum::operator =(const std::string& m)
	{
		set(m);
		return *this;
	}

	//funtions
	void MD5sum::set(const std::string& s)
	{
		unsigned char digest[MD5_DIGEST_LENGTH];
    	char string[s.length()+1];
		strcpy(string,s.c_str());
    	MD5((unsigned char*)&string, strlen(string), (unsigned char*)&digest); 
    	char mdString[33]; 
    	for(int i = 0; i < 16; i++)
		{
			sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
		}
		
		std::string::operator = (mdString);
	}
	
	
	
}
