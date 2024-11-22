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


        constexpr T* operator [](I const& i)
        {
            return data[i];
        }
        constexpr const T* operator [](I const& i) const
        {
            return data[i];
        }
        constexpr T& at(I const& i,I const& j)
        {
            if(i < R) if(j < C) return data[i][j];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr T const& at(I const& i,I const& j) const
        {
            if(i < R) if(j < C) return data[i][j];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr operator T*()
        {
            return (T*)&data;
        }
        constexpr operator const T*() const
        {
            return (const T*)&data;
        }
#ifdef __cpp_multidimensional_subscript
        constexpr T& operator [](I const& i,I const& j)
        {
            if(i < R) if(j < C) return data[i][j];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr T const& operator [](I const& i,I const& j)const
        {
            if(i < R) if(j < C) return data[i][j];

            throw std::out_of_range("Indice fuera de rango");
        }
#endif


    };
}

#endif // OCTETOS_CORE_TABLE_HH_INCLUDED
