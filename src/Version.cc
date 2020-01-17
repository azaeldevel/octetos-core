#include "config.h"

#include "Version.hh"
#include "Error.hh"


namespace octetos
{
namespace core
{

	InvalidComparison::InvalidComparison(const std::string& msg):Error(msg,Error::ERROR_VERSION_INVALID_COMPARISON)
	{
	}
	InvalidComparison::InvalidComparison(const std::string& msg ,std::string filename,int lineNumber):Error(msg,Error::ERROR_VERSION_INVALID_COMPARISON,filename,lineNumber)
	{
	}

	
	Semver getPakageVersion()
	{
		Semver v;
		v.set(VERSION);
		return v;		
	}

}
}
