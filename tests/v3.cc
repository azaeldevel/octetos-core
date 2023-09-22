

#include "v3.hh"

#include <string.h>
#include <iostream>
#include <variant>
#include <random>
#include <chrono>

#include <core/3/array.hh>
#include <core/3/tree.hh>
#include <core/3/Semver.hh>
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
    float a = 1.5;
    float b = 1.5;
    float c = 1.7;
    float epsilon = 0.001;
    float d = b - (epsilon/2);
    float e = b + (epsilon/2);
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

    core::array<int> array9(2,base1 + 2);
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

void v3_TTC()
{
    const core::array<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
    const core::array<char> terms = {'.','-','+',' ','\n','\t'};
    const core::array<char> separators = {'.','-','+'};
    const core::array<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    typedef core::lex::TTC<char,core::Semver::Tokens,core::lex::State,11> TT;

    const char* input1 = "2696.69.36-alpha";
    core::Buffer semver_buff1(input1);


    /*TT semver_tt1;
    //semver_tt1.almost_one(digits,core::Semver::Tokens::number,terms);
    semver_tt1.one(digits);
    //std::cout << "\n";
    //semver_tt1.print(std::cout,2);
	core::lex::LC<char,core::Semver::Tokens,core::lex::State,TT> semver_lex1(semver_tt1,semver_buff1);
    //core::Semver::Tokens token1 = semver_lex1.next();
    //CU_ASSERT(token1 == core::Semver::Tokens::number);*/

    TT semver_tt2;
    //semver_tt1.almost_one(digits,core::Semver::Tokens::number,terms);
    core::lex::State state_next_2 = semver_tt2.one(digits);
    state_next_2 = semver_tt2.one(digits,state_next_2);
    semver_tt2.prefixing(state_next_2,terms,core::Semver::Tokens::number);
    semver_tt2.circular(digits,state_next_2);
    state_next_2 = semver_tt2.one(separators,0,true);
    //std::cout << "\n";
    //semver_tt2.print(std::cout,0);
    //std::cout << "Token : " << to_string(token2.token) << "\n";
    //std::cout << "Token : " << (int)token2.token << "\n";
    state_next_2 = semver_tt2.one(separators,0,true);
    /*state_next_2 = semver_tt2.one(alphabet);
    CU_ASSERT(state_next_2 > 0)
    if(state_next_2 == -1)
    {
        std::cout << "Fallo la creacion de un estado ";
        if(semver_tt2.get_last_error() > core::lex::errors::none)
        {
            std::cout << " : " << semver_tt2.get_last_error() << " : " << to_string(semver_tt2.get_last_error());
        }
        std::cout << "\n";
    }
    state_next_2 = semver_tt2.one(alphabet,state_next_2);*/
    //semver_tt2.prefixing(state_next_2,terms,core::Semver::Tokens::string);
    //semver_tt2.circular(digits,state_next_2);
    //semver_tt2.print(std::cout,0);
    //Reading input....
	core::lex::LC<char,core::Semver::Tokens,core::lex::State,TT> semver_lex2(semver_tt2,semver_buff1);
    core::lex::Tokenized<char,core::Semver::Tokens> token2;
    semver_lex2.next(token2);
    CU_ASSERT(token2.token == core::Semver::Tokens::number);
    CU_ASSERT(token2.string.compare("2696") == 0)
    //std::cout << "TK : " << token2.string << "\n";
    semver_lex2.next(token2);
    CU_ASSERT(token2.token == core::Semver::Tokens('.'));
    CU_ASSERT(token2.string.compare(".") == 0)
    //std::cout << "TK : " << token2.string << "\n";
    //std::cout << "Token : " << to_string(token2.token) << "\n";
    //std::cout << "Token : " << (int)token2.token << "\n";
    //std::cout << "\n";
    semver_lex2.next(token2);
    CU_ASSERT(token2.token == core::Semver::Tokens::number);
    CU_ASSERT(token2.string.compare("69") == 0)
    //std::cout << "TK : " << token2.string << "\n";
    semver_lex2.next(token2);
    CU_ASSERT(token2.token == core::Semver::Tokens('.'));
    CU_ASSERT(token2.string.compare(".") == 0)
    //std::cout << "TK : " << token2.string << "\n";
    semver_lex2.next(token2);
    CU_ASSERT(token2.token == core::Semver::Tokens::number);
    CU_ASSERT(token2.string.compare("36") == 0)
    //std::cout << "TK : " << token2.string << "\n";
    /*semver_lex2.next(token2);
    CU_ASSERT(token2.token == core::Semver::Tokens('-'));
    CU_ASSERT(token2.string.compare("-") == 0)
    std::cout << "TK : " << token2.string << "\n";*/

    /*std::cout << "\n\n";
    TT semver_tt3;
    //semver_tt1.almost_one(digits,core::Semver::Tokens::number,terms);
    semver_tt3.one(digits,core::Semver::Tokens::number,terms,2,5);
    //std::cout << "\n";
    //semver_tt3.print(std::cout,2);
	core::lex::LC<char,core::Semver::Tokens,core::lex::State,TT> semver_lex3(semver_tt3,semver_buff1);
    core::lex::Tokenized<char,core::Semver::Tokens> token3;
    semver_lex3.next(token3);
    CU_ASSERT(token3.token == core::Semver::Tokens::number);
    CU_ASSERT(token3.string.compare("2696") == 0)*/

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
