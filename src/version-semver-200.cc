
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
	const Semver& v200::getVersion() const
	{
		return *version;
	}
    v200* v200::version = new v200(2,0,0);

	
	v200::v200()
	{
		suffix = "200";
		loadParser(suffix);
	}
	v200::v200(short major,short minor,short patch) : Semver(major,minor,patch)
    {
		suffix = "200";
		loadParser(suffix);
    }	
	v200::v200(short major,short minor) : Semver(major,minor)
    {
		suffix = "200";
		loadParser(suffix);
    }
    v200::~v200()
    {
    }	
	v200::v200(const v200& obj) : semver::Semver( obj)
	{
		suffix = "200";
		loadParser(suffix);	
	}

    bool v200::operator !=(const Version& obj)const
    {
        if(major != ((v200&)obj).getMajor() or minor != ((v200&)obj).getMinor() or patch != ((v200&)obj).getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool v200::operator ==(const Version& obj)const
    {
        if(major == ((v200&)obj).getMajor() && minor == ((v200&)obj).getMinor() && patch == ((v200&)obj).getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool v200::operator <(const Version& obj)const
    {                  
		
		if(major < 0 or ((v200&)obj).getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major > ((v200&)obj).getMajor())
        {
            return false;  
        }
		else if(major < ((v200&)obj).getMajor())
        {
            return true;  
        }

        if(minor < 0 and ((v200&)obj).getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and ((v200&)obj).getMinor() > -1)
        {
            return false;
        }
        else if(minor > ((v200&)obj).getMinor())
        {
            return false;
        } 
		else if(minor < ((v200&)obj).getMinor())
        {
            return true;
        } 
        
        if(patch < 0 and ((v200&)obj).getPatch() < 0)
        {
            return false;
        }
        else if(patch < 0 and ((v200&)obj).getPatch() > -1)
        {
            return false;
        }
        else if(patch > ((v200&)obj).getPatch())
        {
            return false;
        }
        else if(patch < ((v200&)obj).getPatch())
        {
            return true;
        }
                
        return false;
    }
	bool v200::operator >(const Version& obj)const
    {
        if(major < 0 or ((v200&)obj).getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major < ((v200&)obj).getMajor())
        {
            return false;
        }
        else if(major > ((v200&)obj).getMajor())
        {
            return true;
        }
		
        
        if(minor < 0 and ((v200&)obj).getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and ((v200&)obj).getMinor() > -1)
        {
            return true;
        }
        else if(minor > ((v200&)obj).getMinor())
        {
            return true;
        }
        else if(minor < ((v200&)obj).getMinor())
        {
            return false;
        }
        
        if(patch < 0 and ((v200&)obj).getPatch() < 0)
        {
            return true;
        }
        else if(patch < 0 and ((v200&)obj).getPatch() > -1)
        {
            return true;
        }
        else if(patch > ((v200&)obj).getPatch())
        {
            return true;
        }
        else if(patch < ((v200&)obj).getPatch())
        {
            return false;
        }
                
        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool v200::operator <=(const Version& obj)const
    {
        if((*this) == ((v200&)obj) or (*this) < ((v200&)obj))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool v200::operator >=(const Version& obj)const
    {
        if((*this) == ((v200&)obj) or (*this) > ((v200&)obj))
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
