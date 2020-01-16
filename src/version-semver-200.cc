
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
	bool Semver::set(const std::string& str)
	{
        octetos_core_Tray ty;
		ty.dysplay_erro = 0;
		ty.version = this;
        int ret = parse_string(&ty,str.c_str());
		
        if(ret == 0) return true;
        return false;
	}	
	v200 v200::getVersion() const
	{
		return v200(2,0,0);
	}
	
	
	v200::v200()
	{
        
	}
	v200::v200(short major,short minor,short patch) : semver::Semver(major,minor,patch)
    {
    }	
	v200::v200(short major,short minor) : semver::Semver(major,minor)
    {
    }
    v200::~v200()
    {
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
