#include <cstdlib>
#include <iostream>

#include <Artifact.hh>

int main(int argc, char *argv[])
{
	//octetos usa esta fucion estandar para retornar informacion de su paquete
	octetos::core::Artifact packinfo = octetos::core::getPackageInfo();
	// la version del paquete esta en octetos::core::Artifact::version
	octetos::core::Semver& ver = packinfo.version;
	std::cout << "Estamos trabajando con la version '" << (std::string)ver << "' del paquete.\n";
	
	octetos::core::Semver ver100(1,0,0);
	if(ver < ver100)
	{
		std::cout << "La API de '" << packinfo.name_decorated << "' está aún en fase desarrollo\n";
	}
	if(ver >= ver100)
	{
		std::cout << "La API de '" << packinfo.name_decorated << "' está en fase estable para la version '" <<  ver.getMajor () << "'\n";
	}
	
	return EXIT_SUCCESS;
}
