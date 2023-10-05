
#ifndef OCTETOS_CORE_V3_TREE_HH
#define OCTETOS_CORE_V3_TREE_HH

/**
 *  This file is part of octetos-core.
 *  octetos-core is a core C/C++ Octeto's library.
 *  Copyright (C) 2018  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */

#include <typeinfo>

#include "array.hh"


#ifdef OCTETOS_CORE_V3_TDD
    #include <iostream>
#endif

namespace oct::core::v3
{

template<class T> class Node : public array<Node<T>>
{
private:


protected:
    T data;

public:
    typedef array<Node<T>> BASE;

public:
    constexpr Node() = default;
    constexpr Node(BASE::Index i) : BASE(i)
    {
    }
    constexpr Node(BASE::Index i,T const* o) : BASE(i,o)
    {
    }
    constexpr Node(BASE const& a) : BASE(a)
    {
    }
    constexpr Node(T const& o) : data(o)
    {
    }
    constexpr Node(T const& o,BASE::Index i) : BASE(i),data(o)
    {
    }
    constexpr Node& operator = (Node const& o)
    {
        data.operator = (o.data);

        return *this;
    }
    constexpr bool operator == (Node const& o) const
    {
        return data.operator == (o.data);
    }
    constexpr bool operator != (Node const& o) const
    {
        return data.operator != (o.data);
    }
    operator T&()
    {
        return data;
    }
    constexpr operator T const&() const
    {
        return data;
    }
    T* operator ->()
    {
        return &data;
    }
    constexpr const T* operator ->() const
    {
        return &data;
    }

};


}

#endif
