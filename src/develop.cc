
#include <iostream>

#include "core.hh"

int main(int argc, char* argv[])
{
	long number = core_next::to_number<long>("123456789");
	std::cout << "Number : " << number << "\n";
	
	return EXIT_SUCCESS;
}
