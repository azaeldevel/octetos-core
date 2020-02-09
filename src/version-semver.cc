
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef OCTETOS_CORE_SANDBOX
#include <iostream> //for test
#endif
#include <dlfcn.h>
#include <dirent.h>

#include "Version.hh"
#include "Error.hh"

namespace octetos
{
namespace core
{
namespace semver
{
	Stage Semver::getPrereleaseStage() const
	{
				
	}
	bool Semver::extractNumbers(const std::string& str)
	{
        octetos_core_Tray ty;
		ty.dysplay_erro = 0;
		ty.version = this;
		std::string cmdstr = "extract numbers from ";
		cmdstr += str;
        int ret = parser(&ty,cmdstr.c_str());
		
        if(!ret) return true;
        return false;
	}
	bool Semver::loadParser(const char* sufix)
	{
		std::string filename;
#ifdef OCTETOS_CORE_SANDBOX
		filename = "Debug/src/.libs/liboctetos-semver-";		
#else
		filename = "liboctetos-semver-";
#endif
		filename = filename + sufix + ".so";	
#ifdef OCTETOS_CORE_SANDBOX
		//std::cout << "filename:" << filename << "\n";
#endif
		handle = dlopen(filename.c_str(), RTLD_LAZY);
		if(!handle)
		{
			std::string msgErr ="dlopen fallo con '" ;
			msgErr += filename + "' : ";
          	msgErr = msgErr + dlerror();
			core::Error err(msgErr,core::Error::ERROR_UNKNOW,__FILE__,__LINE__);            
			core::Error::write(err);
			return false;
		}
		parser = (int (*)(struct octetos_core_Tray*,const char*))dlsym(handle, "parse_string");
		if(!parser)
		{                    
			std::string msgErr ="dlsym fallo con parse_string:\n" ;
			msgErr = msgErr + "\t" + dlerror();
			core::Error err(msgErr,core::Error::ERROR_UNKNOW,__FILE__,__LINE__);            
			core::Error::write(err);
			return false;
		}

		return true;
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
		std::string cmdstr = "extract all from ";
		cmdstr += str;
		if(!parser) 
		{
			std::string msgErr ="No se encontro una fucion parser:\n" ;
			core::Error err(msgErr,core::Error::ERROR_UNKNOW,__FILE__,__LINE__);            
			core::Error::write(err);
			return false;
		}
        int ret = parser(&ty,cmdstr.c_str());
		
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
		parser = NULL;
		handle = NULL;
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
		
		if(!handle) dlclose(handle);
		parser = NULL;
		handle = NULL;
		loadParser (suffix);	
		this->major = v.major;
		this->minor = v.minor;
		this->patch = v.patch;
		if(v.prerelease) octetos_core_Semver_setPrerelease(this,v.prerelease);
		if(v.build) octetos_core_Semver_setBuild(this,v.build);		
		
		return *this;
	}
	const octetos_core_Semver& Semver::operator =(const octetos_core_Semver& v)
	{
		if(!handle) dlclose(handle);
		parser = NULL;
		handle = NULL;
		loadParser (suffix);
		
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
		if(!handle) dlclose(handle); 
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
		if(!handle) dlclose(handle);
		strcpy((char*)suffix,obj.suffix);
		loadParser (suffix);
		
		major = obj.major;
		minor = obj.minor;
		patch = obj.patch;
		if(prerelease) octetos_core_Semver_setPrerelease(this,obj.prerelease);
		if(build) octetos_core_Semver_setBuild(this,obj.build);
	}
}
}
}
