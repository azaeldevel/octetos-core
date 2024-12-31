#ifndef OCTETOS_CORE_V3_STOCK_HH
#define OCTETOS_CORE_V3_STOCK_HH

#include "numbers.hh"

namespace oct::core::v3
{

    template<number T>
    struct Stockable
    {
    public:
        Stockable() = default;
        Stockable(T w, T h, T l) : width(w), height(h), length(l)
        {
        }

    public:
        T width, height, length;
    };


}

#endif // OCTETOS_CORE_V3_STOCK_HH
