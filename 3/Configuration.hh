
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
        *\brief
        **/
        void open(const std::filesystem::path&);
        /**
        *\brief
        **/
        void save(const std::filesystem::path&);

        void write_name(const std::string&);
        void write(const Semver&);

        std::string get_name() const;
        std::string get_decorated() const;
        Semver get_version() const;
    private:

    private:

    };

}


#endif

