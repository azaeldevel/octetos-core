
#ifndef OCTETOS_CORE_V3_CONFIGURATION
#define OCTETOS_CORE_V3_CONFIGURATION

#include <filesystem>
#include <libconfig.h++>

#include "version.hh"

namespace oct::core::v3
{
    class Configuration : public libconfig::Config
    {
    public:


    public:
        Configuration();
        Configuration(const std::filesystem::path& p);
        Configuration(const std::filesystem::path& p,const std::filesystem::path& d);

        //std::filesystem::path read(const std::filesystem::path& p);
        //void create();
        void create(const std::filesystem::path& p);
        //void create(const std::filesystem::path& p,const Version&);
        //void create(const std::filesystem::path& p,const Semver&);
        //void open();
        void open(const std::filesystem::path&);
        //void save();
        void save(const std::filesystem::path&);

        void write_name(const std::string&);
        void write(const Version&);
        void write(const Semver&);

        const std::string& get_name() const;
        const Semver& get_version() const;

    private:

    private:
        std::filesystem::path fullname;
        std::string name;
        Semver version;

    };

}


#endif

