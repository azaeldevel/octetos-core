
#include "config.h"
#include "Artifact.hh"

namespace octetos
{
namespace core
{
	Artifact getPackageInfo()
	{
		Artifact packinfo;
		getPackageInfo(packinfo);
		return packinfo;
	}
	bool getPackageInfo(Artifact& packinfo)
	{
		packinfo.name = PACKAGE;
		packinfo.brief = "Libreria Core de Octetos.";
		packinfo.url = "https://github.com/azaeldevel/octetos-core.git";
		packinfo.name_decorated = "Libreria Core de Octetos";
		
		packinfo.version.set(VERSION);
		
		packinfo.licence.type = Licence::Type::GPL;		
		packinfo.licence.name_public = PACKAGE;
		packinfo.licence.owner = "Azael Reyes";
		packinfo.licence.year = 2019;
        packinfo.licence.contact = "azael.devel@gmail.com";
		
		return true;	
	}
}
}
