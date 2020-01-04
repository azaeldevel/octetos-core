 
#include "Version.hh"
#include "semver-parser.h"



// Reference https://semver.org/
namespace octetos
{
namespace core
{
namespace semver
{
    bool v100::operator !=(const Semver& obj)const
    {
        if(major != obj.getMajor() or minor != obj.getMinor() or patch != obj.getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator ==(const Semver& obj)const
    {
        if(major == obj.getMajor() && minor == obj.getMinor() && patch == obj.getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator <(const Semver& obj)const
    {                  
		
		if(major < 0 or obj.getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major > obj.getMajor())
        {
            return false;  
        }
		else if(major < obj.getMajor())
        {
            return true;  
        }

        if(minor < 0 and obj.getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and obj.getMinor() > -1)
        {
            return false;
        }
        else if(minor > obj.getMinor())
        {
            return false;
        } 
		else if(minor < obj.getMinor())
        {
            return true;
        } 
        
        if(patch < 0 and obj.getPatch() < 0)
        {
            return false;
        }
        else if(patch < 0 and obj.getPatch() > -1)
        {
            return false;
        }
        else if(patch > obj.getPatch())
        {
            return false;
        }
        else if(patch < obj.getPatch())
        {
            return true;
        }
                
        return false;
    }
	bool v100::operator >(const Semver& obj)const
    {
        if(major < 0 or obj.getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major < obj.getMajor())
        {
            return false;
        }
        else if(major > obj.getMajor())
        {
            return true;
        }
		
        
        if(minor < 0 and obj.getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and obj.getMinor() > -1)
        {
            return true;
        }
        else if(minor > obj.getMinor())
        {
            return true;
        }
        else if(minor < obj.getMinor())
        {
            return false;
        }
        
        if(patch < 0 and obj.getPatch() < 0)
        {
            return true;
        }
        else if(patch < 0 and obj.getPatch() > -1)
        {
            return true;
        }
        else if(patch > obj.getPatch())
        {
            return true;
        }
        else if(patch < obj.getPatch())
        {
            return false;
        }
                
        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool v100::operator <=(const Semver& obj)const
    {
        if((*this) == obj or (*this) < obj)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool v100::operator >=(const Semver& obj)const
    {
        if((*this) == obj or (*this) > obj)
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