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
        octetos_core_Semver_setPrerelease(this, str);
    }
    void Semver::setBuild(const char* str)
    {
        octetos_core_Semver_setBuild(this, str);
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
        if (v.prerelease) octetos_core_Semver_setPrerelease(this, v.prerelease);
        if (v.build) octetos_core_Semver_setBuild(this, v.build);

        return *this;
    }

    void Semver::set(Number major, Number minor, Number patch, const std::string& prerelease)
    {
        this->major = major;
        this->minor = minor;
        this->patch = patch;
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


    Semver::operator std::string()const
    {
        const char* verbuf = octetos_core_Semver_toString(this, FormatString::FullString);
        std::string ver = verbuf;
        free((void*)verbuf);
        return ver;
    }

    Semver::~Semver()
    {
        if (prerelease) free((void*)prerelease);
        if (build) free((void*)build);
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
        if (prerelease) octetos_core_Semver_setPrerelease(this, obj.prerelease);
        if (build) octetos_core_Semver_setBuild(this, obj.build);
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
}
