#include <cstdlib>
#include <iostream>
#include "../3/nodes.hh"

namespace core = oct::core::v3;

int main(int argc, char *argv[])
{

    core::Number<float> num1(5.0);
    core::Number<float> num2(1.3);
    core::Addition<core::Number<float>> op1(num1,num2);
    


    return EXIT_SUCCESS;
}