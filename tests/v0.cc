
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>


#include "common.hh"
#include "config.h"



int init(void)
{
	return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean(void)
{
	return 0;
}

void testParseString_v100()
{
	octetos::core::Artifact packinfo = octetos::core::getPackageInfo();
	octetos::core::semver::v100 ver = packinfo.version;

	octetos::core::semver::v100 verReaded;
	verReaded.set(ver.toString());
	//std::cout << "ver '" << ver.toString () << "'\n";
	//std::cout << "verReaded '" << verReaded.toString () << "'\n";
	if(verReaded == ver)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}

	octetos::core::semver::v100 verExtracted;
	if(verExtracted.extractNumbers(ver.toString()))
	{
		//std::cout << "Version is '" << verExtracted.toString () << "'\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}

	octetos::core::semver::v100 mysqlServer(5,7,30);
	octetos::core::semver::v100 mysqlServerImported;
	mysqlServerImported.set(50730,octetos::core::Semver::ImportCode::MySQL);
	if(mysqlServer == mysqlServerImported)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
}

void testComparators_v100()
{
        octetos::core::semver::v100 ver1;
        octetos::core::semver::v100 ver2;
        
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
    octetos::core::semver::v100 ver3;
    octetos::core::semver::v100 ver4;
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
    octetos::core::semver::v100 ver5;
    octetos::core::semver::v100 ver6;
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
    
    octetos::core::semver::v100 verMin;
    octetos::core::semver::v100 verMax;
    octetos::core::semver::v100 verVal;
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
    
    octetos::core::semver::v100 ver7;
    octetos::core::semver::v100 ver8;
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

	octetos::core::semver::v100 ver9;
	ver9.setNumbers(4,4,20);
	ver9.setBuild(12345678901233);
	if(ver9.getBuildUL() == 12345678901233)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
	
	octetos::core::semver::v100 ver10;
	ver10.setNumbers(4,4,20);
	ver10.setBuild("+200-r56");
	if(ver10.getBuildString().compare("+200-r56") == 0)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
    }
}

void testBuildExtension()
{
    octetos::core::Semver ver1;
    ver1.setBuild(12345678901233);
    CU_ASSERT(ver1.getBuildUL() == 12345678901233);
    octetos::core::Semver ver2;
    ver2.setNumbers(2,36,98);
    ver2.setStage(octetos::core::semver::Stage::alpha);
    octetos::core::Semver ver3;
    ver3.setNumbers(1);
    ver3.setStage(octetos::core::semver::Stage::release);
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
    octetos::core::Semver ver1;
    ver1.setNumbers(2,36,98);
    ver1.setStage(octetos::core::semver::Stage::alpha,2);
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
	octetos::core::Semver& ver = packinfo.version;
    
	CU_pSuite pSuite = NULL;
	int majorDevelop = 0;
	if(majorDevelop != ver.getMajor())
	{
		std::cerr << "Esta conjunto de pruebas estan Deseñado para la version mayor '" << majorDevelop << "'\n";
		return EXIT_FAILURE;
	}
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	std::string& pkName = packinfo.name;
	std::string classVersionString = pkName + " " + ver.toString() + "\n" + packinfo.licence.getBrief() + "\n" + packinfo.brief + "\n";
	pSuite = CU_add_suite(classVersionString.c_str(), init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
		
	if ((NULL == CU_add_test(pSuite, "Criterios de comparación", testComparators_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
			
	if ((NULL == CU_add_test(pSuite, "Validacion de parseo", testParseString_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
		
	
	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();	
}
