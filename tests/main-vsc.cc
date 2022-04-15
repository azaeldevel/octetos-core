

#include <iostream>

#include <Exception-v3.hh>

using namespace oct::core::v3;

int main(int argc, char *argv[])
{
	//
	Exception ex1;
	if (ex1.code() != 0) std::cout << "Fallo de inicilizacion por default.\n";
	if (ex1.filename() != NULL) std::cout << "Fallo de inicilizacion por default.\n";


	std::cout << "<<<<\n<<<<Pruebas completadas.\n";
	return EXIT_SUCCESS;
}
