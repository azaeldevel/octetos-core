
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
#endif // OCTETOS_OCTETOS_V3_TDD

namespace oct::core::v3
{


template<class T> class Node : public array<T*>
{
private:

public:
    typedef array<T*> BASE;

public:
    Node() = default;
    Node(BASE::Index i) : BASE(i)
    {
    }
    Node(BASE::Index i,T* const* o) : BASE(i,o)
    {
    }
    Node(BASE const& a) : BASE(a)
    {
    }

};


class Number : public Node<Real>
{
private:

public:
    typedef Node<Real> BASE;

public:
    Number() = default;
    Number(BASE::Index i) : BASE(i)
    {
    }
    Number(BASE::Index i, Real* const* o) : BASE(i,o)
    {
    }
    Number(BASE const& a) : BASE(a)
    {
    }

};

class Addition : public Node<Number>
{
private:

public:
    typedef Node<Number> BASE;

public:
    Addition() = default;
    Addition(BASE::Index i) : BASE(i)
    {
    }
    Addition(BASE::Index i, Number* const* o) : BASE(i,o)
    {
    }
    Addition(BASE const& a) : BASE(a)
    {
    }

};


class Diference : public Node<Number>
{
private:

public:
    typedef Node<Number> BASE;

public:
    Diference() = default;
    Diference(BASE::Index i) : BASE(i)
    {
    }
    Diference(BASE::Index i, Number* const* o) : BASE(i,o)
    {
    }
    Diference(BASE const& a) : BASE(a)
    {
    }

};

class Product : public Node<Number>
{
private:

public:
    typedef Node<Number> BASE;

public:
    Product() = default;
    Product(BASE::Index i) : BASE(i)
    {
    }
    Product(BASE::Index i, Number* const* o) : BASE(i,o)
    {
    }
    Product(BASE const& a) : BASE(a)
    {
    }

};


class Division : public Node<Number>
{
private:

public:
    typedef Node<Number> BASE;

public:
    Division() = default;
    Division(BASE::Index i) : BASE(i)
    {
    }
    Division(BASE::Index i, Number* const* o) : BASE(i,o)
    {
    }
    Division(BASE const& a) : BASE(a)
    {
    }

};

}

#endif
