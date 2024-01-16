
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
	    if(std::filesystem::exists(d))//existe el directorio
        {
            fullname = d/p;
            if(std::filesystem::exists(fullname)) open(p);
            else create(fullname);
        }
	    else
        {
            fullname = d/p;
            create(fullname);
        }
	}



	//create funtion
    void Configuration::create(const std::filesystem::path& fn)
	{
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

        writeFile(fullname.c_str());
	}
	void Configuration::create(const std::filesystem::path& p,const Version& v)
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
	}


    const std::string& Configuration::get_name() const
    {
        return name;
    }
    const Semver& Configuration::get_version()const
    {
        return version;
    }
    void Configuration::open(const std::filesystem::path& p)
    {
	    fullname = p;
        //std::cout << "reading : " << p << "\n";
        readFile(p.c_str());


        name = (std::string)lookup("name");


        const libconfig::Setting &version_setting = lookup("version");
        version.major = version_setting.lookup("major");
        version.minor = version_setting.lookup("minor");
        version.patch = version_setting.lookup("patch");
        version.prerelease = (std::string)version_setting.lookup("prerelease");
        version.build = (std::string)version_setting.lookup("build");
    }
    void Configuration::save()
    {
        writeFile(fullname.c_str());
    }

    void Configuration::write_name(const std::string& n)
    {
        libconfig::Setting &name_setting = lookup("name");
        name_setting = (std::string)n;
        writeFile(fullname.c_str());
    }
    void Configuration::write(const Version&)
    {
        writeFile(fullname.c_str());
    }
    void Configuration::write(const Semver& v)
    {
        libconfig::Setting &version_setting = lookup("version");
        version_setting["major"] = v.major;
        version_setting["minor"] = v.minor;
        version_setting["patch"] = v.patch;
        version_setting["patch"] = v.patch;
        version_setting["build"] = v.build;
        writeFile(fullname.c_str());
        version = v;
    }

}
