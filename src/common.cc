


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
		packinfo.brief = "Libreria Core de Octetos.";
		packinfo.url = "https://github.com/azaeldevel/octetos-core.git";
		
		packinfo.version.set(VERSION);
		
		packinfo.licence.type = Licence::Type::GPL;		
		packinfo.licence.name_public = PACKAGE;
		packinfo.licence.owner = "Azael Reyes";
		packinfo.licence.year = 2019;
        packinfo.licence.contact = "azael.devel@gmail.com";
		return packinfo;	
	}
}
}
