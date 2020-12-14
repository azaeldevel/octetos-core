
#include "Exception.hh"


namespace octetos
{
namespace core
{

    Exception::Exception(const char* fn,int l, const std::string& msg)
    {
        filename = fn;
        line = l;
        message = filename;
        message = message + " : "+ std::to_string(line) + " -> " + msg;
    }
	Exception::Exception( const std::string& msg,const char* fn,int l)
    {
        filename = fn;
        line = l;
        message = filename;
        message = message + " : "+ std::to_string(line) + " -> " + msg;
    }
    const char* Exception::what () const throw ()
    {
        return message.c_str();
    }

}
}