
#include <stdio.h>


#include "semver-parser.h"

int main()
{
	octetos_Semver ver1,ver2,ver3;
	octetos_Semver_init(&ver1);
	octetos_Semver_init(&ver2);
	octetos_Semver_init(&ver3);
	struct Tray ty1,ty2,ty3;
	ty1.version = &ver1;
	ty1.dysplay_erro = 1;
	ty2.version = &ver2;
	ty2.dysplay_erro = 1;
	ty3.version = &ver3;
	ty3.dysplay_erro = 1;
	printf( ">>>\n");
	parse_string(&ty1,"1.6.55-alpha");    
    printf( "M: %d\n",ty1.version->major);
    printf( "m: %d\n",ty1.version->minor);
    printf( "p: %d\n",ty1.version->patch);
    if(ty1.version->prerelease) printf( "prerelease: %s\n",ty1.version->prerelease);
    printf( ">>>\n");
	parse_string(&ty2,"7.6.23-alpha-1");    
    printf( "M: %d\n",ty2.version->major);
    printf( "m: %d\n",ty2.version->minor);
    printf( "p: %d\n",ty2.version->patch);
    if(ty2.version->prerelease) printf( "prerelease: %s\n",ty2.version->prerelease);
    printf( ">>>\n");
	parse_string(&ty3,"7.6.23-alpha5-2");    
    printf( "M: %d\n",ty3.version->major);
    printf( "m: %d\n",ty3.version->minor);
    printf( "p: %d\n",ty3.version->patch);
    if(ty3.version->prerelease) printf( "prerelease: %s\n",ty3.version->prerelease);
	
	
	return 0;
}
