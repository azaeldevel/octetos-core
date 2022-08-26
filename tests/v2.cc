
#include "v2.hh"

int v2_init(void)
{
	return 0;
}
int v2_clean(void)
{
	return 0;
}

void v2_testImports_v100()
{
	oct::core::Semver verPQ;
	if(oct::core::Error::check())
	{
		std::cerr << (std::string)oct::core::Error::get() << "\n";
		return;
	}
	verPQ.set(80105,oct::core::Semver::ImportCode::PostgreSQL);
	if(verPQ.getMajor() == 8)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}
	//std::string strverpq = verPQ.toString();
	//std::cout << "verPQ = " << strverpq << "\n";
}

void v2_testParseString_v100()
{
	oct::core::Semver ver1,ver2,ver3;

	if(oct::core::Error::check())
	{
		CU_ASSERT(false);
		//std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	ver2.set("7.6.23-alpha");
	if(ver2.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver2.getPrerelease().c_str(),"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}


	ver3.set("7.6.23-alpha5");
	if(ver3.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver3.getPrerelease().c_str(),"alpha5") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}
	oct::core::Semver ver4;
	ver4.set("7.6.23-betar12");
	if(ver4.getPrerelease().compare("betar12") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver5;
	if(ver5.extractNumbers("7.6.23"))
	{
		//std::cerr << "Extracted :" << (std::string)ver5 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver6;
	if(ver6.extractNumbers("7.6.23"))
	{
		//std::cerr << "Extracted :" << (std::string)ver6 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver7;
	if(ver7.set("7.6.23-betar1.2"))
	{
		//std::cerr << "Str :" << (std::string)ver7 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver8;
	if(ver8.set("1.2.0-alpha"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver9;
	if(ver9.set("1.2.0-alpha1"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver10;
	if(ver10.set("1.2.0-alpha.1"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver11;
	if(ver11.set("1.2.0"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver12;
	if(ver12.set("1.2.0"))//no deve aceptar letras en la secion numerica
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	oct::core::Semver ver13;
    if(ver13.set("0.1.0-alpha"))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}


	oct::core::Semver ver14;
    if(ver14.extractNumbers("0.1.0-alpha"))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

}

void v2_reduced_parser()
{
	//bool Semver::parser(const char* )
	oct::core::Semver ver15;
	CU_ASSERT(ver15.parse("5.30"));
	CU_ASSERT(ver15.getMajor() == 5);
	CU_ASSERT(ver15.getMinor() == 30);
	//std::cout << "M : " << ver15.getMajor() << "\n";
	//std::cout << "m : " << ver15.getMinor() << "\n";

	oct::core::Semver ver16;
	CU_ASSERT(ver16.parse("5.30-alpha"));
	CU_ASSERT(ver16.getMajor() == 5);
	CU_ASSERT(ver16.getMinor() == 30);
	CU_ASSERT(ver16.getPrerelease().compare("alpha") == 0);
	//std::cout << "prerelease : " << ver16.getPrerelease() << "\n";

	oct::core::Semver ver17;
	CU_ASSERT(ver17.parse("5.30-alpha+mountain"));
	CU_ASSERT(ver17.getMajor() == 5);
	CU_ASSERT(ver17.getMinor() == 30);
	CU_ASSERT(ver17.getPrerelease().compare("alpha") == 0);
	CU_ASSERT(strcmp(ver17.getBuild(),"mountain") == 0);

	oct::core::Semver ver18;
	CU_ASSERT(ver18.parse("5.30+mountain"));
	CU_ASSERT(ver18.getMajor() == 5);
	CU_ASSERT(ver18.getMinor() == 30);
	CU_ASSERT(strcmp(ver18.getBuild(),"mountain") == 0);
}

void v2_testParseString_v200()
{
	oct::core::Semver ver1,ver2,ver3;

	if(oct::core::Error::check())
	{
		CU_ASSERT(false);
		std::cerr << (std::string)oct::core::Error::get() << "\n";
		return;
	}

    if(ver1.set("1.6.55-alpha"))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}

	ver2.set("7.6.23-alpha");
	if(ver2.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver2.getPrerelease().c_str(),"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}


	ver3.set("7.6.23-alpha5");
	if(ver3.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}
    if(strcmp(ver3.getPrerelease().c_str(),"alpha5") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}
	oct::core::Semver ver4;
	ver4.set("7.6.23-betar1");
	if(ver4.getPrerelease().compare("betar1") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
	}


	oct::core::Semver ver5;
	if(ver5.set("5.0.0-alpha\n"))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
}



void v2_testComparators_v100()
{
        oct::core::Semver ver1;
        oct::core::Semver ver2;

        ver1.setNumbers(1,2,3);
        ver2.setNumbers(1,2,5);
        //std::cout << "test 1" << std::endl;
        if(ver1 >= ver2)
        {
			CU_ASSERT(false);
			if(oct::core::Error::check())
			{
				std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
			if(oct::core::Error::check())
			{
				std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
			if(oct::core::Error::check())
			{
				std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
			if(oct::core::Error::check())
			{
				std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
			if(oct::core::Error::check())
			{
				std::cerr << (std::string)oct::core::Error::get() << "\n";
				return;
			}
        }
        //std::cout << "test 4" << std::endl;
        if(ver2 >= ver1)
        {
                CU_ASSERT(false);
			if(oct::core::Error::check())
			{
				std::cerr << (const std::string&)oct::core::Error::get() << "\n";
				return;
			}
        }
        else
        {
                CU_ASSERT(true);
        }

    //x simepre es amjor que x.y
    oct::core::Semver ver3;
    oct::core::Semver ver4;
    ver3.setNumbers(1);
    ver4.setNumbers(1,50);
    if(ver3 >= ver4)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
    }
    if(ver3 <= ver4)
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
    }
    if(ver3 < ver4)
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
			return;
		}
    }
    else
    {
        CU_ASSERT(true);
    }




    //x simepre es amjor que x.y
    oct::core::Semver ver5;
    oct::core::Semver ver6;
    ver5.setNumbers(1,50);
    ver6.setNumbers(1,50,100);
    if(ver5 >= ver6)
    {
        CU_ASSERT(true);
    }
    else
    {
		CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
    }
    if(ver5 < ver6)
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
			return;
		}
    }

    oct::core::Semver verMin;
    oct::core::Semver verMax;
    oct::core::Semver verVal;
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
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
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
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
			return;
		}
    }

    oct::core::Semver ver7;
    oct::core::Semver ver8;
    ver7.setNumbers(4,4,20);
    ver8.setNumbers(3,2);
    if(ver7 >= ver8)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
			return;
		}
    }

	oct::core::Semver ver9;
    oct::core::Semver ver10;
    ver9.setNumbers(2);
    ver10.setNumbers(2);
    if(ver9 < ver10)
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
			return;
		}
    }
	oct::core::Semver ver11;
    oct::core::Semver ver12;
    ver11.setNumbers(2);
    ver12.setNumbers(2);
    if(ver11 > ver12)
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
			return;
		}
    }

	oct::core::Semver ver13;
    oct::core::Semver ver14;
    ver13.setNumbers(2,1);
    ver14.setNumbers(2,1);
    if(ver13 < ver14)
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (const std::string&)oct::core::Error::get() << "\n";
			return;
		}
    }

	oct::core::Semver ver15;
    oct::core::Semver ver16;
    ver15.setNumbers(2,1);
    ver16.setNumbers(2,1);
    if(ver15 < ver16)
    {
        CU_ASSERT(false);
		if(oct::core::Error::check())
		{
			std::cerr << (std::string)oct::core::Error::get() << "\n";
			return;
		}
    }
}

void v2_testOperations_v100()
{
	/*time_t seconds = time (NULL);
	oct::core::Artifact packinfo;
	oct::core::getPackageInfo(packinfo);
	std::string str = std::to_string(seconds);
	std::string filename = packinfo.name;
	filename += "-" + str + ".cfg";
	std::string fullName = bdir + "/" + filename;
	if(packinfo.write(fullName))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}*/

	//oct::core::Artifact pk;
	//pk.read (filename);
}


void v2_testMemory()
{
	/*unsigned short LENGTH = 1000;
	unsigned short TESTS = 10000;

	int* segment1;
	clock_t start1 = clock();
	for(unsigned short test = 0; test < TESTS; test++)
	{
		segment1 = new int[LENGTH];
		for(int i = 0; i < LENGTH; i++)
		{
			segment1[i] = i;
		}
		delete [] segment1;
	}
	clock_t stop1 = clock();
	clock_t duration1 = stop1 - start1;


	int* segment2[LENGTH];
	clock_t start2 = clock();
	for(unsigned short test = 0; test < TESTS; test++)
	{
		for(int i = 0; i < LENGTH; i++)
		{
			segment2[i] = new int;
			(*segment2[i]) = i;
		}
		for(int i = 0; i < LENGTH; i++)
		{
			delete segment2[i];
		}
	}
	clock_t stop2 = clock();
	clock_t duration2 = stop2 - start2;
	float speed2 = duration2/duration1;
	//std::cout  << "Lentiud 2 : " << duration2 << "/" << duration1 << "=" << speed2 << "\n";


	int* segment3[LENGTH];
	clock_t start3 = clock();
	oct::core::MiniGC<int> minigc(LENGTH);
	for(unsigned short test = 0; test < TESTS; test++)
	{
		for(unsigned short i = 0; i < LENGTH; i++)
		{
			segment3[i] = minigc.create();
			*segment3[i] = i;
		}
		for(unsigned short i = 0; i < LENGTH; i++)
		{
			minigc.destroy(segment3[i]);
		}
	}
	clock_t stop3 = clock();
	clock_t duration3 = stop3 - start3;
	float speed3 = duration3/duration1;
	//std::cout << "Lentiud 3 : " << duration3 << "/" << duration1 << "=" << speed3 << "\n";

	float speed = speed3/speed2;
	float ventaja = 1.0 - speed;
	//if(speed < 1.0) std::cout << "Hay una ventaj del " << 100.0 * ventaja << "%\n";
	//else if(fabs(speed - 1.0) <= 0.001) std::cout << "No hay efecto\n";
	//else std::cout << "Hay una desventaja del " << fabs(100.0 * ventaja) << "%\n";

	char hostname[HOST_NAME_MAX + 1];
  	gethostname(hostname, HOST_NAME_MAX + 1);
	std::string filename = SRCDIRTEST;
	filename = filename + "/statics.csv";
	std::ofstream fn(filename,std::ios::app | std::ios::in | std::ios::ate);
	fn << speed2 << "," << speed3 << "," << ventaja << "," << hostname << "\n";*/

	oct::core::Allocator<int>::List list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(3);
	list1.push_back(4);
	list1.push_back(5);
	list1.push_back(6);
	list1.push_back(7);
	list1.push_back(8);
	list1.push_back(9);
	if(list1.get_size() == 10)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	if(list1.first().object == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
	if(list1.last().object == 9)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}

	oct::core::Allocator<int>::Node* node1 = &list1.first();
	int node1_count = 0;
	while(node1 != NULL)
	{
		if(node1_count == node1->object)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		node1 = node1->get_posteriory();
		node1_count++;
	}

	node1 = &list1.first();
	//std::cout << "pMember : " << &node1->object << "\n";
	//std::cout << "pObject " << node1 << "\n";
	if((void*)&node1->object == (void*)node1)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}

	node1 = &list1.last();
	node1_count = 9;
	while(node1 != NULL)
	{
		if(node1_count == node1->object)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		node1 = node1->get_previous();
		node1_count--;
	}


	oct::core::Allocator<int>::List list2,list3;
	list2.push_back(0);
	list2.push_back(1);
	list2.push_back(2);
	list2.push_back(3);
	list2.push_back(4);
	list2.push_back(5);
	list2.push_back(6);
	list2.push_back(7);
	list2.push_back(8);
	list2.push_back(9);
	while(list2.get_size() > 0)
	{
		list3.pull(list2.last());
	}
	node1 = &list3.first();
	node1_count = 9;
	while(node1 != NULL)
	{
		//std::cout << "Number : " << node1->object << "\n";
		if(node1_count == node1->object)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		node1 = node1->get_posteriory();
		node1_count--;
	}

	oct::core::Allocator<int>::List list4,list5;
	list4.push_back(0);
	list4.push_back(1);
	list4.push_back(2);
	list4.push_back(3);
	list4.push_back(4);
	list4.push_back(5);
	list4.push_back(6);
	list4.push_back(7);
	list4.push_back(8);
	list4.push_back(9);
	while(list4.get_size() > 0)
	{
		list5.pull(list4.first());
	}
	node1 = &list5.first();
	node1_count = 0;
	while(node1 != NULL)
	{
		if(node1_count == node1->object)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		node1 = node1->get_posteriory();
		node1_count++;
	}

	std::vector<int*> alloc1_datas(10);
	oct::core::Allocator<int> alloc1;
	for(unsigned int i = 0; i < alloc1_datas.size(); i++)
	{
		alloc1_datas[i] = alloc1.create();
		*alloc1_datas[i] = i;
	}
	for(unsigned int i = 0; i < alloc1_datas.size(); i++)
	{
		if(*alloc1_datas[i] == i)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}

	std::vector<int*> alloc2_datas(10);
	oct::core::Allocator<int> alloc2;
	for(unsigned int i = 0; i < alloc1_datas.size(); i++)
	{
		alloc2_datas[i] = alloc2.create();
		*alloc2_datas[i] = i;
	}
	for(unsigned int i = 0; i < alloc2_datas.size(); i++)
	{
		if(*alloc1_datas[i] == i)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}

	oct::core::Allocator<int>::List& list6 = alloc2.get_used();
	unsigned int sizePrev = list6.get_size();
	alloc2.destroy(alloc2_datas[3]);
	unsigned int sizePost = list6.get_size();
	//std::cout << "sizePrev = " << sizePrev << "\n";
	//std::cout << "sizePost = " << sizePost << "\n";
	if(sizePrev == sizePost + 1)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}

}

void v2_testData()
{
	oct::core::Wall<int> wall1(5);
	wall1[0] = 1;
	wall1[1] = 2;
	wall1[2] = 3;
	wall1[3] = 4;
	wall1[4] = 5;

	for(unsigned int i = 0; i < wall1.get_size(); i++)
	{
		if(wall1[i] = i + 1)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
}
void v2_testShell()
{
	oct::core::Shell shell;
	std::list<std::string> dirs;
	std::string toFind = "configure.ac";
	shell.ls(dirs);
	std::list<std::string>::iterator itFind = std::find(dirs.begin(),dirs.end(),toFind);
	if(itFind != dirs.end())
	{
		CU_ASSERT(false);
		std::cerr << "No ejecutar en el directorio raiz, las pruebas se ejecutan en el directorio correspondiente\n";
		return;
	}
	for(const std::string str : dirs)
	{
		if(str.compare(".") == 0)
		{
			CU_ASSERT(false)
		}
		else
		{
			CU_ASSERT(true)
		}
		if(str.compare("..") == 0)
		{
			CU_ASSERT(false)
		}
		else
		{
			CU_ASSERT(true)
		}
	}


	std::string dm = std::to_string(oct::core::getDayID()) + "/" + std::to_string(oct::core::getTimeID());
	shell.mkdir(dm,true);
	for(unsigned int i = 0; i < 10; i++)
	{
		shell.mkdir(dm + "/" + std::to_string(i));
	}
	for(unsigned int i = 0; i < 10; i++)
	{
		if(shell.exists(dm + "/" + std::to_string(i))) CU_ASSERT(true)
		else CU_ASSERT(false)
	}
	if(shell.rm(dm,true)) CU_ASSERT(true)
	else CU_ASSERT(false)

	unsigned int idtime1 = oct::core::getTimeID();
	if(shell.exists(std::to_string(idtime1)))
	{
		return; //se omite la prueba, puede ser que haya sido creado por el usuario.
	}

	if(shell.exists(std::to_string(idtime1))) CU_ASSERT(false)
	else CU_ASSERT(true);

	shell.mkdir(std::to_string(idtime1));

	if(shell.exists(std::to_string(idtime1))) CU_ASSERT(true)
	else CU_ASSERT(false);

	shell.rm(std::to_string(idtime1));

	if(shell.exists(std::to_string(idtime1))) CU_ASSERT(false)
	else CU_ASSERT(true);

	std::string dir1 = "dir1";
	if(not shell.exists(dir1)) shell.mkdir(dir1);

	if(shell.exists(dir1)) CU_ASSERT(true)
	else CU_ASSERT(false)

	if(shell.rm(dir1)) CU_ASSERT(true)
	else CU_ASSERT(false)
}

void v2_developing()
{
	oct::core::Exception ex1;
	CU_ASSERT(ex1.getLine() == 0);
	CU_ASSERT(ex1.getFilename() == NULL);

	oct::core::Semver version;
	version.setNumbers(0,1,0);
	CU_ASSERT(version.getMajor () == 0);
	CU_ASSERT(version.getMinor () == 1);
	CU_ASSERT(version.getPatch () == 0);
	version.setPrerelease("alpha");
	CU_ASSERT(version.getPrerelease ().compare("alpha") == 0);

	
	oct::core::Semver version2("0.1.0-alpha");
	CU_ASSERT(version2.getMajor () == 0);
	CU_ASSERT(version2.getMinor () == 1);
	CU_ASSERT(version2.getPatch () == 0);
	//if(not version2.getPrerelease ().empty()) std::cout << "Version pre : " << version2.getPrerelease () << "\n";
	CU_ASSERT(version2.getPrerelease ().compare("alpha") == 0);
	
	oct::core::Semver version3("0.1.0-alpha+moon2");
	CU_ASSERT(version3.getMajor () == 0);
	CU_ASSERT(version3.getMinor () == 1);
	CU_ASSERT(version3.getPatch () == 0);
	//if(not version3.getPrerelease ().empty()) std::cout << "Version pre : " << version2.getPrerelease () << "\n";
	CU_ASSERT(version3.getPrerelease ().compare("alpha") == 0);
	CU_ASSERT(strcmp(version3.getBuild (),"moon2") == 0);
}
