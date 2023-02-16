
#ifndef OCTETOS_CORE_ARRAYS
#define OCTETOS_CORE_ARRAYS

#include <vector>
#include <iostream>
#include <initializer_list>


namespace oct::core::v3
{

template<typename T>
class array
{
public:
    constexpr array() = delete;
    constexpr array(std::initializer_list<T> list) : _size(list.size())
    {

    }
    constexpr array(size_t reserved) : _size(reserved)
    {

    }

public:
    const size_t _size;
    //T _data[_size];
};

}


#endif
