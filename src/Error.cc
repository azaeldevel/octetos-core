#include <string.h>
#include <iostream> //test


#include "Error.hh"


namespace octetos
{
namespace core
{	
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
