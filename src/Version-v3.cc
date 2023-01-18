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

#include <typeinfo>
#include <string.h>

#if defined(__linux__)
    #include <config.h>
	#include "Exception-v3.hh"
#elif defined(_WIN32) || defined(_WIN64)
    #include "config-win.h"
#else
    #error "Plataforma desconocida"
#endif


#include "Version-v3.hh"

namespace oct::core::v3
{

	Semver version(PACKAGE_VERSION);


	
	Semver::Exception::Exception()
	{
	}
	Semver::Exception::Exception(const Exception& e) : v3::Exception(e)
	{
	}

	Semver::Exception::Exception(const char* s) : v3::Exception(s)
	{
	}
	Semver::Exception::Exception(const char* m,const char* fn, unsigned int l) : v3::Exception(m,fn,l)
	{
	}


	Semver::Exception::~Exception()
	{
	}
	
	/*const char* Semver::Exception::what() const throw ()
	{	
		return _message;
	}*/



    bool Semver::operator !=(const Semver& obj)const
    {
        if (major != obj.major or minor != obj.minor or patch != obj.patch)
        {
            return true;
        }

        return false;
    }
    bool Semver::operator ==(const Semver& obj)const
    {
        if (major == obj.major && minor == obj.minor && patch == obj.patch)
        {
            return true;
        }

        return false;
    }
    bool Semver::operator <(const Semver& obj)const
    {

        if (major < 0 or obj.major < 0)
        {
            throw Exception("Al menos uno de los operandos no estan inicializados",__FILE__,__LINE__);
        }
        else if (major > obj.major)
        {
            return false;
        }
        else if (major < obj.major)
        {
            return true;
        }

        if (minor < 0 and obj.minor < 0)
        {
            return false;
        }
        else if (minor < 0 and obj.minor > -1)
        {
            return false;
        }
        else if (minor > obj.minor)
        {
            return false;
        }
        else if (minor < obj.minor)
        {
            return true;
        }

        if (patch < 0 and obj.patch < 0)
        {
            return false;
        }
        else if (patch < 0 and obj.patch > -1)
        {
            return false;
        }
        else if (patch > obj.patch)
        {
            return false;
        }
        else if (patch < obj.patch)
        {
            return true;
        }

        return false;
    }
    bool Semver::operator >(const Semver& obj)const
    {
        if (major < 0 or obj.major < 0)
        {
            throw Exception("Al menos uno de los operandos no estan inicializados",__FILE__,__LINE__);
        }
        else if (major < obj.major)
        {
            return false;
        }
        else if (major > obj.major)
        {
            return true;
        }


        if (minor < 0 and obj.minor < 0)
        {
            return false;
        }
        else if (minor < 0 and obj.minor > -1)
        {
            return true;
        }
        else if (minor > obj.minor)
        {
            return true;
        }
        else if (minor < obj.minor)
        {
            return false;
        }

        if (patch < 0 and obj.patch < 0)
        {
            return true;
        }
        else if (patch < 0 and obj.patch > -1)
        {
            return true;
        }
        else if (patch > obj.patch)
        {
            return true;
        }
        else if (patch < obj.patch)
        {
            return false;
        }

        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool Semver::operator <=(const Semver& obj)const
    {
        if (((Semver&)*this) == ((Semver&)obj) or (*this) < ((Semver&)obj))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Semver::operator >=(const Semver& obj)const
    {
        if (((Semver&)*this) == ((Semver&)obj) or (*this) > ((Semver&)obj))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Semver::setPrerelease(const std::string& str)
    {
		if(str.empty()) return;
        copy_prerelease(str.c_str());
    }
    const char* Semver::get_stage() const
    {
        if (prerelease)
        {
            return prerelease;
        }

        return "#";
    }
    const char* Semver::get_build() const
    {
        if (build)
        {
            return build;
        }

        return "#";
    }


    void Semver::init()
    {
        major = -1;
        minor = -1;
        patch = -1;
        prerelease = NULL;
        build = NULL;
    }
    const Semver& Semver::operator =(const Semver& v)
    {
		free_prerelease();
		free_build();
		init();
        major = v.major;
        minor = v.minor;
        patch = v.patch;
        if(v.prerelease)copy_prerelease(v.prerelease);
        if(v.build)copy_build(v.build);
		
        return *this;
    }
    void Semver::set(Number major, Number minor, Number patch, const std::string& prestr)
    {
        this->major = major;
        this->minor = minor;
        this->patch = patch;
        if(not prestr.empty()) copy_prerelease(prestr.c_str());
		free_build();
    }
    void Semver::setNumbers(Number major, Number minor, Number patch)
    {
        this->major = major;
        this->minor = minor;
        this->patch = patch;
		free_prerelease();
		free_build();
    }
    void Semver::setNumbers(Number major, Number minor)
    {
        this->major = major;
        this->minor = minor;
        patch = -1;
		free_prerelease();
		free_build();
    }
    void Semver::setNumbers(Number major)
    {
        this->major = major;
        minor = -1;
        patch = -1;
		free_prerelease();
		free_build();
    }
    Number Semver::get_major() const
    {
        return this->major;
    }

    Number Semver::get_minor() const
    {
        return this->minor;
    }

    Number Semver::get_patch() const
    {
        return this->patch;
    }

    Semver::operator std::string()const
    {
        std::string ver;
        if (major > -1)
        {
            ver += std::to_string(major);
            if (minor > -1)
            {
                ver += ".";
                ver += std::to_string(minor);
                if (patch > -1)
                {
                    ver += ".";
                    ver += std::to_string(patch);
                }
            }

            //
            if(prerelease)
            {
                ver += "-";
                ver += prerelease;
            }
            if (build)
            {
                ver += "+";
                ver += build;
            }
        }

        return ver;
    }

    Semver::~Semver()
    {
        free_prerelease();
        free_build();
    }
    Semver::Semver()
    {
        init();
    }
    Semver::Semver(const char* str)
    {
        init();
        parse(str);
    }
    Semver::Semver(Number major, Number minor, Number patch)
    {
        init();
        this->major = major;
        this->minor = minor;
        this->patch = patch;
    }
    Semver::Semver(Number major, Number minor)
    {
        init();
        this->major = major;
        this->minor = minor;
    }
    Semver::Semver(const Semver& obj)
    {
		init();
        major = obj.major;
        minor = obj.minor;
        patch = obj.patch;
        if(obj.prerelease) copy_prerelease(obj.prerelease);
        if(obj.build)copy_build(obj.build);
    }

    bool Semver::set(const std::string& str)
    {
        return parse(str.c_str());
    }



    bool Semver::empty() const
    {
        if (major < 0 or minor < 0 and patch < 0) return true;
        return false;
    }

	
    void Semver::copy_prerelease(const char* prer)
    {
        if (prerelease) delete[] prerelease;
        std::size_t leng = strlen(prer) + 1;
        prerelease = new char[leng];
        strcpy(prerelease,prer);
    }
	void Semver::free_prerelease()
	{
		if (prerelease) delete[] prerelease;
		prerelease = NULL;
	}
    void Semver::copy_build(const char* strb)
    {
        if (build) delete[] build;
        std::size_t leng = strlen(strb) + 1;
        build = new char[leng];
        strcpy(build, strb);
    }
	void Semver::free_build()
	{
		if (build) delete[] build;
		build = NULL;
	}
}
