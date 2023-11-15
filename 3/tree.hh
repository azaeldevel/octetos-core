
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

    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<typename T> class Node : public array<Node<T>*>
    {
    public:
        typedef array<Node<T>*> BASE;

    public:
        Node() = default;
        Node(const T& t) : type(t)
        {
        }
        Node(const T& t,size_t s) : type(t),BASE(s,NULL)
        {
        }
        Node(const std::initializer_list<Node<T>>& l) : BASE(l)
        {
        }
        Node(const T& t,const std::initializer_list<Node<T>>& l) : type(t),BASE(l)
        {
        }

        /**
        *\brief Asigna el type
        *
        **/
        void set(const T& t)
        {
            type = t;
        }


#ifdef OCTETOS_CORE_V3_TDD
        virtual void print(std::ostream& out) const
        {
        }
#endif

    private:
        T type;

    };


}

#endif
