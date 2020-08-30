/**
 * 
 *  This file is part of octetos-core.
 *  octetos-core is a core C/C++ Octeto's library.
 *  Copyright (C) 2018  Azael Reyes
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * */
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "Artifact.hh"
#include "Error.hh"


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
			std::string msg = fioex.what();
#ifdef DEBUG
			Error::write(Error(msg,errno,__FILE__,__LINE__));
#else
			Error::write(Error(msg,errno));
#endif
			return false;
	  	}
	  	catch(const libconfig::ParseException &pex)
	  	{	
			std::string msg = pex.what();
#ifdef DEBUG
			Error::write(Error(msg,Error::Codes::ERROR_ARTIFACT,__FILE__,__LINE__));
#else
			Error::write(Error(msg,Error::Codes::ERROR_ARTIFACT));
#endif
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
		
		return true;
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
			std::string msg = ex.what();
#ifdef DEBUG
			octetos::core::Error::write(octetos::core::Error(msg,Error::Codes::ERROR_ARTIFACT,__FILE__,__LINE__));
#else
			octetos::core::Error::write(octetos::core::Error(msg,Error::Codes::ERROR_ARTIFACT));
#endif
			return false;
		}
		catch(libconfig::SettingTypeException ex)
		{
			std::string msg = ex.what();
#ifdef DEBUG
			Error::write(Error(msg,Error::Codes::ERROR_ARTIFACT,__FILE__,__LINE__));
#else
			Error::write(Error(msg,Error::Codes::ERROR_ARTIFACT));
#endif
			return false;
		}
		
		
		return true;
	}

	
	bool getPackageInfo(Artifact& packinfo)
	{
		packinfo.name = PACKAGE;
		packinfo.brief = "Libreria Core de Octetos.";
		packinfo.url = "https://github.com/azaeldevel/octetos-core.git";
		packinfo.name_decorated = "Libreria Core de Octetos";
		
		packinfo.version.set(VERSION);
		
		packinfo.licence.type = Licence::Type::GPLv3;		
		packinfo.licence.name_public = PACKAGE;
		packinfo.licence.owner = "Azael Reyes";
		packinfo.licence.year = 2019;
        packinfo.licence.contact = "azael.devel@gmail.com";
		
		return true;	
	}
}
}
