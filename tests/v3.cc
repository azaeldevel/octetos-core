

#include "v3.hh"

#include <string.h>
#include <iostream>
#include <variant>


#include <core/3/array.hh>
#include <core/3/tree.hh>
#include <core/3/Lexer-TTC.hh>
#include <core/3/Semver.hh>
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
}
void v3_tree()
{
    core::Root root1(4);

    core::Data<int> num1;
    num1 = 156;
    core::Data<float> num2;
    num2 = 157;
    core::Data<double> num3;
    num3 = 158;
    core::Data<unsigned long> num4;
    num4 = 159;

    root1[0] = &num1;
    root1[1] = &num2;
    root1[2] = &num3;
    root1[3] = &num4;

    CU_ASSERT(root1[0] == &num1);
    CU_ASSERT(root1[1] == &num2);
    CU_ASSERT(root1[2] == &num3);
    CU_ASSERT(root1[3] == &num4);

    CU_ASSERT(root1[3]->is(typeid(num4)));
    CU_ASSERT_FALSE(root1[3]->is(typeid(num2)));
    //auto num = root1[2];
    //std::cout << (core::Type<double>&)*num << "\n";

    CU_ASSERT(root1.check() == core::qualifier::branch);
    CU_ASSERT(root1[0]->check() == core::qualifier::data);
    CU_ASSERT(root1[1]->check() == core::qualifier::data);
    CU_ASSERT(root1[2]->check() == core::qualifier::data);
    CU_ASSERT(root1[3]->check() == core::qualifier::data);

    core::Data<int> num5(200);
    core::Data<int> num6(300);
    core::Data<int> num7(25);
    core::Data<float> num8(12.3);
    core::Math mat1(4,core::Math::Operator::addition);
    mat1[0] = &num5;
    mat1[1] = &num6;
    mat1[2] = &num7;
    mat1[3] = &num8;
    core::Root root2(1);
    root2[0] = &mat1;

    /*std::cout << "\n";
    root2.print(std::cout);
    std::cout << "\n";*/


}

void v3_lexer_C()
{
    const core::array<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
    const core::array<char> terms = {'.','-','+',' ','\n'};
    const core::array<char> nothing = {};
    const char* input1 = "269.56.9-alpha+archlinux";
    typedef core::lex::TTC<char,core::Semver::Tokens,core::lex::State,11> TT;
    TT semver_tt1;

    semver_tt1.almost_one(digits,core::Semver::Tokens::number,terms);

    std::cout << "\n";
    semver_tt1.print(std::cout,0);

    core::Buffer semver_buff1(input1);
	core::lex::Lexer<char,core::Semver::Tokens,core::lex::State,TT> semver_lex3(semver_tt1,semver_buff1);

}
