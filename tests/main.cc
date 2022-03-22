

#include "v2.hh"

int main(int argc, char *argv[])
{  
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
	bdir = "";
	std::string option;
	for(int i = 1 ; i < argc; i++)
	{
		option = argv[i];
		//bdir
		int bdirIndex = option.compare(0, 7, "--bdir=");
		if(!bdirIndex)
		{
			bdir = option.substr(7,option.size());
			std::cout << "bdir es '" << bdir << "'.\n";
		}
		int helpIndex = option.compare("--help");
		if(!helpIndex)
		{
			std::cout << "--bdir=[directory]		Directorio de contrución";
		}
	}
	oct::core::Artifact packinfo;
	oct::core::getPackageInfo(packinfo);
	if(oct::core::Error::check())
	{
		std::cerr << (const std::string&)oct::core::Error::get() << "\n";
		return EXIT_FAILURE;
	}
	
	int majorNumber = 2;
	if(majorNumber != packinfo.version.getMajor())
	{
		std::cerr << "Cree un nuevo archivo para la version '" << majorNumber << "' estas en la version'" << (std::string)packinfo.version << "'\n";
		return EXIT_FAILURE;
	}
	
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	std::string& pkName = packinfo.name;
	std::string headerTest = pkName + " " + (std::string)packinfo.version + "\n" + packinfo.licence.getText() + "\n" + packinfo.brief + "\n";
	CU_pSuite pSuite = NULL;
	pSuite = CU_add_suite(headerTest.c_str(), v2_init, v2_clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Semver for C.", v2_testsemverc)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Criterios de comparación semver v1.0.0", v2_testComparators_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
			
	if ((NULL == CU_add_test(pSuite, "Validacion de parseo semver v1.0.0", v2_testParseString_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}		
	if ((NULL == CU_add_test(pSuite, "Operaciones genéricas", v2_testOperations_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "Validacion de Operaciones semver v1.0.0", v2_testImports_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Validacion de parseo semver v2.0.0", v2_testParseString_v200)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite, "Memory modules", v2_testMemory)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Data modules", v2_testData)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Prueba de Shell class..", v2_testShell)))
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
