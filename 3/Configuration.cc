
/*
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 *
 * CC is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CC is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

 #include <fstream>
 #include <iostream>

#include "Exception.hh"
#include "Configuration.hh"

namespace oct::core::v3
{



	Configuration::Configuration()
	{
	}
	Configuration::Configuration(const std::filesystem::path& p)
	{
	    if(std::filesystem::exists(p)) open(p);
	    else create(p);
	}
	Configuration::Configuration(const std::filesystem::path& p,const std::filesystem::path& d)
	{
	    std::filesystem::path fullname = d/p;
	    if(std::filesystem::exists(fullname)) open(fullname);
	    else create(fullname);
	}



	//create funtion
    void Configuration::create(const std::filesystem::path& fn)
	{
	    //std::cout << "archivo :" << fn << "\n";
	    if(std::filesystem::exists(fn))
        {
            std::string strmsg = "Ya existe el archivo \"";
            strmsg += fn.string().c_str();
            strmsg += "\"";
            throw exception(strmsg);
        }

	    libconfig::Setting &root = getRoot();
	    libconfig::Setting &name_setting = root.add("name", libconfig::Setting::TypeString);
	    libconfig::Setting &decorated_setting = root.add("decorated", libconfig::Setting::TypeString);
	    //name_setting = "octetos";
        //version
        libconfig::Setting &version_setting = root.add("version", libconfig::Setting::TypeGroup);
        version_setting.add("major", libconfig::Setting::TypeInt) = 0;
        version_setting.add("minor", libconfig::Setting::TypeInt) = 0;
        version_setting.add("patch", libconfig::Setting::TypeInt) = 0;
        version_setting.add("prerelease", libconfig::Setting::TypeString) = "";
        version_setting.add("build", libconfig::Setting::TypeString) = "";
	}

    std::string Configuration::get_name() const
    {
        if(getRoot().exists("name"))
        {
            return (std::string)lookup("name");
        }

        return "";
    }
    Semver Configuration::get_version()const
    {
        Semver version;
        if(getRoot().exists("version"))
        {
            const libconfig::Setting &version_setting = lookup("version");
            version.major = version_setting.lookup("major");
            version.minor = version_setting.lookup("minor");
            version.patch = version_setting.lookup("patch");
            version.prerelease = (std::string)version_setting.lookup("prerelease");
            version.build = (std::string)version_setting.lookup("build");
        }

        return version;
    }
    std::string Configuration::get_decorated() const
    {
        if(getRoot().exists("decorated"))
        {
            return (std::string)lookup("decorated");
        }

        return "";
    }
    void Configuration::open(const std::filesystem::path& p)
    {
	    if(not std::filesystem::exists(p))
        {
            std::string strmsg = "No existe el archivo \"";
            strmsg += p.string().c_str();
            strmsg += "\"";
            throw exception(strmsg);
        }

        readFile(p.string().c_str());
        libconfig::Setting &root = getRoot();

        if(exists("name"))
        {

        }
        else
        {
            libconfig::Setting &name_setting = root.add("name", libconfig::Setting::TypeString);
        }



        //version
        if(exists("version"))
        {
        }
        else
        {
            libconfig::Setting &version_setting = root.add("version", libconfig::Setting::TypeGroup);
            version_setting.add("major", libconfig::Setting::TypeInt) = 0;
            version_setting.add("minor", libconfig::Setting::TypeInt) = 0;
            version_setting.add("patch", libconfig::Setting::TypeInt) = 0;
            version_setting.add("prerelease", libconfig::Setting::TypeString) = "";
            version_setting.add("build", libconfig::Setting::TypeString) = "";
        }
    }
    void Configuration::save(const std::filesystem::path& p)
    {
	    if(p.empty())
        {
            std::string strmsg = "No se a asignaod un nombre de archivo, deve crear uno o abrir uno existeste";
            throw exception(strmsg);
        }

        /*std::filesystem::path parentdir = fn.parent_path();
        if(not std::filesystem::exists(parentdir) and (not parentdir.string().empty())) std::filesystem::create_directory(fn.parent_path());
        if(not std::filesystem::exists(fn))
        {
            std::ofstream file(fn);
            file.close();
        }*/

        writeFile(p.string().c_str());
    }

    void Configuration::write_name(const std::filesystem::path& file,const std::string& n)
    {
        libconfig::Setting &name_setting = lookup("name");
        name_setting = (std::string)n;
        writeFile(file.string().c_str());
    }
    void Configuration::write(const std::filesystem::path& file,const Version&)
    {
        writeFile(file.string().c_str());
    }
    void Configuration::write(const std::filesystem::path& file,const Semver& v)
    {
        libconfig::Setting &version_setting = lookup("version");
        version_setting["major"] = v.major;
        version_setting["minor"] = v.minor;
        version_setting["patch"] = v.patch;
        version_setting["prerelease"] = v.prerelease;
        version_setting["build"] = v.build;
        writeFile(file.string().c_str());
    }

}
