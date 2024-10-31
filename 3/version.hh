
#ifndef OCTEOTOS_CORE_V3_VERSION_HH
#define OCTEOTOS_CORE_V3_VERSION_HH

#include <string>

namespace oct::core::v3
{

    struct Version
    {
    };

    struct Semver : public Version
    {
        Semver();
        constexpr Semver(int ma, int mi) : major(ma),minor(mi),patch(0)
        {
        }

        int major;
        int minor;
        int patch;
        std::string prerelease;
        std::string build;
    };

}


#endif
