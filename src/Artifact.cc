#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

#include "config.h"
#include "Artifact.hh"

namespace octetos
{
namespace core
{
	bool Artifact::read(const std::string& file)
	{
  		libconfig::Config cfg;

	  	// Read the file. If there is an error, report it and exit.
	  	try
	  	{
			cfg.readFile(file.c_str());
	  	}
	  	catch(const libconfig::FileIOException &fioex)
	  	{
			return false;
	  	}
	  	catch(const libconfig::ParseException &pex)
	  	{
			return false;
	  	}

		/*try
  		{
    		std::string name = cfg.lookup("name");
  		}
  		catch(const libconfig::SettingNotFoundException &nfex)
  		{
			return false;
  		}*/
		
		const libconfig::Setting& root = cfg.getRoot();
		name = (const std::string&)root["package"]["name"];
		name_decorated = (const std::string&)root["package"]["name_decorated"];
		brief = (const std::string&)root["package"]["brief"];
		url = (const std::string&)root["package"]["url"];
		version.set(root["package"]["version"]);
		
		return false;
	}
	bool Artifact::write(const std::string& file)
	{
  		libconfig::Config cfg;
	  	libconfig::Setting &root = cfg.getRoot();		
	  	libconfig::Setting &package = root.add("package", libconfig::Setting::TypeGroup);

	  	package.add("name", libconfig::Setting::TypeString) = name;
	  	package.add("name_decorated", libconfig::Setting::TypeString) = name_decorated;
	  	package.add("brief", libconfig::Setting::TypeString) = brief;
	  	package.add("url", libconfig::Setting::TypeString) = url;
	  	package.add("version", libconfig::Setting::TypeString) = (std::string)version;
	  	if(!licence.write(package)) return false;
		
		try
		{
			cfg.writeFile(file.c_str());
		}
		catch(libconfig::FileIOException ex)
		{
			return false;
		}
		catch(libconfig::SettingTypeException ex)
		{
			return false;
		}
		
		
		return true;
	}
	/*Artifact getPackageInfo()
	{
		Artifact packinfo;
		getPackageInfo(packinfo);
		return packinfo;
	}*/
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
