

#include "v3.hh"

#include <string.h>
#include <iostream>
#include <variant>
#include <random>
#include <chrono>

#include <core/3/array.hh>
#include <core/3/tree.hh>
//#include <core/3/Semver.hh>
#include <core/3/numbers.hh>
#include <algorithm>


#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif


namespace core = oct::core::v3;

int v3_init(void)
{
	return 0;
}

int v3_clean(void)
{
	return 0;
}



void v3_developing()
{
    float a = 1.5f;
    float b = 1.5f;
    float c = 1.7f;
    float epsilon = 0.001f;
    float d = b - (epsilon/2.0f);
    float e = b + (epsilon/2.0f);
    CU_ASSERT(core::equal(a,b));
    CU_ASSERT_FALSE(core::equal(a,c));
    CU_ASSERT(core::equal(a,d,epsilon));
    CU_ASSERT(core::equal(a,e,epsilon));

    int f = 2;
    int g = 2;
    int h = 3;
    CU_ASSERT(core::equal(f,g));
    CU_ASSERT_FALSE(core::equal(f,h));
    CU_ASSERT(core::equal(f,h,1));

    core::convertion<int>::type data = 1.11f;
    CU_ASSERT(core::equal(data,1.11f));

}


void v3_array()
{
    constexpr core::array<int,6> array1 {-1,5,6,9,8,7};
    CU_ASSERT(array1[0] == -1);
    CU_ASSERT(array1[1] == 5);
    CU_ASSERT(array1[2] == 6);
    CU_ASSERT(array1[3] == 9);
    CU_ASSERT(array1[4] == 8);
    CU_ASSERT(array1[5] == 7);

    const int* base1 = array1;
    CU_ASSERT(base1[0] == -1);
    CU_ASSERT(base1[1] == 5);
    CU_ASSERT(base1[2] == 6);
    CU_ASSERT(base1[3] == 9);
    CU_ASSERT(base1[4] == 8);
    CU_ASSERT(base1[5] == 7);

    core::array<int> array2 {-1,5,6,9,8,7};
    CU_ASSERT(array1[0] == -1);
    CU_ASSERT(array1[1] == 5);
    CU_ASSERT(array1[2] == 6);
    CU_ASSERT(array1[3] == 9);
    CU_ASSERT(array1[4] == 8);
    CU_ASSERT(array1[5] == 7);

    int* base2 = array2;
    CU_ASSERT(base2[0] == -1);
    CU_ASSERT(base2[1] == 5);
    CU_ASSERT(base2[2] == 6);
    CU_ASSERT(base2[3] == 9);
    CU_ASSERT(base2[4] == 8);
    CU_ASSERT(base2[5] == 7);

    core::array<int> array3(core::array<int>{-1,5,6,9,8,7});
    CU_ASSERT(array3[0] == -1);
    CU_ASSERT(array3[1] == 5);
    CU_ASSERT(array3[2] == 6);
    CU_ASSERT(array3[3] == 9);
    CU_ASSERT(array3[4] == 8);
    CU_ASSERT(array3[5] == 7);

    int* base3 = array3;
    CU_ASSERT(base3[0] == -1);
    CU_ASSERT(base3[1] == 5);
    CU_ASSERT(base3[2] == 6);
    CU_ASSERT(base3[3] == 9);
    CU_ASSERT(base3[4] == 8);
    CU_ASSERT(base3[5] == 7);

    core::array<int> array4;
    array4 = array3;
    CU_ASSERT(array4[0] == -1);
    CU_ASSERT(array4[1] == 5);
    CU_ASSERT(array4[2] == 6);
    CU_ASSERT(array4[3] == 9);
    CU_ASSERT(array4[4] == 8);
    CU_ASSERT(array4[5] == 7);

    int* base4 = array4;
    CU_ASSERT(base4[0] == -1);
    CU_ASSERT(base4[1] == 5);
    CU_ASSERT(base4[2] == 6);
    CU_ASSERT(base4[3] == 9);
    CU_ASSERT(base4[4] == 8);
    CU_ASSERT(base4[5] == 7);

    core::array<int> array5;
    array5 = {-1,5,6,9,8,7};
    CU_ASSERT(array5[0] == -1);
    CU_ASSERT(array5[1] == 5);
    CU_ASSERT(array5[2] == 6);
    CU_ASSERT(array5[3] == 9);
    CU_ASSERT(array5[4] == 8);
    CU_ASSERT(array5[5] == 7);

    int* base5 = array5;
    CU_ASSERT(base5[0] == -1);
    CU_ASSERT(base5[1] == 5);
    CU_ASSERT(base5[2] == 6);
    CU_ASSERT(base5[3] == 9);
    CU_ASSERT(base5[4] == 8);
    CU_ASSERT(base5[5] == 7);

    constexpr core::array<int,6> array6(core::array<int,6>{-1,5,6,9,8,7});
    CU_ASSERT(array6[0] == -1);
    CU_ASSERT(array6[1] == 5);
    CU_ASSERT(array6[2] == 6);
    CU_ASSERT(array6[3] == 9);
    CU_ASSERT(array6[4] == 8);
    CU_ASSERT(array6[5] == 7);
    CU_ASSERT(array6.back() == 7);

    auto array7 = array6.sub<2,2>();
    //array7.print(std::cout);
    CU_ASSERT(array7.size() == 2)
    CU_ASSERT(array7[0] == 6);
    CU_ASSERT(array7[1] == 9);

    auto array8 = array3.sub(2,2);
    //array8->print(std::cout);
    CU_ASSERT(array8->size() == 2)
    CU_ASSERT(array8->at(0) == 6);
    CU_ASSERT(array8->at(1) == 9);

    core::array<int> array9(base1 + 2,2);
    CU_ASSERT(array9[0] == 6);
    CU_ASSERT(array9[1] == 9);

    core::array<int> array10 {-1,5,6,9,8,7};
    CU_ASSERT(array10[0] == -1);
    CU_ASSERT(array10[1] == 5);
    CU_ASSERT(array10[2] == 6);
    CU_ASSERT(array10[3] == 9);
    CU_ASSERT(array10[4] == 8);
    CU_ASSERT(array10[5] == 7);
    //array10.print(std::cout);
    //std::cout << "\n";
    std::reverse(array10.begin(),array10.end());
    //array10.print(std::cout);
    CU_ASSERT(array10[0] == 7);
    CU_ASSERT(array10[1] == 8);
    CU_ASSERT(array10[2] == 9);
    CU_ASSERT(array10[3] == 6);
    CU_ASSERT(array10[4] == 5);
    CU_ASSERT(array10[5] == -1);
    CU_ASSERT(array10.back() == -1);

    core::array<int,6> array11 {-1,5,6,9,8,7};
    CU_ASSERT(array11[0] == -1);
    CU_ASSERT(array11[1] == 5);
    CU_ASSERT(array11[2] == 6);
    CU_ASSERT(array11[3] == 9);
    CU_ASSERT(array11[4] == 8);
    CU_ASSERT(array11[5] == 7);
    //array11.print(std::cout);
    //std::cout << "\n";
    std::reverse(array11.begin(),array11.end());
    //array11.print(std::cout);
    CU_ASSERT(array11[5] == -1);
    CU_ASSERT(array11[4] == 5);
    CU_ASSERT(array11[3] == 6);
    CU_ASSERT(array11[2] == 9);
    CU_ASSERT(array11[1] == 8);
    CU_ASSERT(array11[0] == 7);
}
void v3_tree()
{

    core::Node<core::Number> num1;
    core::Node<core::Number> num2;
    core::Node<core::Number> num3;

}


void v3_cpp()
{
    const char* cstr1 = "Prueba 1...";
    std::string str1 = std::string(cstr1 + 3,5);
    //std::cout << "String : " << str1 << "\n";
    CU_ASSERT(str1.compare("eba 1") == 0);
}

void v3_trails()
{
    //core::convertion<signed int>::type data1 = std::numeric_limits<signed int>::max();
    //CU_ASSERT((signed int)data1 == std::numeric_limits<signed int>::max());

    //core::convertion<unsigned int>::type data2 = std::numeric_limits<unsigned int>::max();
    //CU_ASSERT((unsigned int)data2 == (float)std::numeric_limits<unsigned int>::max());

    //core::convertion<signed long int>::type data3 = std::numeric_limits<signed long int>::max();
    //CU_ASSERT((signed long int)data3 == (float)std::numeric_limits<signed long int>::max());

    //core::convertion<signed long int>::type data4 = std::numeric_limits<signed long int>::max();
    //CU_ASSERT((signed long int)data4 == (float)std::numeric_limits<signed long int>::max());

    //core::convertion<unsigned long int>::type data4 = std::numeric_limits<unsigned long int>::max();
    //CU_ASSERT(core::equal(data4, (float)std::numeric_limits<unsigned long int>::max()));

    /*core::convertion<unsigned long>::type data2 = std::numeric_limits<unsigned long>::max();
    CU_ASSERT(data2 == std::numeric_limits<unsigned long>::max());

    core::convertion<unsigned long>::type data3 = std::numeric_limits<unsigned long>::max();
    CU_ASSERT(data3 == std::numeric_limits<unsigned long>::max());*/


}

void v3_Number()
{
    core::Number real1 = 1.36f;
    core::Number real2 = -361.6f;
    core::Number real3 = 93.6f;
    CU_ASSERT(core::equal((float)real1,1.36f));
    CU_ASSERT(core::equal((float)real2,-361.6f));
    CU_ASSERT(core::equal((float)real3,93.6f));

    float& real4 = real1;
    real4 = 65.3f;
    CU_ASSERT_FALSE(core::equal((float)real1,1.36f));
    CU_ASSERT(core::equal((float)real1,65.3f));
}


void v3_performance()
{
    constexpr size_t amoung = 1000;
    core::Number numn;
    double numd,res1 = 0,res2 = 0;
    double data[amoung];
    std::random_device rd;
    std::uniform_real_distribution<double> distd(-10.0, 10.0);

    for(size_t i = 0; i < amoung; i++)
    {
        data[i] = distd(rd);
    }
    /*for(size_t i = 0; i < amoung; i++)
    {
        std::cout << i << ".-" << data[i] << "\n";
    }*/

    size_t times = 100000;
    auto start1 = std::chrono::high_resolution_clock::now();
    for(size_t t = 0; t < times; t++)
    {
        for(size_t i = 0; i < amoung; i++)
        {
            numd = data[i];
            res1 += numd;
        }
    }
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(stop1 - start1);
    //std::cout << "Time taken by function: " << duration1.count() << " milliseconds" << std::endl;
    //std::cout << "Resul : " << res1 << "\n";

    res2 = 0;
    auto start2 = std::chrono::high_resolution_clock::now();
    for(size_t t = 0; t < times; t++)
    {
        for(size_t i = 0; i < amoung; i++)
        {
            numn = data[i];
            res2 += (double)numn;
        }
    }
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
    //std::cout << "Time taken by function: " << duration2.count() << " milliseconds" << std::endl;
    //std::cout << "Resul : " << res2 << "\n";
    CU_ASSERT(core::equal(res1,res2))
    double v = (double)duration2.count() / (double)duration1.count();
    //std::cout << "Eficiencia : " << v << "\n";
    CU_ASSERT(v < 1.1)
}
