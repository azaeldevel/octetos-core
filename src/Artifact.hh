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

	/**
	 * \brief retorna la informacion del paquete
	 **/
	__attribute__((deprecated)) Artifact getPackageInfo();
	/**
	 * \brief retorna la informacion del paquete
	 **/
	bool getPackageInfo(Artifact&);
}
}

#endif
