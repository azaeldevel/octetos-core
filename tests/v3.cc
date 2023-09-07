

#include "v3.hh"

#include <string.h>
#include <iostream>
#include <variant>


#if defined(__linux__)
    //#include <src/Exception-v3.hh>
    //#include <src/Version-v3.hh>
    #include <core/3/array.hh>
    #include <core/3/tree.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <core/src/Exception-v3.hh>
    //#include <core/src/Version-v3.hh>
    #include <core/3/array.hh>
    #include <core/3/tree.hh>
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
    core::array<int,6> array1 {-1,5,6,9,8,7};
    CU_ASSERT(array1[0] == -1);
    CU_ASSERT(array1[1] == 5);
    CU_ASSERT(array1[2] == 6);
    CU_ASSERT(array1[3] == 9);
    CU_ASSERT(array1[4] == 8);
    CU_ASSERT(array1[5] == 7);

    int* base1 = array1;
    CU_ASSERT(base1[0] == -1);
    CU_ASSERT(base1[1] == 5);
    CU_ASSERT(base1[2] == 6);
    CU_ASSERT(base1[3] == 9);
    CU_ASSERT(base1[4] == 8);
    CU_ASSERT(base1[5] == 7);

}
void v3_tree()
{
    core::Number<std::variant<int,float>> num1;
    //num1 = 1.3f;
    //std::cout << num1 << "\n";
}
