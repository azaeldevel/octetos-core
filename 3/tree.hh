
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

#include "entity.hh"

#ifdef OCTETOS_OCTETOS_V3_TDD
    #include <iostream>
#endif // OCTETOS_OCTETOS_V3_TDD

namespace oct::core::v3
{

enum class qualifier
{
    none,
    branch,
        //branch_math,
    data,

};

struct Node
{
private:
    //bool _is_branch,_is_data;
    //std::type_info info;

public:
    virtual qualifier check() = 0;
    virtual bool is(const std::type_info&) = 0;

    /*Node(bool b, bool d, const std::type_info& t) : _is_branch(b),_is_data(d),info(t)
    {
    }*/
};

class Branch : public Node
{
protected:
    Node** childs;
    size_t size;

public:
    Branch() : childs(NULL),size(0)
    {
    }
    Branch(size_t s) : childs(new Node*[s]),size(s)
    {
    }
    virtual ~Branch()
    {
        if(childs) delete[] childs;
    }

    Node*& operator [](size_t i)
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }
    Node* const& operator [](size_t i) const
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }
    Node*& at(size_t i)
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }
    Node* const& at(size_t i) const
    {
        if(i < size) return childs[i];

        throw std::out_of_range("Indice fuera de rango");
    }

    virtual qualifier check()
    {
        return qualifier::branch;
    }
    virtual bool is(const std::type_info& info)
    {
        return typeid(Branch) == info;
    }

    void print(std::ostream& out,size_t ) const
    {

    }
};
class Math : public Branch
{
public:
    enum class Operator
    {
        none,
        addition,
        subtraction,
        multiplication,
        division,
        subexpression,
        assignment,
    };

private:
    Operator op;

public:
    Math()
    {
    }
    Math(size_t s, Operator o) : Branch(s),op(o)
    {
    }
    virtual ~Math()
    {
    }

    const char* describe() const
    {
        switch(op)
        {
            case Operator::addition : return "Addition";
            case Operator::subtraction : return "Subtraction";
            case Operator::multiplication : return "Multiplication";
            case Operator::division : return "Division";
            case Operator::subexpression : return "Sub-expression";
            case Operator::assignment : return "Assignment";
            default : return "Unknow";
        }
    }
    const char* to_string() const
    {
        switch(op)
        {
            case Operator::addition : return "+";
            case Operator::subtraction : return "-";
            case Operator::multiplication : return "*";
            case Operator::division : return "/";
            case Operator::subexpression : return "()";
            case Operator::assignment : return "=";
            default : return "Unknow";
        }
    }

    virtual qualifier check()
    {
        return qualifier::branch;
    }
    virtual bool is(const std::type_info& info)
    {
        return typeid(Math) == info;
    }

    void print(std::ostream& out,size_t begin) const
    {
        std::string spaces;
        size_t margin = 7;
        spaces.insert(0,begin + margin,' ');

        out << spaces << "--";
        //TODO: opetner el valor del nodo
        out << '0';
        out << "-|\n";
        for(size_t i = 0; i < size; i++)
        {
            out << spaces << "--";
            //TODO: opetner el valor del nodo
            out << to_string();
            out << "-|\n";

            out << spaces << "--";
            //TODO: opetner el valor del nodo
            out << '0';
            out << "-|\n";
        }
    }
};

struct Root : public Branch
{
public:
    Root() = default;
    Root(size_t size) : Branch(size)
    {
    }



    virtual qualifier check()
    {
        return qualifier::branch;
    }
    virtual bool is(const std::type_info& info)
    {
        return typeid(Root) == info;
    }

#ifdef OCTETOS_OCTETOS_V3_TDD
    void print(std::ostream& out) const
    {
        out << "Root-|\n";
        size_t margin = 5;
        std::string spaces;
        spaces.insert(0,margin,' ');
        for(size_t i = 0; i < size; i++)
        {
            if(at(i)->is(typeid(const Math)))
            {
                out << spaces << "--Math-|\n";
                ((const Math*)at(i))->print(out,margin);
            }
            else if(at(i)->is(typeid(const Branch)))
            {
                out << spaces << "--Branch-|\n";
                ((const Branch*)at(i))->print(out,margin);
            }
        }
    }
#endif
};

template<class T> struct Data : public Node
{
    T data;

    Data() = default;
    Data(const T& t) : data(t)
    {
    }

    Data& operator = (const T& t)
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



    virtual qualifier check()
    {
        return qualifier::data;
    }
    virtual bool is(const std::type_info& info)
    {
        return typeid(Data<T>) == info;
    }

    void print(std::ostream& out) const
    {

    }
};


}

#endif
