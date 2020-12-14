
#include "Exception.hh"


namespace octetos
{
namespace core
{
	Exception::Exception()
    {
    }	
    Exception::Exception(const std::string& msg)
    {
        filename = NULL;
        line = 0;
		message = msg;
        text = msg;
    }
    Exception::Exception(const char* fn,int l, const std::string& msg)
    {
        filename = fn;
        line = l;
		message = msg;
        text = filename;
        text = text + " : "+ std::to_string(line) + " -> " + msg;
    }
	Exception::Exception( const std::string& msg,const char* fn,int l)
    {
        filename = fn;
        line = l;
		message = msg;
        text = filename;
        text = text + " : "+ std::to_string(line) + " -> " + msg;
    }
    const char* Exception::what () const throw ()
    {
        return text.c_str();
    }

}
}