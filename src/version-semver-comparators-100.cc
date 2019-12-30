 
#include "Version.hh"
#include "semver-parser.h"



// Reference https://semver.org/
namespace octetos
{
namespace core
{
namespace semver
{
    bool v100::operator !=(const Version& v)const
    {
        if(major != ((Semver&)v).major or minor != ((Semver&)v).minor or patch != ((Semver&)v).patch)
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator ==(const Version& v)const
    {
        if(major == ((Semver&)v).major && minor == ((Semver&)v).minor && patch == ((Semver&)v).patch)
        {
            return true;
        }
        
        return false;
    }
    bool v100::operator <(const Version& v)const
    {                              
        //por numeros
        if(major < ((Semver&)v).major)
        {
            return true;  
        }
        else if(major < 0 and ((v100&)v).major < 0) // no se puede retornar false y escribir un erro ya que el programa tendria la false idea de que la comparacion fue correcta con valor de retorno falso.
        {
            throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
        }
                
        if(minor < 0 and ((v100&)v).minor > -1)
        {
            return false;
        }
        else if(minor < ((v100&)v).minor)
        {
            return true;
        } 
        else if(minor > ((v100&)v).minor)
        {
            return false;
        }
        
        if(patch < 0 and ((v100&)v).patch > -1)
        {
            return false;
        }
        else if(patch < ((v100&)v).patch)
        {
            return true;
        }
                
        return false;
    }
	bool v100::operator >(const Version& v)const
    {
        //por numeros
        if(major < ((Semver&)v).major)
        {
            return false;
        }
        else if(major > ((Semver&)v).major)
        {
            return true;
        }
        else if(major < 0 and ((Semver&)v).major < 0) // no se puede retornar false y escribir un erro ya que el programa tendria la false idea de que la comparacion fue correcta con valor de retorno falso.
        {
            throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
        }
        
        if(minor < 0 and ((Semver&)v).minor > -1)
        {
            return true;
        }
        else if(minor > ((Semver&)v).minor)
        {
            return true;
        }
        else if(minor < ((Semver&)v).minor)
        {
            return false;
        }
        
        if(patch < 0 and ((Semver&)v).patch > -1)
        {
            return true;
        }
        else if(patch > ((Semver&)v).patch)
        {
            return true;
        }
                
        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool Semver::operator <=(const Version& v)const
    {
        if((*this) < v or (*this) == v)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Semver::operator >=(const Version& v)const
    {
        if((*this) > v or (*this) == v)
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