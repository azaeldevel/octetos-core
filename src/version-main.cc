
#include<string.h>
#include <string>
#include <iostream>


#include "Version-v2.hh"

int main(int argc, char* argv[])
{
	const char* verstr;
	oct::core::v2::Semver ver;
	bool ver_detected = false;

	if(argc >= 1)
	{
		verstr = (const char*)argv[1];
		std::cout << "version : " << verstr << "\n";
		ver_detected = ver.parse(verstr);
		if(not ver_detected)
		{
			std::cerr << "No se detecto el string version.\n";
			return EXIT_FAILURE;
		}
	}

	
	if(ver_detected)
	{
		for(int i = 1; i < argc; i++)
		{
			if(strcmp("-M", argv[i]) == 0 or strcmp("--major", argv[i]) == 0)
			{
				std::cout << ver.getMajor();
			}
			else if(strcmp("-m", argv[i]) == 0 or strcmp("--minor", argv[i]) == 0)
			{
				std::cout << ver.getMinor();				
			}
			else if(strcmp("-p", argv[i]) == 0 or strcmp("--patch", argv[i]) == 0)
			{
				std::cout << ver.getPatch();				
			}
			else if(strcmp("-s", argv[i]) == 0 or strcmp("--stage", argv[i]) == 0)
			{
				std::cout << ver.getPrerelease();				
			}
		}
	}

	return EXIT_SUCCESS;
}