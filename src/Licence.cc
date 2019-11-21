
#include "Licence.hh"

namespace octetos
{
namespace core
{
	
	std::string Licence::getBrief()const
	{
		std::string brief;
		if(type == Type::GPL)
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
