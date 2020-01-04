
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
	void Semver::setPrerelease(const std::string& str)
	{
		octetos_Semver_setPrerelease(this,str.c_str());
	}
	std::string Semver::getPrerelease() const
	{
		return prerelease;
	}
	
	
	bool Semver::set(unsigned long ver,ImportCode import)
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
		
	bool Semver::set(const std::string& str)
	{
        octetos_Tray ty;
		ty.dysplay_erro = 0;
		ty.version = this;
        int ret = parse_string(&ty,str.c_str());
		
        if(ret == 0) return true;
        return false;
	}
    void Semver::init()
    {
		octetos_Semver_init(this);
    }
	

	
	const Semver& Semver::operator =(const Semver& v)
	{
        octetos_Semver& v1 = *this;
		v1 = v;
		return *this;
	}
	const octetos_Semver& Semver::operator =(const octetos_Semver& v)
	{
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		this->prerelease = v.prerelease;
                
		return *this;
	}
    void Semver::set(Number major,Number minor,Number patch, const std::string& prerelease)
    {                
        this->major = major;
        this->minor = minor;
        this->patch = patch;
		octetos_Semver_setPrerelease(this,prerelease.c_str());
    }
        void Semver::setNumbers(Number major,Number minor,Number patch)
        {
                this->major = major;
                this->minor = minor;
                this->patch = patch;
        }
        void Semver::setNumbers(Number major,Number minor)
        {
                this->major = major;
                this->minor = minor;
                patch = -1;
        }
        void Semver::setNumbers(Number major)
        {
                this->major = major;
                minor = -1;
                patch = -1;
        }
	Number Semver::getMajor() const
	{
		return this->major;		
	}

	Number Semver::getMinor() const
	{
		return this->minor;
	}

	Number Semver::getPatch() const
	{
		return this->patch;
	}

	std::string Semver::toString(FormatString formato) const
	{		
		std::string ver = "";
        ver = octetos_Semver_toString(this,formato);
		return ver;
	}


	Semver::~Semver()
	{
	}
	Semver::Semver()
	{
		init();
	}
	Semver::Semver(Number major,Number minor,Number patch)
    {
		init();
		this->major = major;
		this->minor = minor;
		this->patch = patch;
    }
	Semver::Semver(Number major,Number minor)
    {
		init();
		this->major = major;
		this->minor = minor;
    }
}
}
}
