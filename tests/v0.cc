
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>


#include "common.hh"
#include "config.h"
#include "semver-parser.h"


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

void testImports_v100()
{
	octetos::core::semver::v100 verPQ;
	verPQ.set(80105,octetos::core::semver::ImportCode::PostgreSQL);
	if(verPQ.getMajor() == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	if(verPQ.getMinor() == 1)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	if(verPQ.getPatch() == 5)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	std::string strverpq = verPQ.toString();
	std::cout << "verPQ = " << strverpq << "\n";
}

void testParseString_v100()
{
	octetos_Semver ver1,ver2,ver3;
	octetos_Semver_init(&ver1);
	octetos_Semver_init(&ver2);
	octetos_Semver_init(&ver3);
	struct octetos_Tray ty1,ty2,ty3;
	ty1.version = &ver1;
	ty1.dysplay_erro = 1;
	ty2.version = &ver2;
	ty2.dysplay_erro = 1;
	ty3.version = &ver3;
	ty3.dysplay_erro = 1;
	
	//printf( ">>>\n");
	parse_string(&ty1,"1.6.55-alpha");    
    if(ty1.version->major == 1)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ty1.version->minor == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ty1.version->patch == 55)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(strcmp(ty1.version->prerelease,"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    
	parse_string(&ty2,"7.6.23-alpha-1"); 
	if(ty2.version->major == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ty2.version->minor == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ty2.version->patch == 23)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(strcmp(ty2.version->prerelease,"alpha-1") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	
    
	parse_string(&ty3,"7.6.23-alpha5-2");     
	if(ty3.version->major == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ty3.version->minor == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ty3.version->patch == 23)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(strcmp(ty3.version->prerelease,"alpha5-2") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	octetos::core::semver::v100 ver4;
	ver4.set("7.6.23-betar1-2");
	if(ver4.getPrerelease().compare("betar1-2") == 0)
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
	
	if ((NULL == CU_add_test(pSuite, "Validacion de Imports", testImports_v100)))
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
