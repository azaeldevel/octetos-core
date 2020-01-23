
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>
#include <Artifact.hh>

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
	if(octetos::core::Error::check())
	{
		std::cerr << (std::string)octetos::core::Error::get() << "\n";
		return;
	}
	verPQ.set(80105,octetos::core::semver::ImportCode::PostgreSQL);
	if(verPQ.getMajor() == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
	if(verPQ.getMinor() == 1)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
	if(verPQ.getPatch() == 5)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
	//std::string strverpq = verPQ.toString();
	//std::cout << "verPQ = " << strverpq << "\n";
}

void testParseString_v100()
{
	octetos::core::semver::v100 ver1,ver2,ver3;

	if(octetos::core::Error::check())
	{
		CU_ASSERT(false);
		std::cerr << (std::string)octetos::core::Error::get() << "\n";
		return;
	} 
	
	ver1.set("1.6.55-alpha"); 
    if(ver1.getMajor() == 1)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver1.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver1.getPatch() == 55)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver1.getPrerelease().c_str(),"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    
	ver2.set("7.6.23-alpha-1"); 
	if(ver2.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver2.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ver2.getPatch() == 23)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver2.getPrerelease().c_str(),"alpha-1") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
	
    
	ver3.set("7.6.23-alpha5-2");     
	if(ver3.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver3.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ver3.getPatch() == 23)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver3.getPrerelease().c_str(),"alpha5-2") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
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
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
	
	octetos::core::semver::v100 ver5;
	if(ver5.extractNumbers("7.6.23-betar1-2"))
	{
		//std::cerr << "Extracted :" << (std::string)ver5 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
}

void testParseString_v200()
{
	octetos::core::semver::v200 ver1,ver2,ver3;

	if(octetos::core::Error::check())
	{
		CU_ASSERT(false);
		std::cerr << (std::string)octetos::core::Error::get() << "\n";
		return;
	} 
	
	ver1.set("1.6.55-alpha"); 
    if(ver1.getMajor() == 1)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver1.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver1.getPatch() == 55)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver1.getPrerelease().c_str(),"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    
	ver2.set("7.6.23-alpha-1"); 
	if(ver2.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver2.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ver2.getPatch() == 23)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver2.getPrerelease().c_str(),"alpha-1") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
	
    
	ver3.set("7.6.23-alpha5-2");     
	if(ver3.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver3.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ver3.getPatch() == 23)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver3.getPrerelease().c_str(),"alpha5-2") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
	octetos::core::semver::v200 ver4;
	ver4.set("7.6.23-betar1-2");
	if(ver4.getPrerelease().compare("betar1-2") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}

	octetos::core::semver::v200 ver5;
	ver5.set("1.6.55+20190102"); 
    if(ver5.getMajor() == 1)
	{
		std::cout << "["<< (std::string)ver5 << "]: pass \n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    /*if(ver1.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(ver1.getPatch() == 55)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver1.getPrerelease().c_str(),"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
	}*/
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
			if(octetos::core::Error::check())
			{
				std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
				return;
			}
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
			if(octetos::core::Error::check())
			{
				std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
				return;
			}
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
			if(octetos::core::Error::check())
			{
				std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
				return;
			}
        }
        //std::cout << "test 4" << std::endl;
        if(ver2 >= ver1)
        {
                CU_ASSERT(true);
        }
        else
        {
                CU_ASSERT(false);
			if(octetos::core::Error::check())
			{
				std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
				return;
			}
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
			if(octetos::core::Error::check())
			{
				std::cerr << (std::string)octetos::core::Error::get() << "\n";
				return;
			}
        }
        //std::cout << "test 4" << std::endl;
        if(ver2 >= ver1)
        {
                CU_ASSERT(false);
			if(octetos::core::Error::check())
			{
				std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
				return;
			}
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
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
    if(ver3 >= ver4) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
    }
    if(ver3 <= ver4) 
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
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
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
    if(ver3 > ver4) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
    }
    if(ver3 < ver4) 
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
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
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
    if(ver5 > ver6) 
    {
        CU_ASSERT(true);
    }
    else 
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
    }
    if(ver5 < ver6) 
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
    else 
    {
        CU_ASSERT(true);
    }
    
    
    if(ver5 == ver6)
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
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
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
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
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
    if(verMax >= verVal)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
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
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }

	octetos::core::semver::v100 ver9;
    octetos::core::semver::v100 ver10;
    ver9.setNumbers(2);
    ver10.setNumbers(2);
    if(ver9 < ver10)
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
	octetos::core::semver::v100 ver11;
    octetos::core::semver::v100 ver12;
    ver11.setNumbers(2);
    ver12.setNumbers(2);
    if(ver11 > ver12)
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
	
	octetos::core::semver::v100 ver13;
    octetos::core::semver::v100 ver14;
    ver13.setNumbers(2,1);
    ver14.setNumbers(2,1);
    if(ver13 < ver14)
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
			return;
		}
    }
	
	octetos::core::semver::v100 ver15;
    octetos::core::semver::v100 ver16;
    ver15.setNumbers(2,1);
    ver16.setNumbers(2,1);
    if(ver15 < ver16)
    {
        CU_ASSERT(false);
		if(octetos::core::Error::check())
		{
			std::cerr << (std::string)octetos::core::Error::get() << "\n";
			return;
		}
    }
}

void testOperations_v100()
{
	octetos::core::semver::v100 ver1;
	octetos::core::semver::v100 ver2;
	
	ver2.setNumbers(1,3);
	ver1 = ver2;
	if(ver1 == ver2)
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
#ifdef OCTETOS_CORE_SANDBOX
	std::cout << "Sandbox is enabled.\n";
#else
	std::cout << "Sandbox is not enabled.\n";	
#endif
#ifdef DEBUG
	std::cout << "Debug is enabled.\n";
#else
	std::cout << "Debug is not enabled.\n";	
#endif
#ifdef COLLETION_ASSISTANT
	std::cout << "Collention Assitan is enabled.\n";
#else
	std::cout << "Collention Assitan is not enabled.\n";	
#endif
	octetos::core::Artifact packinfo;
	octetos::core::getPackageInfo(packinfo);
	if(octetos::core::Error::check())
	{
		std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
		return EXIT_FAILURE;
	}
	CU_pSuite pSuite = NULL;
	int majorNumber = 1;
	if(majorNumber != packinfo.version.getMajor())
	{
		std::cerr << "Este conjunto de pruebas estan Deseñado para la version mayor '" << majorNumber << "'\n";
		return EXIT_FAILURE;
	}
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	std::string& pkName = packinfo.name;
	std::string headerTest = pkName + " " + (std::string)packinfo.version + "\n" + packinfo.licence.getBrief() + "\n" + packinfo.brief + "\n";
	pSuite = CU_add_suite(headerTest.c_str(), init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Criterios de comparación semver v1.0.0", testComparators_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
			
	if ((NULL == CU_add_test(pSuite, "Validacion de parseo semver v1.0.0", testParseString_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}		
	/*if ((NULL == CU_add_test(pSuite, "Validacion de parseo v2.0.0", testParseString_v200)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}	*/
	
	if ((NULL == CU_add_test(pSuite, "Validacion de Imports semver v1.0.0", testOperations_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	
	if ((NULL == CU_add_test(pSuite, "Validacion de Operaciones semver v1.0.0", testImports_v100)))
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
