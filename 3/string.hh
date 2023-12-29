
#ifndef OCTETOS_CORE_V3_STRING
#define OCTETOS_CORE_V3_STRING

#include <string>
#include <vector>

namespace oct::core::v3
{

    template<class T> std::string toupper(const T& from)
    {
        T to = from;
        for(size_t i = 0; i < to.size(); i++)
        {
            to[i] = std::toupper(to[i]);
        }
        return to;
    }

}


#endif

