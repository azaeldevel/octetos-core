
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
        fullname = p;
	    if(std::filesystem::exists(p)) open(p);
	    else create(p);
	}
	Configuration::Configuration(const std::filesystem::path& p,const std::filesystem::path& d)
	{
	    fullname = d/p;
	    if(std::filesystem::exists(p)) open(p);
	    else create(p);
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

	    //std::cout << "archivo :" << fn << "\n";
	    fullname = fn;
	    libconfig::Setting &root = getRoot();
	    //System key name
	    libconfig::Setting &name_setting = root.add("name", libconfig::Setting::TypeString);
        name_setting = name;

        //version
        libconfig::Setting &version_setting = root.add("version", libconfig::Setting::TypeGroup);
        version_setting.add("major", libconfig::Setting::TypeInt) = 0;
        version_setting.add("minor", libconfig::Setting::TypeInt) = 0;
        version_setting.add("patch", libconfig::Setting::TypeInt) = 0;
        version_setting.add("prerelease", libconfig::Setting::TypeString) = "";
        version_setting.add("build", libconfig::Setting::TypeString) = "";

        //std::cout << "check : "  << fullname << "\n";
        std::filesystem::path parentdir = fullname.parent_path();
        if(not std::filesystem::exists(parentdir) and (not parentdir.string().empty())) std::filesystem::create_directory(fullname.parent_path());
        if(not std::filesystem::exists(fullname))
        {
            std::ofstream file(fullname);
            file.close();
        }
        //std::cout << "write : " << fullname << "\n";

        writeFile(fullname.string().c_str());
        //std::cout << "write : " << fullname << "\n";
	}
	/*void Configuration::create(const std::filesystem::path& p,const Version& v)
	{
	    fullname = p;
	    create(p);
        write(v);
	}
	void Configuration::create(const std::filesystem::path& p,const Semver& v)
	{
	    fullname = p;
	    create(p);
        write(v);
	}*/


    const std::string& Configuration::get_name() const
    {
        return name;
    }
    const Semver& Configuration::get_version()const
    {
        return version;
    }
    /*void Configuration::open()
    {
        open(fullname);
    }*/
    void Configuration::open(const std::filesystem::path& p)
    {
	    if(not std::filesystem::exists(p))
        {
            std::string strmsg = "No existe el archivo \"";
            strmsg += p.string().c_str();
            strmsg += "\"";
            throw exception(strmsg);
        }

	    fullname = p;
        std::cout << "reading : " << p << "\n";
        readFile(p.string().c_str());
        libconfig::Setting &root = getRoot();



        if(exists("name"))
        {
            name = (std::string)lookup("name");
        }
        else
        {
            libconfig::Setting &name_setting = root.add("name", libconfig::Setting::TypeString);
            name_setting = name;
        }



        //version
        if(exists("version"))
        {
            const libconfig::Setting &version_setting = lookup("version");
            version.major = version_setting.lookup("major");
            version.minor = version_setting.lookup("minor");
            version.patch = version_setting.lookup("patch");
            version.prerelease = (std::string)version_setting.lookup("prerelease");
            version.build = (std::string)version_setting.lookup("build");
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

        writeFile(p.string().c_str());
    }
    /*void Configuration::save()
    {
	    if(fullname.empty())
        {
            std::string strmsg = "No se a asignaod un nombre de archivo, deve crear uno o abrir uno existeste";
            throw exception(strmsg);
        }

        if(not std::filesystem::exists(fullname))
        {
            create(fullname);
        }

        writeFile(fullname.string().c_str());
    }*/

    void Configuration::write_name(const std::string& n)
    {
        libconfig::Setting &name_setting = lookup("name");
        name_setting = (std::string)n;
        writeFile(fullname.string().c_str());
    }
    void Configuration::write(const Version&)
    {
        writeFile(fullname.string().c_str());
    }
    void Configuration::write(const Semver& v)
    {
        libconfig::Setting &version_setting = lookup("version");
        version_setting["major"] = v.major;
        version_setting["minor"] = v.minor;
        version_setting["patch"] = v.patch;
        version_setting["prerelease"] = v.prerelease;
        version_setting["build"] = v.build;
        writeFile(fullname.string().c_str());
        version = v;
    }

}
