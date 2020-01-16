
#include <stdio.h>
#include <string.h>
#include <iostream> //for test


#include "Version.hh"
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
	

    bool v100::operator !=(const Version& obj)const
    {
        if(major != ((v100&)obj).getMajor() or minor != ((v100&)obj).getMinor() or patch != ((v100&)obj).getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator ==(const Version& obj)const
    {
        if(major == ((v100&)obj).getMajor() && minor == ((v100&)obj).getMinor() && patch == ((v100&)obj).getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator <(const Version& obj)const
    {                  
		
		if(major < 0 or ((v100&)obj).getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major > ((v100&)obj).getMajor())
        {
            return false;  
        }
		else if(major < ((v100&)obj).getMajor())
        {
            return true;  
        }

        if(minor < 0 and ((v100&)obj).getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and ((v100&)obj).getMinor() > -1)
        {
            return false;
        }
        else if(minor > ((v100&)obj).getMinor())
        {
            return false;
        } 
		else if(minor < ((v100&)obj).getMinor())
        {
            return true;
        } 
        
        if(patch < 0 and ((v100&)obj).getPatch() < 0)
        {
            return false;
        }
        else if(patch < 0 and ((v100&)obj).getPatch() > -1)
        {
            return false;
        }
        else if(patch > ((v100&)obj).getPatch())
        {
            return false;
        }
        else if(patch < ((v100&)obj).getPatch())
        {
            return true;
        }
                
        return false;
    }
	bool v100::operator >(const Version& obj)const
    {
        if(major < 0 or ((v100&)obj).getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major < ((v100&)obj).getMajor())
        {
            return false;
        }
        else if(major > ((v100&)obj).getMajor())
        {
            return true;
        }
		
        
        if(minor < 0 and ((v100&)obj).getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and ((v100&)obj).getMinor() > -1)
        {
            return true;
        }
        else if(minor > ((v100&)obj).getMinor())
        {
            return true;
        }
        else if(minor < ((v100&)obj).getMinor())
        {
            return false;
        }
        
        if(patch < 0 and ((v100&)obj).getPatch() < 0)
        {
            return true;
        }
        else if(patch < 0 and ((v100&)obj).getPatch() > -1)
        {
            return true;
        }
        else if(patch > ((v100&)obj).getPatch())
        {
            return true;
        }
        else if(patch < ((v100&)obj).getPatch())
        {
            return false;
        }
                
        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool v100::operator <=(const Version& obj)const
    {
        if((*this) == ((v100&)obj) or (*this) < ((v100&)obj))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool v100::operator >=(const Version& obj)const
    {
        if((*this) == ((v100&)obj) or (*this) > ((v100&)obj))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
	
}
}
}
