
#include<string.h>
#include <string>
#include <iostream>
#include "config.h"
#include <glibmm/i18n.h>


#include "Version.hh"

int main(int argc, char* argv[])
{
	bindtextdomain(GETTEXT_PACKAGE, OCTETOS_CORE_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
	
	const char* verstr;
	oct::core::v2::Semver ver;
	bool ver_detected = false;

	if(argc >= 1)
	{
		verstr = (const char*)argv[1];
		//std::cout << "version : " << verstr << "\n";
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
			else if(strcmp("-s", argv[i]) == 0 or strcmp("--stage", argv[i]) == 0 or strcmp("--pre-release", argv[i]) == 0)
			{
				std::cout << ver.getPrerelease ();				
			}
			else if(strcmp("-b", argv[i]) == 0 or strcmp("--build", argv[i]) == 0)
			{
				std::cout << ver.getBuild();				
			}
		}
	}

	return EXIT_SUCCESS;
}