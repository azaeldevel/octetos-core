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

#if defined(__linux__)
    #include <config.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include "config-win.h"
#else
    #error "Plataforma desconocida"
#endif
#include <typeinfo>
#include <string.h>

#include "Exception-v3.hh"
#include "Version-v3.hh"

namespace oct::core::v3
{
	Semver version(PACKAGE_VERSION);
	
    bool Semver::operator !=(const Version& obj)const
    {
        if (major != ((Semver&)obj).getMajor() or minor != ((Semver&)obj).getMinor() or patch != ((Semver&)obj).getPatch())
        {
            return true;
        }

        return false;
    }
    bool Semver::operator ==(const Version& obj)const
    {
        if (major == ((Semver&)obj).getMajor() && minor == ((Semver&)obj).getMinor() && patch == ((Semver&)obj).getPatch())
        {
            return true;
        }

        return false;
    }
    bool Semver::operator <(const Version& obj)const
    {

        if (major < 0 or ((Semver&)obj).getMajor() < 0)
        {
            throw Exception(Exception::Empty_Object,__FILE__,__LINE__);
        }
        else if (major > ((Semver&)obj).getMajor())
        {
            return false;
        }
        else if (major < ((Semver&)obj).getMajor())
        {
            return true;
        }

        if (minor < 0 and ((Semver&)obj).getMinor() < 0)
        {
            return false;
        }
        else if (minor < 0 and ((Semver&)obj).getMinor() > -1)
        {
            return false;
        }
        else if (minor > ((Semver&)obj).getMinor())
        {
            return false;
        }
        else if (minor < ((Semver&)obj).getMinor())
        {
            return true;
        }

        if (patch < 0 and ((Semver&)obj).getPatch() < 0)
        {
            return false;
        }
        else if (patch < 0 and ((Semver&)obj).getPatch() > -1)
        {
            return false;
        }
        else if (patch > ((Semver&)obj).getPatch())
        {
            return false;
        }
        else if (patch < ((Semver&)obj).getPatch())
        {
            return true;
        }

        return false;
    }
    bool Semver::operator >(const Version& obj)const
    {
        if (major < 0 or ((Semver&)obj).getMajor() < 0)
        {
            throw Exception(Exception::Empty_Object, __FILE__, __LINE__);
        }
        else if (major < ((Semver&)obj).getMajor())
        {
            return false;
        }
        else if (major > ((Semver&)obj).getMajor())
        {
            return true;
        }


        if (minor < 0 and ((Semver&)obj).getMinor() < 0)
        {
            return false;
        }
        else if (minor < 0 and ((Semver&)obj).getMinor() > -1)
        {
            return true;
        }
        else if (minor > ((Semver&)obj).getMinor())
        {
            return true;
        }
        else if (minor < ((Semver&)obj).getMinor())
        {
            return false;
        }

        if (patch < 0 and ((Semver&)obj).getPatch() < 0)
        {
            return true;
        }
        else if (patch < 0 and ((Semver&)obj).getPatch() > -1)
        {
            return true;
        }
        else if (patch > ((Semver&)obj).getPatch())
        {
            return true;
        }
        else if (patch < ((Semver&)obj).getPatch())
        {
            return false;
        }

        //std::cout << "no cumple" << std::endl;
        return false;
    }
    bool Semver::operator <=(const Version& obj)const
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
    bool Semver::operator >=(const Version& obj)const
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

    void Semver::setPrerelease(const char* str)
    {
        copy_prerelease(str);
    }
    void Semver::setBuild(const char* str)
    {
        copy_build(str);
    }


    const char* Semver::getPrerelease() const
    {
        return prerelease;
    }
    const char* Semver::getBuild() const
    {
        return build;
    }



    const Semver& Semver::operator =(const Semver& v)
    {
        if (strcmp(typeid(*this).name(), typeid(&v).name()) == 0)
        {
            std::string msgErr = "Asignacion no equivalente, el obejto destino es '";
            msgErr += typeid(*this).name();
            msgErr += "', minetras que el origne es '";
            msgErr += typeid(&v).name();
            msgErr += "'";
            throw Exception(Exception::Invalid_Compared_Version_Objects, __FILE__, __LINE__);
        }

        this->major = v.major;
        this->minor = v.minor;
        this->patch = v.patch;
        copy_prerelease(v.prerelease);
        copy_build(v.build);

        return *this;
    }

    void Semver::set(Number major, Number minor, Number patch, const std::string& prerelease)
    {
        this->major = major;
        this->minor = minor;
        this->patch = patch;
        copy_prerelease(prerelease.c_str());
    }
    void Semver::setNumbers(Number major, Number minor, Number patch)
    {
        this->major = major;
        this->minor = minor;
        this->patch = patch;
    }
    void Semver::setNumbers(Number major, Number minor)
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
    Semver::Number Semver::getMajor() const
    {
        return major;
    }

    Semver::Number Semver::getMinor() const
    {
        return minor;
    }

    Semver::Number Semver::getPatch() const
    {
        return patch;
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
        if (prerelease) delete prerelease;
        if (build) delete build;
    }
    void Semver::init()
    {
        major = -1;
        minor = -1;
        patch = -1;
        prerelease = NULL;
        build = NULL;
    }
    Semver::Semver()
    {
        init();
    }
    Semver::Semver(const char* str)
    {
        parse(str);
    }
    Semver::Semver(Number major, Number minor, Number patch)
    {
        this->major = major;
        this->minor = minor;
        this->patch = patch;
        this->prerelease = NULL;
        this->build = NULL;
    }
    Semver::Semver(Number major, Number minor)
    {
        this->major = major;
        this->minor = minor;
        this->patch = -1;
        this->prerelease = NULL;
        this->build = NULL;
    }
    Semver::Semver(const Semver& obj)
    {
        major = obj.major;
        minor = obj.minor;
        patch = obj.patch;
        copy_prerelease(obj.prerelease);
        copy_build(obj.build);
    }


    bool Semver::empty() const
    {
        return (major < 0 and minor < 0 and patch < 0)? true : false;
    }

    Version& Semver::operator =(const char* str)
    {
        parse(str);

        return (Version&) * this;
    }
    Version& Semver::operator =(const std::string& str)
    {
        parse(str.c_str());

        return (Version&)*this;
    }

    void Semver::copy_prerelease(const char* prer)
    {
        if (prerelease) delete prerelease;
        std::size_t leng = strlen(prer) + 1;
        prerelease = new char[leng];
        strcpy(prerelease,prer);
    }

    void Semver::copy_build(const char* strb)
    {
        if (build) delete build;
        std::size_t leng = strlen(strb) + 1;
        prerelease = new char[leng];
        strcpy(prerelease, strb);
    }
}
