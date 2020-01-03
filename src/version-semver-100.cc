
#include <stdio.h>
#include <string.h>
#include <iostream> //for test


#include "Version.hh"
#include "semver-parser.h"
#include "Error.hh"


// Reference https://semver.org/
namespace octetos
{
namespace core
{
namespace semver
{
	
	v100 v100::getVersion() const
	{
		return semver::v100(1,0,0);
	}
	
	
    
	
	v100::v100()
	{
        
	}
	v100::v100(short major,short minor,short patch) : semver::Semver(major,minor,patch)
    {
    }	
	v100::v100(short major,short minor) : semver::Semver(major,minor)
    {
    }
    v100::~v100()
    {
    }
	

}
}
}
