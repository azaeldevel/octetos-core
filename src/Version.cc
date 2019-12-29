
#include <stdio.h>
#include <string.h>
#include <iostream> //for test


#include "Version.hh"
#include "semver-parser.h"



// Reference https://semver.org/
namespace octetos
{
namespace core
{
namespace semver
{
	v100 v100::getVersion() const
	{
		return v100(1,0,0);
	}
	
	bool v100::importFactors(unsigned long ver,Imports import)
	{
		if(import == Imports::MySQL)
		{
			unsigned long actualVer = ver;
			major = actualVer/10000;
			actualVer -= (10000 * major);
			minor = actualVer/100;
			actualVer -= (100 * minor);
			patch = actualVer;
			
			return true;
		}	

		return false;
	}
	bool v100::extractNumbers(const std::string& str)
	{
        Tray ty;
		ty.dysplay_erro = 0;
		std::string strcmd = "extract numbers from ";
		strcmd += str;
		//printf("command : %s\n",strcmd.c_str());
        int ret = parse_string(&ty,strcmd.c_str());
        major = ty.version.major;
        minor = ty.version.minor;
        patch = ty.version.patch;
		
        if(ret == 0) return true;
        return false;
	}
		
	bool v100::set(const std::string& str)
	{
        Tray ty;
		ty.dysplay_erro = 0;
        int ret = parse_string(&ty,str.c_str());
        major = ty.version.major;
        minor = ty.version.minor;
        patch = ty.version.patch;
		stage = ty.version.stage;
		stageNumber = ty.version.stageNumber;
		//Version::build = ty.version.build;
		octetos_version_Version::build = ty.version.build;
		
        if(ret == 0) return true;
        return false;
	}
	/*bool Version::operator =(const std::string& str)
    {
		return set(str);
    }*/
	const char* v100::getStageString() const
	{
		return octetos_core_Stage_getString(stage);
	}
    /*bool Version::from(const std::string& str)
    {
        Tray ty;
		ty.dysplay_erro = 0;
        int ret = parse_string(&ty,str.c_str());
        major = ty.version.major;
        minor = ty.version.minor;
        patch = ty.version.patch;
		stage = ty.version.stage;
		stageNumber = ty.version.stageNumber;
		//Version::build = ty.version.build;
		octetos_version_Version::build = ty.version.build;
		
        if(ret == 0) return true;
        return false;
    } */
	
    const char* v100::Build::getString()const
    {
        if(type == eBuild::string_e)
        {
            return value.string;
        }
        else
        {
            throw Error("El tipo de este dato no es 'una cadena de texto.'",0);
        }
    }
    /*Version* Version::Build::getVersion() const
    {
        if(type == etype::version)
        {
                return val.version;
        }
        else
        {
            throw Error("El tipo de este dato no es 'Version'",0);
        }
    }*/
    unsigned long v100::Build::getUL() const
    {
        if(type == eBuild::ul_e)
        {
                return value.ul;
        }
        else
        {
            throw Error("El tipo de este dato no es 'unsigned long'",0);
        }
    }
    v100::Build::eBuild v100::Build::getType()const
    {
        return type;
    }    
    /*Version::Build& Version::Build::operator =(Version* build)
    {
        val.version = build;
        type = etype::version;
        
        return *this;
    }*/
    v100::Build& v100::Build::operator =(unsigned long ul)
    {
        type = eBuild::ul_e;
        value.ul = ul;
        
        return *this;
    }
    v100::Build& v100::Build::operator =(const char* str)
    {
        
        strcpy(value.string,str);
        type = eBuild::string_e;        
        return *this;
    }
    
    v100::Build::~Build()
    {
        /*if(build.getType() == Build::etype::version)
        {
            delete this->build.getVersion();
        }*/
        if(type == Build::eBuild::string_e)
        {
            delete this->value.string;
        }
    }
    
    
    
    
    

    v100::v100(const v100* v)
    {
        (*this) = *v;
    }
    v100::v100(const v100& v)
    {
        (*this) = v;
    }
    v100::~v100()
    {
    }
    /*void Version::setBuild(const Version& v)
    {
        Version* ver = new Version(v);
        this->build = ver;
    }*/
    void v100::setBuild(const std::string& str)
    {
        //std::string* str = new std::string(v);
        this->build = str.c_str();
    }
    /*void Version::setBuild(const Version* v)
    {
        Version* ver = new Version(v);
        this->build = ver;        
    }  */  
        v100::InvalidComparison::InvalidComparison(const std::string& msg):Error(msg,Error::ERROR_VERSION_INVALID_COMPARISON)
        {
                
        }
        v100::InvalidComparison::InvalidComparison(const std::string& msg ,std::string filename,int lineNumber):Error(msg,Error::ERROR_VERSION_INVALID_COMPARISON,filename,lineNumber)
        {
                
        }
    void v100::init()
    {
		major = -1;
		minor = -1;
		patch = -1;
		stage = unknown;
		stageNumber = -1;
        build = (unsigned long)0;
        //name = "";
    }
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
        const v100& v100::operator =(const v100& v)
        {
                this->major = v.major;
                this->minor = v.minor;
                this->patch = v.patch;
                this->build = v.build;
                this->stage = v.stage;
                //this->name = v.name;
                
                return *this;
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
    /*bool Version::operator >=(const Version& v)
    {
        //por numeros
        if(major > -1 and v.major > -1)
        {
            if(major > v.major)
            {
                //std::cout << "por major" << std::endl;
                return true;
            }
            else if(major < v.major) 
            {
                return false;
            }                                
        }
        else // no se puede retornar false y escribir un erro ya que el programa tendria la false idea de que la comparacion fue correcta con valor de retorno falso.
        {
            throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
        }
               
               
        if(minor > -1 and v.minor > -1)
        {
            if(minor > v.minor)
            {
                //std::cout << "por minor" << std::endl;
                return true;
            }
            else if(minor < v.minor)
            {
                return false;
            }
        }
        else if(minor < 0 and v.minor > -1) //x simepre es major que x.y
        {
            return true;
        }
        
        
        if(patch > -1 and v.patch > -1)
        {
            if(patch >= v.patch)
            {
                //std::cout << "por patch" << std::endl;
                return true;
            }
            else if(patch < v.patch)
            {
                return false;
            }
        }
        else if(patch < 0 and v.patch > -1)
        {
            return true;
        }
        else if(patch > v.patch)
        {
            return true;
        }
        else//El menor se asigno pero el patch no.
        {
            return false;
        }
                
        //std::cout << "no cumple" << std::endl;
        return false;
    }*/
        /*const std::string& Version::getName() const
        {
                return name;
        }*/
        /*void Version::setName(const std::string& name)
        {
                this->name = name;
        }*/
    void v100::set(short major,short minor,short patch,Stage stage,unsigned long build, const std::string& name)
    {                
        this->major = major;
        this->minor = minor;
        this->patch = patch;
        this->stage = stage;
        this->build = build;
        //this->name = name;
    }
	const std::string& v100::getBuildString() const
	{
        return build.getString();
    }
	unsigned long v100::getBuildUL() const
	{
        return build.getUL();
    }
    Semver::Stage v100::getStage() const
    {
        return stage;
    }       
    short v100::getStageNumber() const
    {
        return stageNumber;
    }
    const v100::Build& Semver::getBuild() const
    {
        return build;
    }
        void v100::setNumbers(short major,short minor,short patch)
        {
                this->major = major;
                this->minor = minor;
                this->patch = patch;
        }
        void v100::setNumbers(short major,short minor)
        {
                this->major = major;
                this->minor = minor;
                patch = -1;
        }
        void v100::setNumbers(short major)
        {
                this->major = major;
                minor = -1;
                patch = -1;
        }
 	void v100::setStage(Stage stage)
	{
		this->stage = stage;
	}
 	void v100::setStage(Stage stage,short number)
	{
		this->stage = stage;
		this->stageNumber = number;
	}
    void v100::setBuild(unsigned long build)
    {
        this->build = build;
    }
	short v100::getMajor() const
	{
		return this->major;		
	}

	short v100::getMinor() const
	{
		return this->minor;
	}

	short v100::getPatch() const
	{
		return this->patch;
	}

	v100::v100(short major,short minor,short patch)
    {
		this->major = major;
		this->minor = minor;
		this->patch = patch;
		stage = unknown;
        build = (unsigned long)0;
        //name = "";
    }
	v100::v100(short major,short minor)
    {
		this->major = major;
		this->minor = minor;
		patch = -1;
		stage = unknown;
        build = (unsigned long)0;
        //name = "";
    }
	v100::v100()
	{
        init();
	}

	std::string v100::toString(Semver::Format formato) const
	{		
		std::string ver = "";
                if(major >= 0)
                {
                        ver += std::to_string(major);
                }
                if(minor >= 0)
                {
                        ver += ".";
                        ver += std::to_string(minor);
                }
                if(patch >= 0)
                {
                        ver += ".";
                        ver += std::to_string(patch);		
                }
                if(formato == Semver::Format::ONLY_NUMBERS) return ver;
                
		switch(stage)
		{
                        case developing:
                                ver += "-developing";
                                break;
                        case snapshot:
                                ver += "-snapshot";
                                break;
                        case alpha:
                                ver += "-alpha";
                                break;
                        case beta:
                                ver += "-beta";
                                break;
                        case betarelease:
                                ver += "-betarelease";
                                break;
                        case rc:
                                ver += "-rc";
                                break;
                        case prerelease:
                                ver += "-prerelease";
                                break;
                        case release:
                                ver += "-release";
                                break;
                        case ga:
                                ver += "-GA";
                                break;
                        case rtm:
                                ver += "-RTM";
                                break;
						default:
						
							break;							
		}

		if(build.getType() == Build::eBuild::ul_e)
        {
            if(build.getUL() > 0)
            {
                ver += "+";
                ver += std::to_string(build.getUL());	
            }
        }
        /*else if(build.getType() == Build::etype::version)
        {
            
            ver += " ";
            ver += build.getVersion()->toString(formato);
        }*/
        else if(build.getType() == Build::eBuild::string_e)
        {
            ver += build.getString();
        }
        /*if(name.size() > 0)
        {
            ver += " ";
            ver += name;
        }*/
                
		return ver;
	}
}
}
}
