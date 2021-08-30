
#include <openssl/md5.h>
#include <string.h>

#include "MD5sum.hh"


namespace oct::core
{

	//contructors
	StringMD5::StringMD5()
	{

	}
	StringMD5::StringMD5(const std::string& md5sum)
	{
		set(md5sum);
	}

	//operators
	const StringMD5& StringMD5::operator =(const StringMD5& m)
	{
		std::string::operator = (m);
		return *this;
	}	
	const StringMD5& StringMD5::operator =(const char* m)
	{
		set(m);
		return *this;
	}	
	const StringMD5& StringMD5::operator =(const std::string& m)
	{
		set(m);
		return *this;
	}

	//funtions
	void StringMD5::set(const std::string& s)
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
