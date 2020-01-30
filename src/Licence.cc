#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

#include "Licence.hh"

namespace octetos
{
namespace core
{
	bool Licence::write(libconfig::Setting &root)
	{
		libconfig::Setting &lc = root.add("licence", libconfig::Setting::TypeGroup);
		switch(type)
		{
			case Type::GPL:
				lc.add("type", libconfig::Setting::TypeString) = "GPL";
				break;
			case Type::GPLv1:
				lc.add("type", libconfig::Setting::TypeString) = "GPLv1";
				break;
			case Type::GPLv2:
				lc.add("type", libconfig::Setting::TypeString) = "GPLv2";
				break;
			case Type::GPLv3:
				lc.add("type", libconfig::Setting::TypeString) = "GPLv3";
				break;
			case Type::LGPL:
				lc.add("type", libconfig::Setting::TypeString) = "LGPL";
				break;
			default:
				return false;
		}
		lc.add("owner", libconfig::Setting::TypeString) = owner;
		lc.add("name_public", libconfig::Setting::TypeString) = name_public;
		lc.add("year", libconfig::Setting::TypeInt) = year;
		lc.add("contact", libconfig::Setting::TypeString) = contact;
		
		return true;
	}
	
	std::string Licence::getText()const
	{
		std::string brief;
		if(type >= Type::GPL or type <= Type::LGPL)
		{
			if(!name_public.empty()) brief += name_public + " ";		
			brief += "Copyright (C) ";
			if(year > 0) brief += std::to_string(year) + " ";
			if(!owner.empty()) brief += owner;
			brief += "\nThis program comes with ABSOLUTELY NO WARRANTY.";
		}
		
		
		return brief;
	}
	
	
	
	
}
}
