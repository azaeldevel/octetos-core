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
#elif defined(_WIN32) || defined(_WIN64)
    #include "config-win.h"
#else
    #error "Plataforma desconocida"
#endif

#include "semver-lexer.h"
#include "Version-v2.hh"

namespace oct::core::v2
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
            throw InvalidComparison("Operaci�n invalidad, est� comprando objetos Version sin antes asignarles valores.");
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
            throw InvalidComparison("Operaci�n invalidad, est� comprando objetos Version sin antes asignarles valores.");
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

    void Semver::setPrerelease(const std::string& str)
    {
        octetos_core_Semver_setPrerelease(this, str.c_str());
    }
    std::string Semver::getPrerelease() const
    {
        if (prerelease)
        {
            return prerelease;
        }

        return "";
    }
    const char* Semver::getBuild() const
    {
        return build;
    }
    bool Semver::set(unsigned long ver, ImportCode import)
    {
        if (import == ImportCode::MySQL)
        {
            unsigned long actualVer = ver;
            major = actualVer / 10000;
            actualVer -= (10000 * major);
            minor = actualVer / 100;
            actualVer -= (100 * minor);
            patch = actualVer;

            return true;
        }
        else if (import == ImportCode::PostgreSQL)
        {
            unsigned long actualVer = ver;
            major = actualVer / 10000;
            actualVer -= (10000 * major);
            minor = actualVer / 100;
            actualVer -= (100 * minor);
            patch = actualVer;

            return true;
        }

        return false;
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
        if (strcmp(typeid(*this).name(), typeid(&v).name()) == 0)
        {
            std::string msgErr = "Asignacion no equivalente, el obejto destino es '";
            msgErr += typeid(*this).name();
            msgErr += "', minetras que el origne es '";
            msgErr += typeid(&v).name();
            msgErr += "'";
            throw Exception(msgErr, __FILE__, __LINE__);
        }

        //if(!handle) dlclose(handle);
        //parser = NULL;
        //handle = NULL;
        //loadParser (suffix);
        this->major = v.major;
        this->minor = v.minor;
        this->patch = v.patch;
        if (v.prerelease) octetos_core_Semver_setPrerelease(this, v.prerelease);
        if (v.build) octetos_core_Semver_setBuild(this, v.build);

        return *this;
    }
    const octetos_core_Semver& Semver::operator =(const octetos_core_Semver& v)
    {
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
        octetos_core_Semver_setPrerelease(this, prerelease.c_str());
        build = NULL;
    }
    void Semver::setNumbers(Number major, Number minor, Number patch)
    {
        this->major = major;
        this->minor = minor;
        this->patch = patch;
        prerelease = NULL;
        build = NULL;
    }
    void Semver::setNumbers(Number major, Number minor)
    {
        this->major = major;
        this->minor = minor;
        patch = -1;
        prerelease = NULL;
        build = NULL;
    }
    void Semver::setNumbers(Number major)
    {
        this->major = major;
        minor = -1;
        patch = -1;
        prerelease = NULL;
        build = NULL;
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
        const char* verbuf = octetos_core_Semver_toString(this, formato);
        std::string ver = verbuf;
        free((void*)verbuf);
        return ver;
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
        //if(!handle) dlclose(handle);
        if (prerelease) free((void*)prerelease);
        if (build) free((void*)build);
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
        //if(!handle) dlclose(handle);
        //strcpy((char*)suffix,obj.suffix);
        //loadParser (suffix);

        major = obj.major;
        minor = obj.minor;
        patch = obj.patch;
        if (prerelease) octetos_core_Semver_setPrerelease(this, obj.prerelease);
        if (build) octetos_core_Semver_setBuild(this, obj.build);
    }


//#if _MSC_VER
    bool Semver::extractNumbers(const std::string& str)
    {
        return parse(str.c_str());
    }
    bool Semver::set(const std::string& str)
    {
        return parse(str.c_str());
    }
/*#elif __GNUG__
    bool Semver::extractNumbers(const std::string& str)
    {
        octetos_core_Tray ty;
        ty.dysplay_erro = 0;
        ty.version = this;
        ty.buffer = NULL;
        ty.state = 0;
        std::string cmdstr = "extract numbers from ";
        cmdstr += str;
        ty.str = (char*)cmdstr.c_str();
        int ret = parse_string(&ty);
        if (ty.buffer) delete ty.buffer;

        if (ret == 0) return true;
        return false;
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
        ty.str = (char*)cmdstr.c_str();
        int ret = parse_string(&ty);
        if (ty.buffer) delete ty.buffer;

        if (ret == 0) return true;
        return false;
    }
#endif*/


    bool Semver::empty() const
    {
        if (major < 0 and minor < 0 and patch < 0) return true;
        return false;
    }

	InvalidComparison::InvalidComparison(const std::string& msg):Error(msg,Error::ERROR_VERSION_INVALID_COMPARISON)
	{
	}
	InvalidComparison::InvalidComparison(const std::string& msg ,std::string filename,int lineNumber):Error(msg,Error::ERROR_VERSION_INVALID_COMPARISON,filename,lineNumber)
	{
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
