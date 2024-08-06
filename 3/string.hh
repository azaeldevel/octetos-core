
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


    std::vector<std::string> split(const std::string& from,const std::string& delim = "\n");

    template <class C = std::vector<std::string>> C split(const std::string& str, char sep)
    {
        C result;
        size_t begin = 0,end = 0;
        for(size_t i = 0; i < str.size(); i++)
        {
            if(str[i] == sep)
            {
                end = i;
                result.push_back(std::string(str,begin,end - begin));
                begin = i + 1;
            }
        }
        if(begin > 0 and end < begin)//el ultimio elemento
        {
            result.push_back(std::string(str,begin,str.size() - begin));
        }
        else if(result.empty())
        {
            result.push_back(str);
        }

        return result;
    }

}


#endif

