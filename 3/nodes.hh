
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
    **/
    class node
    {
    private:
    public:
        node() = default;
        virtual ~node() = default;
        
        virtual void resolve() const = 0;
    };

    /**
    *\brief Representa el nodo de un arbol
    *\param C Child
    *\param L label
    **/
    template<class C,class L> class Node : public std::vector<C*>
    {
    private:
        typedef std::vector<C*> BASE;
    private:

    public:
        Node() = default;
        Node(size_t s) : BASE(s)
        {
        }

    };








    /**
    *\brief Representa el nodo de un arbol
    *\param C Child
    *\param L label
    **/
    template<class C,class L = char> class Number
    {
    private:
        C number;
    public:
        Number() = default;
        Number(const C& n) : number(n)
        {
        }
    };


    /**
    *\brief Representa el nodo de un arbol
    *\param C Child
    *\param L label
    **/
    template<class C,class L = char> class operation : public Node<C,L>
    {
    private:
        typedef Node<C,L> BASE;

    public:
        operation() = default;
        operation(C& a,C& b) : BASE(2)
        {
            BASE::at(0) = &a;
            BASE::at(1) = &b;
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param C Child
    *\param L label
    **/
    template<class C,class L = char> class Addition : public operation<C,L>
    {
    private:
        typedef operation<C,L> BASE;

    public:
        Addition() = default;
        Addition(C& a,C& b) : BASE(a,b)
        {
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param C Child
    *\param L label
    **/
    template<class C,class L = char> class Subtration : public operation<C,L>
    {
    private:
        typedef operation<C,L> BASE;

    public:
        Subtration() = default;
        Subtration(C& a,C& b) : BASE(a,b)
        {
        }

    };
}

#endif
