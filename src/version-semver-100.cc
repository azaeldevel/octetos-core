
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
		ty.version = this;
		std::string strcmd = "extract numbers from ";
		strcmd += str;
		//printf("command : %s\n",strcmd.c_str());
        int ret = parse_string(&ty,strcmd.c_str());
		
        if(ret == 0) return true;
        return false;
	}
		
	bool v100::set(const std::string& str)
	{
        Tray ty;
		ty.dysplay_erro = 0;
		ty.version = this;
        int ret = parse_string(&ty,str.c_str());
		
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
	
    /*const char* v100::Build::getString()const
    {
        if(type == eBuild::string_e)
        {
            return value.string;
        }
        else
        {
            throw Error("El tipo de este dato no es 'una cadena de texto.'",0);
        }
    }*/
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
    /*unsigned long v100::Build::getUL() const
    {
        if(type == eBuild::ul_e)
        {
                return value.ul;
        }
        else
        {
            throw Error("El tipo de este dato no es 'unsigned long'",0);
        }
    }*/
    /*v100::Build::eBuild v100::Build::getType()const
    {
        return type;
    }*/    
    /*Version::Build& Version::Build::operator =(Version* build)
    {
        val.version = build;
        type = etype::version;
        
        return *this;
    }*/
    /*v100::Build& v100::Build::operator =(unsigned long ul)
    {
        type = eBuild::ul_e;
        value.ul = ul;
        
        return *this;
    }*/
    /*v100::Build& v100::Build::operator =(const char* str)
    {
        
        strcpy(value.string,str);
        type = eBuild::string_e;        
        return *this;
    }*/
    
    /*v100::Build::~Build()
    {
        if(type == Build::eBuild::string_e)
        {
            delete this->value.string;
        }
    }*/
    
    
    
    
    

    void v100::init()
    {
		Semver_init(this);
    }
	v100::v100(short major,short minor)
    {
		this->major = major;
		this->minor = minor;
		patch = -1;
		stage = unknown;
        build.type = octetos_version_eBuild::none;
        build.value.ul = 0;
    }
	v100::v100()
	{
        init();
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
		if(build.type == eBuild::string_e)
		{
			if(!build.value.string) delete build.value.string;
		}
    }

	
    void v100::setBuild(unsigned long b)
    {
		if(build.type == eBuild::none)
		{
			build.type = eBuild::ul_e;
        	this->build.value.ul = b;
		}
		else if(build.type == eBuild::ul_e)
		{
			
        	this->build.value.ul = b;
		}
		else
		{
			throw Error("Esta asignado un valor entero a un campo no entero.");
		}
    }
    void v100::setBuild(const std::string& str)
    {
		if(build.type == eBuild::none or build.type == eBuild::string_e)
		{
			build.type = eBuild::string_e;
			const char* temp = str.c_str();
			if(build.value.string)
			{//si hay una string librar la memoria
				delete build.value.string;
			}
			build.value.string = new char(str.size() + 1);
		    strcpy(build.value.string, temp);
		}
		else
		{
			throw Error("Esta asignado un valor entero a un campo no entero.");
		}
    }
    /*void Version::setBuild(const Version* v)
    {
        Version* ver = new Version(v);
        this->build = ver;        
    }  */  
	const v100& v100::operator =(const v100& v)
	{
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		this->build = v.build;
		this->stage = v.stage;
		this->stageNumber = v.stageNumber;
                
		return *this;
	}
	const octetos_Semver& v100::operator =(const octetos_Semver& v)
	{
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		this->build = v.build;
		this->stage = v.stage;
		this->stageNumber = v.stageNumber;
                
		return *this;
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
        this->build.type = eBuild::none;
		this->build.value.ul = 0;
    }
	std::string v100::getBuildString() const
	{
        if(build.type == eBuild::string_e) return std::string(build.value.string);
		throw Error("El campo build no contine informacion de tipo string.",Error::ERROR_UNKNOW);
    }
	unsigned long v100::getBuildUL() const
	{
        if(build.type == octetos_version_eBuild::ul_e) return build.value.ul;
		throw Error("El campo build no contine informacion de tipo long.",Error::ERROR_UNKNOW);
    }
    Stage v100::getStage() const
    {
        return stage;
    }       
    short v100::getStageNumber() const
    {
        return stageNumber;
    }
    /*const v100::Build& Semver::getBuild() const
    {
        return build;
    }*/
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
        build.type = octetos_version_eBuild::none;
        //name = "";
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

		if(build.type == octetos_version_eBuild::ul_e)
        {
            if(build.value.ul > 0)
            {
                ver += "+";
                ver += std::to_string(build.value.ul);	
            }
        }
        else if(build.type == octetos_version_eBuild::string_e)
        {
            ver += build.value.string;
        }
                
		return ver;
	}
}
}
}
