/**
 * 
 *  This file is part of octetos-core.
 *  octetos-core is a core C/C++ Octeto's library.
 *  Copyright (C) 2018  Azael Reyes
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>

#include "Version.hh"
#include "Error.hh"

namespace octetos
{
namespace core
{
    bool Semver::operator !=(const Version& obj)const
    {
        if(major != ((Semver&)obj).getMajor() or minor != ((Semver&)obj).getMinor() or patch != ((Semver&)obj).getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool Semver::operator ==(const Version& obj)const
    {
        if(major == ((Semver&)obj).getMajor() && minor == ((Semver&)obj).getMinor() && patch == ((Semver&)obj).getPatch())
        {
            return true;
        }
        
        return false;
    }
    bool Semver::operator <(const Version& obj)const
    {                  
		
		if(major < 0 or ((Semver&)obj).getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major > ((Semver&)obj).getMajor())
        {
            return false;  
        }
		else if(major < ((Semver&)obj).getMajor())
        {
            return true;  
        }

        if(minor < 0 and ((Semver&)obj).getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and ((Semver&)obj).getMinor() > -1)
        {
            return false;
        }
        else if(minor > ((Semver&)obj).getMinor())
        {
            return false;
        } 
		else if(minor < ((Semver&)obj).getMinor())
        {
            return true;
        } 
        
        if(patch < 0 and ((Semver&)obj).getPatch() < 0)
        {
            return false;
        }
        else if(patch < 0 and ((Semver&)obj).getPatch() > -1)
        {
            return false;
        }
        else if(patch > ((Semver&)obj).getPatch())
        {
            return false;
        }
        else if(patch < ((Semver&)obj).getPatch())
        {
            return true;
        }
                
        return false;
    }
	bool Semver::operator >(const Version& obj)const
    {
        if(major < 0 or ((Semver&)obj).getMajor() < 0)
		{
			throw InvalidComparison("Operación invalidad, está comprando objetos Version sin antes asignarles valores.");
		}
        else if(major < ((Semver&)obj).getMajor())
        {
            return false;
        }
        else if(major > ((Semver&)obj).getMajor())
        {
            return true;
        }
		
        
        if(minor < 0 and ((Semver&)obj).getMinor() < 0)
        {
            return false;
        }
        else if(minor < 0 and ((Semver&)obj).getMinor() > -1)
        {
            return true;
        }
        else if(minor > ((Semver&)obj).getMinor())
        {
            return true;
        }
        else if(minor < ((Semver&)obj).getMinor())
        {
            return false;
        }
        
        if(patch < 0 and ((Semver&)obj).getPatch() < 0)
        {
            return true;
        }
        else if(patch < 0 and ((Semver&)obj).getPatch() > -1)
        {
            return true;
        }
        else if(patch > ((Semver&)obj).getPatch())
        {
            return true;
        }
        else if(patch < ((Semver&)obj).getPatch())
        {
            return false;
        }
                
        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool Semver::operator <=(const Version& obj)const
    {
        if((*this) == ((Semver&)obj) or (*this) < ((Semver&)obj))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Semver::operator >=(const Version& obj)const
    {
        if((*this) == ((Semver&)obj) or (*this) > ((Semver&)obj))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
	
	bool Semver::extractNumbers(const std::string& str)
	{
        octetos_core_Tray ty;
		ty.dysplay_erro = 0;
		ty.version = this;
		ty.buffer = NULL;
		ty.state = 0;
		std::string cmdstr = "extract numbers from ";
		cmdstr += str;
		/*if(!parser) 
		{
			std::string msgErr ="No se encontro una fucion parser:\n" ;
			core::Error err(msgErr,core::Error::ERROR_UNKNOW,__FILE__,__LINE__);            
			core::Error::write(err);
			return false;
		}*/
		ty.str = cmdstr.c_str();
        int ret = parse_string(&ty);
		
        if(!ret) return true;
        return false;
	}
	void Semver::setPrerelease(const std::string& str)
	{
		octetos_core_Semver_setPrerelease(this,str.c_str());
	}
	std::string Semver::getPrerelease() const
	{
		if(prerelease)
		{
			return prerelease;
		}
	}
	
	
	bool Semver::set(const std::string& str)
	{
        octetos_core_Tray ty;
		ty.dysplay_erro = 0;
		ty.version = this;
		ty.buffer = NULL;
		ty.state = 0;
		std::string cmdstr = "extract all from ";
		cmdstr += str;
		/*if(!parser) 
		{
			std::string msgErr ="No se encontro una fucion parser:\n" ;
			core::Error err(msgErr,core::Error::ERROR_UNKNOW,__FILE__,__LINE__);            
			core::Error::write(err);
			return false;
		}*/
		ty.str = cmdstr.c_str();
        int ret = parse_string(&ty);
		
        if(ret == 0) return true;
        return false;
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
		
	
    void Semver::init()
    {
		octetos_core_Semver_init(this);
		//parser = NULL;
		//handle = NULL;
    }
	const Semver& Semver::operator =(const Semver& v)
	{
		if(strcmp(typeid(*this).name(),typeid(&v).name()) == 0 )
		{
      		std::string msgErr ="Asignacion no equivalente, el obejto destino es '";
            msgErr += typeid(*this).name();
			msgErr += "', minetras que el origne es '";
			msgErr += typeid(&v).name();
			msgErr += "'";
            core::Error err(msgErr,core::Error::ERROR_UNKNOW,__FILE__,__LINE__);            
           	core::Error::write(err);
			return *this;
		}
		
		//if(!handle) dlclose(handle);
		//parser = NULL;
		//handle = NULL;
		//loadParser (suffix);	
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		if(v.prerelease) octetos_core_Semver_setPrerelease(this,v.prerelease);
		if(v.build) octetos_core_Semver_setBuild(this,v.build);		
		
		return *this;
	}
	const octetos_core_Semver& Semver::operator =(const octetos_core_Semver& v)
	{
		//if(!handle) dlclose(handle);
		//parser = NULL;
		//handle = NULL;
		//loadParser (suffix);
		
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		if(v.prerelease) octetos_core_Semver_setPrerelease(this,v.prerelease);
		if(v.build) octetos_core_Semver_setBuild(this,v.build);
		
		return *this;
	}
    void Semver::set(Number major,Number minor,Number patch, const std::string& prerelease)
    {                
        this->major = major;
        this->minor = minor;
        this->patch = patch;
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
		const char* verbuf = octetos_core_Semver_toString(this,formato);
		std::string ver = verbuf;
		free((void*)verbuf);
		return ver;
	}
	Semver::operator std::string()
	{
		const char* verbuf = octetos_core_Semver_toString(this,FormatString::FullString);
		std::string ver = verbuf;
		free((void*)verbuf);
		return ver;
	}

	Semver::~Semver()
	{
		//if(!handle) dlclose(handle); 
		if(prerelease) free((void*)prerelease);
		if(build) free((void*)build);
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
	Semver::Semver(const Semver& obj)
	{
		init();
		//if(!handle) dlclose(handle);
		//strcpy((char*)suffix,obj.suffix);
		//loadParser (suffix);
		
		major = obj.major;
		minor = obj.minor;
		patch = obj.patch;
		if(prerelease) octetos_core_Semver_setPrerelease(this,obj.prerelease);
		if(build) octetos_core_Semver_setBuild(this,obj.build);
	}
}
}
