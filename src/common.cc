


#include "config.h"
#include "common.hh"
	

namespace octetos
{
namespace core
{
	Semver getPakageVersion()
	{
		Semver v;
		v.set(VERSION);
		return v;		
	}

	std::string getPakageName()
	{
		return PACKAGE;
	}
	
	Artifact getPackageInfo()
	{
		Artifact packinfo;
		
		packinfo.name = PACKAGE;
		packinfo.brief = "";
		packinfo.url = "";
		
		packinfo.version.set(VERSION);
		
		packinfo.licence.type = Licence::Type::GPL;		
		packinfo.licence.name_public = packinfo.name;
		packinfo.licence.owner = "Azael Reyes";
		packinfo.licence.year = 2019;
        packinfo.licence.contact = "azael.devel@gmail.com";
		return packinfo;	
	}
}
}
