
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>


#include "common.hh"
#include "config.h"

//#include "common.hpp"


static std::string  rootDir;
static int majorNumber;

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_toolkit_common(void)
{
        return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_toolkit_common(void)
{
        return 0;
}

void testComparators()
{
        octetos::core::Version ver1;
        octetos::core::Version ver2;
        
        ver1.setNumbers(1,2,3);
        ver2.setNumbers(1,2,5);
        //std::cout << "test 1" << std::endl;
        if(ver1 >= ver2)
        {
                CU_ASSERT(false);
        }
        else
        {
                CU_ASSERT(true);
        }
        //std::cout << "test 2" << std::endl;
        if(ver2 >= ver1)
        {
                CU_ASSERT(true);
        }
        else
        {
                CU_ASSERT(false);
        }
                
        ver1.setNumbers(1,2,3);
        ver2.setNumbers(1,2,3);
        //std::cout << "test 3" << std::endl;
        if(ver1 >= ver2)
        {
                CU_ASSERT(true);
        }
        else
        {
                CU_ASSERT(false);
        }
        //std::cout << "test 4" << std::endl;
        if(ver2 >= ver1)
        {
                CU_ASSERT(true);
        }
        else
        {
                CU_ASSERT(false);
        }
        
        //La nueva politca dicta que build no tiene significado en la presendiencia de las version pero sera removido hasta v5 paramantener compatibilidad 
        ver1.setNumbers(1,2,3);
        ver2.setNumbers(1,0,3);
        //std::cout << "test 3" << std::endl;
        if(ver1 >= ver2)
        {
                CU_ASSERT(true);
        }
        else
        {
                CU_ASSERT(false);
        }
        //std::cout << "test 4" << std::endl;
        if(ver2 >= ver1)
        {
                CU_ASSERT(false);
        }
        else
        {
                CU_ASSERT(true);
        }   
        
    //x simepre es amjor que x.y
    octetos::core::Version ver3;
    octetos::core::Version ver4;
    ver3.setNumbers(1);
    ver4.setNumbers(1,50);
    if(ver3 >= ver4) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
    }
    if(ver3 >= ver4) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
    }
    if(ver3 <= ver4) 
    {
        CU_ASSERT(false);
    }
    else 
    {
        CU_ASSERT(true);
    }     
    if(ver3 > ver4) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
    }
    if(ver3 > ver4) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
    }
    if(ver3 < ver4) 
    {
        CU_ASSERT(false);
    }
    else 
    {
        CU_ASSERT(true);
    }  
    
    
    
    
    //x simepre es amjor que x.y
    octetos::core::Version ver5;
    octetos::core::Version ver6;
    ver5.setNumbers(1,50);
    ver6.setNumbers(1,50,100);
    if(ver5 >= ver6) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
    }
    if(ver5 > ver6) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
    }
    if(ver5 < ver6) 
    {
        CU_ASSERT(false);
    }
    else 
    {
        CU_ASSERT(true);
    }
    
    
    if(ver5 == ver6)
    {
        CU_ASSERT(false);
    }
    else
    {
        CU_ASSERT(true);
    }
    if(ver5 != ver6)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
    
    octetos::core::Version verMin;
    octetos::core::Version verMax;
    octetos::core::Version verVal;
    verMin.setNumbers(1,2,0);
    verVal.setNumbers(1,2,3);
    verMax.setNumbers(3,9,0);
    if(verMin <= verVal)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
    if(verMax >= verVal)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
    
    octetos::core::Version ver7;
    octetos::core::Version ver8;
    ver7.setNumbers(4,4,20);
    ver8.setNumbers(3,2);
    if(ver7 >= ver8)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
}


void testValidStatement()
{
        //CU_ASSERT(octetos::toolkit::Version::valid("valid numbers = 1.3.65"));
        ///std::cout << "Err>>:" <<std::endl;
        //CU_ASSERT_FALSE(octetos::toolkit::Version::valid("valid numbers = 1.44.55-rc"));//deve rechazar porque se esta incluyendo la etapa
        //std::cout << "Err<<" <<std::endl;
        //CU_ASSERT(octetos::toolkit::Version::valid("valid stage = rc"));
        //CU_ASSERT_FALSE(octetos::toolkit::Version::valid("valid stage = 1.2.3-rc"));
        //CU_ASSERT(octetos::toolkit::Version::valid("valid name = snate43"));
        //CU_ASSERT(octetos::toolkit::Version::valid("valid build = +12389678111233"));
}

void testBuildExtension()
{
    octetos::core::Version ver1;
    ver1.setBuild(12345678901233);
    CU_ASSERT(ver1.getBuildUL() == 12345678901233);
    octetos::core::Version ver2;
    ver2.setNumbers(2,36,98);
    ver2.setStage(octetos::core::Version::Stage::alpha);
    octetos::core::Version ver3;
    ver3.setNumbers(1);
    ver3.setStage(octetos::core::Version::Stage::release);
    ver2.setBuild("+200-r56");
    //std::cout << std::endl << "Build complejo " << ver2.toString() << std::endl;
    if(ver2.getBuildString().compare("+200-r56") == 0)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
}

void testStageExtension()
{
    octetos::core::Version ver1;
    ver1.setNumbers(2,36,98);
    ver1.setStage(octetos::core::Version::Stage::alpha,2);
    if(ver1.getStageNumber() == 2)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
}
int main(int argc, char *argv[])
{

	octetos::core::Artifact packinfo = octetos::core::getPackageInfo();
	octetos::core::Version& ver = packinfo.version;
    
	CU_pSuite pSuite = NULL;
	majorNumber = ver.getMajor();
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	std::string& pkName = packinfo.name;
	std::string classVersionString = std::string("Probando ") + pkName + " " + ver.toString() + "\n" + packinfo.licence.getBrief() + "\n" + packinfo.brief + "\n";
	pSuite = CU_add_suite(classVersionString.c_str(), init_toolkit_common, clean_toolkit_common);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
		
	if ((NULL == CU_add_test(pSuite, "Criterios de comparación", testComparators)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Pruebas de validadacion", testValidStatement)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	
	/*if ((NULL == CU_add_test(pSuite, "Extención de Campo Build.", testBuildExtension)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}*/
	
	/*if ((NULL == CU_add_test(pSuite, "Extención de Campo Stage.", testStageExtension)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}*/
	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();	
}
