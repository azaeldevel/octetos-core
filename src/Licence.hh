#ifndef OCTETOS_CORE_LICENCE_HH
#define OCTETOS_CORE_LICENCE_HH

#include "Version.hh"


namespace octetos
{
namespace core
{
	class Licence : public Object
	{
	public:
		enum Type
		{
			GPL,
            GPLv2,
            GPLv3,
			LGPL
		};
		
		Type type;
		short year;
		std::string owner;
		std::string name_public;
        std::string contact;
		
		std::string getBrief() const;
	};
	
}
}

#endif
