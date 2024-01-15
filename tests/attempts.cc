
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>

bool is_prime(size_t n)
{
    size_t temp = std::sqrt(n);
    for(size_t i = 0; i < temp; i++)
    {
        if(n % i == 0) return true;
    }

    return false;
}
int main(int argc, char *argv[])
{
    /*for(size_t i = 0; i < 1000; i++)
    {
        std::cout << i;
        if(is_prime(i)) std::cout << " es primo\n";
        else std::cout << " no es primo\n";
    }*/
    constexpr int original[] = {2,4,3,6,3,7,9,8,5,3,1,5,3,1,9,3,5,3,2,6,1,8,7,7,6,5,4,3,2,0,0,0,1,3,2,6,5,4,5,4,3,5,4,9};
    constexpr size_t originalSize = sizeof(original)/sizeof(int);
    int result[originalSize];
    size_t resultSize = 0;

    size_t i,j;
    bool duplicated;
    for(i = 0,resultSize = 0; i < originalSize ; i++)
    {
        //std::cout << original[i] << "\n";
        duplicated = false;
        for(j = 0; j < resultSize; j++)
        {
            if(original[i] == result[j])
            {
                duplicated = true;
                break;
            }
        }
        if(not duplicated) result[resultSize++] = original[i];
    }
    for(i = 0; i < resultSize ; i++)
    {
        std::cout << result[i] << "\n";
    }

	return EXIT_SUCCESS;
}
