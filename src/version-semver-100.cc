
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
	
	Semver_v100 Semver_v100::getVersion() const
	{
		return Semver_v100(1,0,0);
	}
	
	
	Semver_v100::Semver_v100()
	{
        
	}
    /*v100::v100(const v100* v)
    {
        (*this) = *v;
    }
    v100::v100(const v100& v)
    {
        (*this) = v;
    }*/
    Semver_v100::~Semver_v100()
    {
    }
	Semver_v100::Semver_v100(short major,short minor,short patch) : Semver(major,minor,patch)
    {
    }	
	Semver_v100::Semver_v100(short major,short minor) : Semver(major,minor)
    {
    }
	

}
}
}
