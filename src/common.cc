

#ifdef ENABLED_CMAKE
	#include "packInfo.hpp"
#endif
#ifdef ENABLED_AUTOTOOLS
	#include "config.h"
#endif
#include "common.hh"
	

namespace octetos
{
namespace core
{
	Version getPakageVersion()
	{
		Version v;
		#ifdef ENABLED_CMAKE
		v.setNumbers(VERSION_MAJOR,VERSION_MINOR,VERSION_PATCH);
		v.setStage(VERSION_STAGE);
		v.setBuild(std::stoul(VERSION_BUILD));
		#elif defined ENABLED_AUTOTOOLS
		v.set(VERSION);
		//v.setStage(octetos::toolkit::Version::Stage::alpha);
		//v.setBuild(std::stoul(VERSION_BUILD));
		#endif
		return v;		
	}

	std::string getPakageName()
	{
        	#ifdef ENABLED_CMAKE
        	return PACKAGE_NAME;
		#elif defined ENABLED_AUTOTOOLS
		return PACKAGE;
        	#endif
	}
	
	Artifact getPackageInfo()
	{
		Artifact packinfo;
		
		#ifdef ENABLED_CMAKE
		packinfo.name = PACKAGE_NAME;
		packinfo.brief = PACKAGE_BRIEF;
		//packinfo.url = PACKAGE_URL;
		
		packinfo.version.setNumbers(VERSION_MAJOR,VERSION_MINOR,VERSION_PATCH);
		packinfo.version.setStage(VERSION_STAGE);
		packinfo.version.setBuild(std::stoul(VERSION_BUILD));
		
		packinfo.licence.type = Licence::Type::GPL;		
		packinfo.licence.name_public = packinfo.name;
		packinfo.licence.owner = "Azael Reyes";
		packinfo.licence.year = 2018;
        packinfo.licence.contact = "azael.devel@gmail.com";
		#elif defined ENABLED_AUTOTOOLS
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
		packinfo.licence.year = 2018;
        packinfo.licence.contact = "azael.devel@gmail.com";
		#endif
		return packinfo;	
	}
}
}
