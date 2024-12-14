#ifndef OCTETOS_CORE_TABLE_HH_INCLUDED
#define OCTETOS_CORE_TABLE_HH_INCLUDED

#include "array.hh"

namespace oct::core::v3
{
    /**
    *\brief Representa una secuacion continua de datos, eqiuvalante al sequence
    *\param T Tipo de dato de la secuencia
    *\param C La cantidad de datos, si es 0, la asignacion es dinamica
    *\param R La cantidad de renglones, si es 0, la asignacion es dinamica
    **/
    template<typename T,index auto C = 0,index auto R = 0,index I = size_t> using table = array<array<T,C>,R>;

}

#endif // OCTETOS_CORE_TABLE_HH_INCLUDED
