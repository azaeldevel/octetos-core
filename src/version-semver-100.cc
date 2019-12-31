
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
	
	bool v100::set(unsigned long ver,ImportCode import)
	{
		if(import == ImportCode::MySQL)
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
	const char* v100::getStageString() const
	{
		return octetos_Stage_getString(stage);
	}    
    void v100::init()
    {
		octetos_Semver_init(this);
    }
	v100::v100(short major,short minor)
    {
		this->major = major;
		this->minor = minor;
		patch = -1;
		stage = unknown;
        build.type = octetos_Semver_Build_Type::none;
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
		if(build.type == octetos_Semver_Build_Type::string_e)
		{
			if(!build.value.string) delete build.value.string;
		}
    }

	
    void v100::setBuild(unsigned long b)
    {
		if(build.type == octetos_Semver_Build_Type::none)
		{
			build.type = octetos_Semver_Build_Type::ul_e;
        	this->build.value.ul = b;
		}
		else if(build.type == octetos_Semver_Build_Type::ul_e)
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
		if(build.type == octetos_Semver_Build_Type::none or build.type == octetos_Semver_Build_Type::string_e)
		{
			build.type = octetos_Semver_Build_Type::string_e;
			const char* temp = str.c_str();
			if(build.value.string)
			{//si hay una string librar la memoria
				free(build.value.string);
			}
			build.value.string = (char*)malloc(str.size() + 1);
		    strcpy(build.value.string, temp);
		}
		else
		{
			throw Error("Esta asignado un valor entero a un campo no entero.");
		}
    }  
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
    void v100::set(short major,short minor,short patch,Stage stage,unsigned long build, const std::string& name)
    {                
        this->major = major;
        this->minor = minor;
        this->patch = patch;
        this->stage = stage;
        this->build.type = octetos_Semver_Build_Type::none;
		this->build.value.ul = 0;
    }
	std::string v100::getBuildString() const
	{
        if(build.type == octetos_Semver_Build_Type::string_e) return std::string(build.value.string);
		throw Error("El campo build no contine informacion de tipo string.",Error::ERROR_UNKNOW);
    }
	unsigned long v100::getBuildUL() const
	{
        if(build.type == octetos_Semver_Build_Type::ul_e) return build.value.ul;
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
        build.type = octetos_Semver_Build_Type::none;
    }

	std::string v100::toString(FormatString formato) const
	{		
		std::string ver = "";
		/*
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

		if(build.type == octetos_Semver_Build_Type::ul_e)
        {
            if(build.value.ul > 0)
            {
                ver += "+";
                ver += std::to_string(build.value.ul);	
            }
        }
        else if(build.type == octetos_Semver_Build_Type::string_e)
        {
            ver += build.value.string;
        }*/
        ver = octetos_Semver_toString(this,formato);
		return ver;
	}
}
}
}
