
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
	std::string v100::getPrerelease() const
	{
		return prerelease;
	}
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
		else if(import == ImportCode::PostgreSQL)
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
		
	bool v100::set(const std::string& str)
	{
        octetos_Tray ty;
		ty.dysplay_erro = 0;
		ty.version = this;
        int ret = parse_string(&ty,str.c_str());
		
        if(ret == 0) return true;
        return false;
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
		prerelease = NULL;
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
    }

	
	const v100& v100::operator =(const v100& v)
	{
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		this->prerelease = v.prerelease;
                
		return *this;
	}
	const octetos_Semver& v100::operator =(const octetos_Semver& v)
	{
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		this->prerelease = v.prerelease;
                
		return *this;
	}    
    void v100::set(short major,short minor,short patch, const std::string& prerelease)
    {                
        this->major = major;
        this->minor = minor;
        this->patch = patch;
		octetos_Semver_setPrerelease(this,prerelease.c_str());
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
    }

	std::string v100::toString(FormatString formato) const
	{		
		std::string ver = "";
        ver = octetos_Semver_toString(this,formato);
		return ver;
	}
}
}
}
