
#include <iostream>

#include "arrays.hh"

namespace core_here = oct::core::v3;



int main(int argc, char* argv[])
{
    core_here::array<int> numbers = {-1,0,1,2,3,4,5,6,7};
    for(auto e : numbers)
    {
        std::cout << "Number : " << e << "\n";
    }
    //numbers[0] = -100;

    /*core_here::array numbers2 = numbers;
    for(auto e : numbers2)
    {
        std::cout << "Number : " << e << "\n";
    }*/

	return EXIT_SUCCESS;
}
