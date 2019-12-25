


#include "config.h"
#include "common.hh"
	

namespace octetos
{
namespace core
{
	Version getPakageVersion()
	{
		Version v;
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
		
		//packinfo.version.setNumbers(0,0,0);
		//packinfo.version.setStage(Version::Stage::alpha);
		//packinfo.version.setBuild(std::stoul(VERSION_BUILD));
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
