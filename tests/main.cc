
#include <iostream>

#include "../src/shell.hh"


int main()
{
	std::cout << "Testing..";
	oct::core::Shell shell;

	shell.mkdir("test-123456");

	return EXIT_SUCCESS;
}
