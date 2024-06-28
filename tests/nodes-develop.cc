#include <cstdlib>
#include <iostream>
#include <random>
#include <chrono>

#include "../3/nodes.hh"

struct add
{
    float a,b;
    float result(){return a + b;}
};
struct sub
{
    float a,b;

    float result() {return a - b;}
};

namespace core = oct::core::v3;

int main(int argc, char *argv[])
{
    const char* testing = "testing....";
    core::Number<float> num1(5.0f);
    core::Number<float> num2(1.9f);
    core::Number<float> num3(3.9f);
    core::Addition<float> op1(num1,num2);
    core::Addition<float> op2(op1,num3);
    core::Subtration<float> op3(op2,num2);
    std::cout <<"Developing...\n";
    float result = op1;
    float result2 = op2;
    float result3 = op3;
    std::cout <<"Result 1 : " << result << "\n";
    std::cout <<"Result 2 : " << result2 << "\n";
    std::cout <<"Result 3 : " << result3 << "\n";

    constexpr size_t numbers_length = 1000;
    constexpr size_t operations_length = numbers_length/size_t(2);

    float numbers[numbers_length];
    core::Number<float> numbersNode[numbers_length];

    add adds[operations_length];
    core::Addition<float> additions[operations_length];

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<float> gen(1.0f,100000.0f);

    for(size_t i = 0; i < numbers_length;i++)
    {
        numbers[i] = gen(rng);
        numbersNode[i] = numbers[i];
    }
    /*for(size_t i = 0; i < numbers_length;i++)
    {
        std::cout << numbers[i] << "\n";
    }*/

    for (size_t i = 0; i < operations_length; i++)
    {
        adds[i].a = numbers[i];
        adds[i].b = numbers[i + 1];
        additions[i].set(numbersNode[i],numbersNode[i + 1]);
        //std::cout << "Result " << i << " : " << adds[i].result() << "\n";
        //std::cout << "Result " << i << " : " << float(additions[i]) << "\n";
        //std::cout << "\n";
    }

    float data;
    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < operations_length;i++)
    {
        data = adds[i].result();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time_base = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < operations_length;i++)
    {
        data = float(additions[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    auto time_target = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "base : " << time_base.count() << "\n";
    std::cout << "target : " << time_target.count() << "\n";
    std::cout << "Speed : " << time_target.count()/time_base.count() << "\n";


    return EXIT_SUCCESS;
}