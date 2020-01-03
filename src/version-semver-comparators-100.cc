 
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
        if(major != obj.major or minor != obj.minor or patch != obj.patch)
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator ==(const Semver& obj)const
    {
        if(major == obj.major && minor == obj.minor && patch == obj.patch)
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator <(const Semver& obj)const
    {                              
        //por numeros
        if(major < obj.major)
        {
            return true;  
        }
        else if(major < 0 and obj.major < 0) // no se puede retornar false y escribir un erro ya que el programa tendria la false idea de que la comparacion fue correcta con valor de retorno falso.
        {
            throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
        }
                
        if(minor < 0 and obj.minor > -1)
        {
            return false;
        }
        else if(minor < obj.minor)
        {
            return true;
        } 
        else if(minor > obj.minor)
        {
            return false;
        }
        
        if(patch < 0 and obj.patch > -1)
        {
            return false;
        }
        else if(patch < obj.patch)
        {
            return true;
        }
                
        return false;
    }
	bool v100::operator >(const Semver& obj)const
    {
        //por numeros
        if(major < obj.major)
        {
            return false;
        }
        else if(major > obj.major)
        {
            return true;
        }
        else if(major < 0 and obj.major < 0) // no se puede retornar false y escribir un erro ya que el programa tendria la false idea de que la comparacion fue correcta con valor de retorno falso.
        {
            throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
        }
        
        if(minor < 0 and obj.minor > -1)
        {
            return true;
        }
        else if(minor > obj.minor)
        {
            return true;
        }
        else if(minor < obj.minor)
        {
            return false;
        }
        
        if(patch < 0 and obj.patch > -1)
        {
            return true;
        }
        else if(patch > obj.patch)
        {
            return true;
        }
                
        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool v100::operator <=(const Semver& obj)const
    {
        if((*this) < obj or (*this) == obj)
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
        if((*this) > obj or (*this) == obj)
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