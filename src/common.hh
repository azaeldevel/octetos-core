#ifndef TOOLKIT_COMMON_HPP
#define TOOLKIT_COMMON_HPP

#include <string>

#include "Message.hh"
#include "Object.hh"
#include "Version.hh"
#include "Artifact.hh"
#include "Licence.hh"


namespace octetos
{
namespace core
{
	/**
	 * \brief retorna la version actual de componente
	 **/
	Version getPakageVersion();
	std::string getPakageName();
	
	/**
	 * \brief retorna la informacion del paquete usese ne lugar getPakageVersion y getPakageName
	 **/
	Artifact getPackageInfo();
	
}
}
#endif
