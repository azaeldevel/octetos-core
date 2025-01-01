
#ifndef OCTETOS_CORE_V3_AST_HH
#define OCTETOS_CORE_V3_AST_HH

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
#include "Exception.hh"

#ifdef OCTETOS_CORE_V3_TDD
    #include <iostream>
#endif

namespace oct::core::v3::ast
{

    enum class typen
    {
        none,
        number,
        arithmetic,
            sum,
            rest,
            product,
            quotient,
    };

    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<typename T = typen> struct node
    {
        node() = default;
        node(const T& t) : type(t)
        {
        }

        T type;
    };


    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class T = typen> struct numeric : public node<T>
    {
    public:
        typedef numeric<T> NUMBER_NODE;

    public:
        numeric() = default;
        numeric(T t) : NUMBER_NODE(t)
        {
        }
        numeric(N d) : data(d)
        {
        }

    public:
        N data;
    };


    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class M,class T = typen> struct arithmetic : public node<T>
    {
    public:
        typedef node<T> ARITHMETIC_NODE;

    public:
        arithmetic() = default;
        arithmetic(T t) : ARITHMETIC_NODE(t)
        {
        }
        arithmetic(numeric<N,T>* n,numeric<M,T>* m) : ARITHMETIC_NODE(typen::arithmetic),a(n),b(m)
        {
        }
        arithmetic(numeric<N,T>& n,numeric<M,T>& m) : ARITHMETIC_NODE(typen::arithmetic),a(&n),b(&m)
        {
        }
        arithmetic(T t,numeric<N,T>* n,numeric<M,T>* m) : ARITHMETIC_NODE(t),a(n),b(m)
        {
        }
        arithmetic(T t,numeric<N,T>& n,numeric<M,T>& m) : ARITHMETIC_NODE(t),a(&n),b(&m)
        {
        }

        N result()const
        {
            switch(this->type)
            {
            case typen::sum:
                return a->data + b->data;
            case typen::rest:
                return a->data - b->data;
            case typen::product:
                return a->data * b->data;
            case typen::quotient:
                return a->data / b->data;
            default:
                throw exception("No se reconoce como una operacion aritmetica valida");
            }
        }

    public:
        numeric<N,T>* a;
        numeric<M,T>* b;
    };


}

#endif
