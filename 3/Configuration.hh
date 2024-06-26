
#ifndef OCTETOS_CORE_V3_CONFIGURATION
#define OCTETOS_CORE_V3_CONFIGURATION

#include <filesystem>
#include <libconfig.h++>

#include "version.hh"

namespace oct::core::v3
{
    /**
    *\brief Crea un archivo de configuracion estandar
    **/
    class Configuration : public libconfig::Config
    {
    public:


    public:
        Configuration();
        Configuration(const std::filesystem::path& p);
        Configuration(const std::filesystem::path& p,const std::filesystem::path& d);

        //std::filesystem::path read(const std::filesystem::path& p);
        //void create();

        /**
        *\brief Create a new config file and create the proper default config tree(whitout save on file), it shoul not be exists in that case throw a exception
        **/
        void create(const std::filesystem::path& p);
        //void create(const std::filesystem::path& p,const Version&);
        //void create(const std::filesystem::path& p,const Semver&);
        //void open();
        void open(const std::filesystem::path&);
        //void save();
        void save(const std::filesystem::path&);

        void write_name(const std::filesystem::path&,const std::string&);
        void write(const std::filesystem::path&,const Version&);
        void write(const std::filesystem::path&,const Semver&);

        const std::string& get_name() const;
        const Semver& get_version() const;

        /*const std::filesystem::path& get_file_name() const
        {
            return fullname;
        }*/

    private:

    private:
        //std::filesystem::path fullname;
        std::string name;
        Semver version;

    };

}


#endif

