#ifndef OCTETOS_CORE_TABLE_HH_INCLUDED
#define OCTETOS_CORE_TABLE_HH_INCLUDED

#include "numbers.hh"

namespace oct::core::v3
{

    /**
    *\brief Representa una arreglo
    *\param T Tipo de dato
    *\param R Renglones
    *\param C Columnas
    **/
    template<class T,index auto R = 0,index auto C = 0>
    struct Table
    {
    public:

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
        T data[R][C];
#pragma GCC diagnostic pop
    };
}

#endif // OCTETOS_CORE_TABLE_HH_INCLUDED
