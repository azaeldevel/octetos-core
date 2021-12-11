
#include <iostream>

#include "../src/shell.hh"


int main()
{
	oct::core::Shell shell;

	shell.mkdir("test-123456");

	std::cout << "work directory : " << shell.cwd() << "\n";

	if(shell.exists("bin"))
    {
        std::cout << "Existe el directorio\n";
    }
    else
    {
        std::cout << "No existe el directorio\n";
    }

    if(shell.exists("configure.ac"))
    {
        std::cout << "Existe el configure.ac\n";
    }
    else
    {
        std::cout << "No existe el configure.ac\n";
    }


    if(shell.exists("configure2.ac"))
    {
        std::cout << "Existe el configure2.ac\n";
    }
    else
    {
        std::cout << "No existe el configure2.ac\n";
    }

	return EXIT_SUCCESS;
}
