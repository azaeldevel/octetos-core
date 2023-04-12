
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
}
void v2_testParseString_v100()
{
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

    if(ver1.set("1.6.55-alpha"))
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(ver1.getMinor() == 6)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}

    if(ver1.getPatch() == 55)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}
    if(strcmp(ver1.getPrerelease().c_str(),"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}

	ver2.set("7.6.23-alpha");
	if(ver2.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
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
	}
    if(strcmp(ver2.getPrerelease().c_str(),"alpha") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
	}


	ver3.set("7.6.23-alpha5");
	if(ver3.getMajor() == 7)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
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
	}
    if(strcmp(ver3.getPrerelease().c_str(),"alpha5") == 0)
	{
		CU_ASSERT(true);
	}
	else
	{
		CU_ASSERT(false);
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
    }
    if(verMax >= verVal)
    {
        CU_ASSERT(true);
    }
    else
    {
        CU_ASSERT(false);
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
    }

	oct::core::Semver ver9;
    oct::core::Semver ver10;
    ver9.setNumbers(2);
    ver10.setNumbers(2);
    if(ver9 < ver10)
    {
        CU_ASSERT(false);
    }
	oct::core::Semver ver11;
    oct::core::Semver ver12;
    ver11.setNumbers(2);
    ver12.setNumbers(2);
    if(ver11 > ver12)
    {
        CU_ASSERT(false);
    }

	oct::core::Semver ver13;
    oct::core::Semver ver14;
    ver13.setNumbers(2,1);
    ver14.setNumbers(2,1);
    if(ver13 < ver14)
    {
        CU_ASSERT(false);
    }

	oct::core::Semver ver15;
    oct::core::Semver ver16;
    ver15.setNumbers(2,1);
    ver16.setNumbers(2,1);
    if(ver15 < ver16)
    {
        CU_ASSERT(false);
    }
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
	CU_ASSERT(version3.getPrerelease().compare("alpha") == 0);
	CU_ASSERT(strcmp(version3.getBuild(),"moon2") == 0);

	oct::core::Semver version4 = version3;
	CU_ASSERT(version4.getMajor () == 0);
	CU_ASSERT(version4.getMinor () == 1);
	CU_ASSERT(version4.getPatch () == 0);
	//if(not version4.getPrerelease ().empty()) std::cout << "Version pre : " << version2.getPrerelease () << "\n";
	CU_ASSERT(version4.getPrerelease ().compare("alpha") == 0);
	CU_ASSERT(strcmp(version4.getBuild (),"moon2") == 0);


	oct::core::Semver version5;
	version5.setNumbers(1,2,3);
	CU_ASSERT(version5.getMajor () == 1);
	CU_ASSERT(version5.getMinor () == 2);
	CU_ASSERT(version5.getPatch () == 3);

	oct::core::Semver version6;
	version6 = version5;
	CU_ASSERT(version6.getMajor () == 1);
	CU_ASSERT(version6.getMinor () == 2);
	CU_ASSERT(version6.getPatch () == 3);
	CU_ASSERT(version6.getPrerelease ().compare("#") == 0);
	CU_ASSERT(strcmp(version6.getBuild (),"#") == 0);
}
