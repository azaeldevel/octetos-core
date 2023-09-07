
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


#include "entity.hh"


namespace oct::core::v3
{

struct Node
{
    //virtual T& value() = 0;
};

class Branch : public Node
{
private:
    Node** childs;
    size_t size;

public:
    Branch();
    Branch(size_t s);
    ~Branch();

    Node*& operator [](size_t index);
    const Node*& operator [](size_t index) const;
    Node*& at(size_t index);
    const Node*& at(size_t index) const;
};
struct Nested : public Branch
{
};

struct Root : public Branch
{
public:
    Root() = default;
    Root(size_t size);
};

template<class T> struct Type : public Node
{
    T data;

    Type() = default;
    Type(T& t) : data(t)
    {
    }

    Type& operator = (const T& t)
    {
        data = t;

        return *this;
    }

    operator T&()
    {
        return data;
    }
    operator const T&() const
    {
        return data;
    }
};


}

#endif
