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
    core::nodes::Number num2(33);
    core::nodes::Number num3(24.36);
    core::nodes::Operation op1('+',num1,num2);
    core::nodes::Operation op2('*',num3,op1);
    op2.print(std::cout);

    return EXIT_SUCCESS;
}
