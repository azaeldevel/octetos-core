
#include <CUnit/Basic.h>
#include <iostream>
#include <cstdlib>
#include <Artifact.hh>
#include <time.h>

#include "config.h"
#include "semver-lexer.h"

static std::string bdir;

int init(void)
{
	return 0;
}
int clean(void)
{
	return 0;
}

void testImports_v100()
{
	octetos::core::Semver verPQ;
	if(octetos::core::Error::check())
	{
		std::cerr << (std::string)octetos::core::Error::get() << "\n";
		return;
	}
	verPQ.set(80105,octetos::core::Semver::ImportCode::PostgreSQL);
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
	octetos::core::Semver ver1,ver2,ver3;
	
	if(octetos::core::Error::check())
	{
		CU_ASSERT(false);
		//std::cerr << (std::string)octetos::core::Error::get() << "\n";
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
	octetos::core::Semver ver4;
	ver4.set("7.6.23-betar12");
	if(ver4.getPrerelease().compare("betar12") == 0)
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
	
	octetos::core::Semver ver5;
	if(ver5.extractNumbers("7.6.23"))
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
	
	octetos::core::Semver ver6;
	if(ver6.extractNumbers("7.6.23"))
	{
		//std::cerr << "Extracted :" << (std::string)ver6 << "\n";
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
	
	octetos::core::Semver ver7;
	if(ver7.set("7.6.23-betar1.2"))
	{
		//std::cerr << "Str :" << (std::string)ver7 << "\n";
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

	octetos::core::Semver ver8;
	if(ver8.set("1.2.0-alpha"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
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

	octetos::core::Semver ver9;
	if(ver9.set("1.2.0-alpha1"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
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

	octetos::core::Semver ver10;
	if(ver10.set("1.2.0-alpha.1"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
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
	
	octetos::core::Semver ver11;
	if(ver11.set("1.2.0"))
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
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
	
	octetos::core::Semver ver12;
	if(ver12.set("1.2.0"))//no deve aceptar letras en la secion numerica
	{
		//std::cerr << "Str :" << (std::string)ver8 << "\n";
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
	octetos::core::Semver ver1,ver2,ver3;
	
	if(octetos::core::Error::check())
	{
		CU_ASSERT(false);
		std::cerr << (std::string)octetos::core::Error::get() << "\n";
		return;
	}
	
    if(ver1.set("1.6.55-alpha"))
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
    
	ver2.set("7.6.23-alpha"); 
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
    if(strcmp(ver2.getPrerelease().c_str(),"alpha") == 0)
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
	
    
	ver3.set("7.6.23-alpha5");     
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
    if(strcmp(ver3.getPrerelease().c_str(),"alpha5") == 0)
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
	octetos::core::Semver ver4;
	ver4.set("7.6.23-betar1");
	if(ver4.getPrerelease().compare("betar1") == 0)
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
}



void testComparators_v100()
{
        octetos::core::Semver ver1;
        octetos::core::Semver ver2;
        
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
    octetos::core::Semver ver3;
    octetos::core::Semver ver4;
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
    octetos::core::Semver ver5;
    octetos::core::Semver ver6;
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
    
    octetos::core::Semver verMin;
    octetos::core::Semver verMax;
    octetos::core::Semver verVal;
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
    
    octetos::core::Semver ver7;
    octetos::core::Semver ver8;
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

	octetos::core::Semver ver9;
    octetos::core::Semver ver10;
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
	octetos::core::Semver ver11;
    octetos::core::Semver ver12;
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
	
	octetos::core::Semver ver13;
    octetos::core::Semver ver14;
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
	
	octetos::core::Semver ver15;
    octetos::core::Semver ver16;
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
	time_t seconds = time (NULL);
	octetos::core::Artifact packinfo;
	octetos::core::getPackageInfo(packinfo);
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
	}

	//octetos::core::Artifact pk;
	//pk.read (filename);
}

void testsemverc()
{
	const char *strver1 = "1.0.2-alpha";
	octetos_core_Semver ver1;
	if(octetos_core_toObject(strver1,&ver1))
	{
		if(ver1.major == 1)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		
		if(ver1.minor == 0)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
		
		if(ver1.patch == 2)
		{
			CU_ASSERT(true);
		}
		else
		{
			CU_ASSERT(false);
		}
	}
	else
	{
		CU_ASSERT(false);
	}
}
void testTemporally()
{
	octetos::core::Semver ver;
	ver.set("1.0.2-alpha");
	//std::cout << "Str ver :" << (std::string)ver << "\n";
}


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
	octetos::core::Artifact packinfo;
	octetos::core::getPackageInfo(packinfo);
	if(octetos::core::Error::check())
	{
		std::cerr << (const std::string&)octetos::core::Error::get() << "\n";
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
	pSuite = CU_add_suite(headerTest.c_str(), init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Semver for C.", testsemverc)))
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
	if ((NULL == CU_add_test(pSuite, "Operaciones genéricas", testOperations_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "Validacion de Operaciones semver v1.0.0", testImports_v100)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	/*if ((NULL == CU_add_test(pSuite, "Prueba temporal..", testTemporally)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}*/
	
	if ((NULL == CU_add_test(pSuite, "Validacion de parseo semver v2.0.0", testParseString_v200)))
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
