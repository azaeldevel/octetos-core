#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <chrono>

#include "../3/nodes.hh"

namespace core = oct::core::v3;

int main(int argc, char *argv[])
{
    core::nodes::Number num1(10);
    num1.print(std::cout);

    return EXIT_SUCCESS;
}
