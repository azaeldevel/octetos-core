
#ifndef OCTETOS_CORE_ARRAYS
#define OCTETOS_CORE_ARRAYS

#include <vector>
#include <iostream>
#include <initializer_list>

#include "Exception.hh"

namespace oct::core::v3
{

template<typename T>
class array
{
public:
    constexpr array() = delete;
    constexpr array(size_t reserved) : _size(reserved),_begin(new T)
    {
    }
    constexpr array(std::initializer_list<T> list) : _size(list.size()),_begin(new T)
    {
        for(size_t i = 0; i < _size; i++)
        {
            _begin[i] = list.begin()[i];
        }
    }
    constexpr array(const array& a) : _size(a._size),_begin(new T)
    {

    }
    const T* begin() const
    {
        return _begin;
    }
    const T* end() const
    {
        return _begin + (_size - 1);
    }
    T& operator [](size_t i)
    {
        if(i < _size) return _begin[i];

        throw exception("Indice fuera de rango");
    }
/*#if defined(__GNUC__)

#elif defined(__clang__)
    #error "Sin emplementar"
#elif defined(_MSC_VER)
    #error "Sin emplementar"
#else
    #error "Compilador desconocido"
#endif
*/
private:

private:
    size_t _size;
    T* _begin;
};

}


#endif
