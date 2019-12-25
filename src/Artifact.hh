#ifndef TOOLKIT_COMMON_PACKAGE
#define TOOLKIT_COMMON_PACKAGE

#include "Version.hh"
#include "Licence.hh"

namespace octetos
{
namespace core
{
	class Artifact : public Object
	{
	public:
		std::string name;
		std::string name_decorated;
		std::string brief;
		std::string url;
		Semver version;
		Licence licence;
	};
	
}
}

#endif
