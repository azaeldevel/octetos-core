
#ifndef OCTETOS_CORE_V3_NODES_HH
#define OCTETOS_CORE_V3_NODES_HH

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

#include <vector>

#ifdef OCTETOS_CORE_V3_TDD
    #include <iostream>
#endif

namespace oct::core::v3
{

    /**
    *\brief Representa el nodo de un arbol
    *\param C Child
    **/
    template<class T> class node
    {
    private:
    public:
        node() = default;
        virtual ~node() = default;
        
        virtual operator T() = 0;
    };

    /**
    *\brief Representa el nodo de un arbol
    *\param T Child
    **/
    template<class T> class Node : public std::vector<node<T>*>
    {
    private:
        typedef std::vector<node<T>*> BASE;
    private:

    public:
        Node() = default;
        Node(size_t s) : BASE(s)
        {
        }

    };








    /**
    *\brief Representa el nodo de un arbol
    *\param T Child
    *\param L label
    **/
    template<class T,class L = char> class Number
    {
    private:
        T number;
    public:
        Number() = default;
        Number(const T& n) : number(n)
        {
        }

        virtual operator T()
        {
            return number;
        }
    };


    /**
    *\brief Representa el nodo de un arbol
    *\param T Type
    *\param L label
    **/
    template<class T,class L = char> class operation : public Node<T>
    {
    private:
        typedef Node<T> BASE;

    public:
        operation() = default;
        operation(Number<T>& a,Number<T>& b) : BASE(2)
        {
            BASE::at(0) = reinterpret_cast<node<T>*>(&a);
            BASE::at(1) = reinterpret_cast<node<T>*>(&b);
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param T Type
    *\param L label
    **/
    template<class T,class L = char> class Addition : public operation<T>
    {
    private:
        typedef operation<T> BASE;

    public:
        Addition() = default;
        Addition(Number<T>& a,Number<T>& b) : BASE(a,b)
        {
        }

        virtual operator T()
        {
            Number<T>& a = reinterpret_cast<Number<T>&>(*BASE::at(0));
            Number<T>& b = reinterpret_cast<Number<T>&>(*BASE::at(1));
            return T(a) + T(b);
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param C Child
    *\param L label
    **/
    template<class T,class L = char> class Subtration : public operation<T,L>
    {
    private:
        typedef operation<T,L> BASE;

    public:
        Subtration() = default;
        Subtration(Number<T>& a,Number<T>& b) : BASE(a,b)
        {
        }

        virtual operator T()
        {
            Number<T>& a = reinterpret_cast<Number<T>&>(*BASE::at(0));
            Number<T>& b = reinterpret_cast<Number<T>&>(*BASE::at(1));
            return T(a) - T(b);
        }
    };
}

#endif
