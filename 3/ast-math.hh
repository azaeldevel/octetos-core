
#ifndef OCTETOS_CORE_V3_AST_MATH_HH
#define OCTETOS_CORE_V3_AST_MATH_HH

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


#include "ast.hh"


namespace oct::core::v3::ast
{
    template<class N,class T> struct Variable;
    template<class N,class T> struct Number;
    template<class N,class T> struct Binopr;
    template<class N,class T> struct Nest;

    template<class N,class T>
    node<T>* copy(const node<T>* n)
    {
        switch(n->type)
        {
        case typen::addition:
        case typen::subtraction:
        case typen::product:
        case typen::quotient:
            return new Binopr<N,T>(static_cast<const Binopr<N,T>*>(n));
        case typen::nest:
            return new Nest<N,T>(static_cast<const Nest<N,T>*>(n));
        case typen::number:
            return new Number<N,T>(static_cast<const Number<N,T>*>(n));
        case typen::variable:
            return new Variable<N,T>(static_cast<const Variable<N,T>*>(n));
        default:
            break;
        }

        return NULL;
    }

    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class T = typen> struct Number : public node<T>
    {
    public:
        typedef node<T> NUMBER_NODE;

    public:
        Number() : NUMBER_NODE(T::number),data(0)
        {
        }
        Number(const Number& o) : NUMBER_NODE(o),data(o.data)
        {
        }
        Number(const Number* o) : NUMBER_NODE(o),data(o->data)
        {
        }
        Number(T t) : NUMBER_NODE(t),data(0)
        {
        }
        Number(N d) : NUMBER_NODE(T::number),data(d)
        {
        }
        Number(T t,N d) : NUMBER_NODE(t),data(d)
        {
        }
        virtual ~Number()
        {
        }

        virtual void print(std::ostream& out) const
        {
            switch(this->type)
            {
            case T::number:
                out << N(data);
                break;
            case T::variable:
                out << N(data);
                break;
            default:
                out << "Number-desconocido";
            }
        }

        operator N()const
        {
            return data;
        }
        Number& operator = (const N& i)
        {
            data = i;
            return *this;
        }
        virtual N result()const
        {
            return data;
        }

        unsigned deep()const
        {
            return 0;
        }

    public:
        N data;
    };


    /**
    *\brief Indica una variable(columna) en la tabla de inputs
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class R = size_t,class T = typen> struct Variable : public node<T>
    {
    public:
        typedef node<T> NUMERIC_NODE;

    public:
        Variable() : NUMERIC_NODE(T::variable),name("variable")
        {
        }
        Variable(const Variable& o) : NUMERIC_NODE(o),name(o.name),reference(o.reference)
        {
        }
        Variable(const Variable* o) : NUMERIC_NODE(o),name(o->name),reference(o->reference)
        {
        }
        Variable(T t) : NUMERIC_NODE(t),name("variable")
        {
        }
        Variable(const R& d) : NUMERIC_NODE(T::variable),name("variable"),reference(d)
        {
        }
        Variable(const char* n) : NUMERIC_NODE(T::variable),name(n)
        {
        }
        Variable(const char* n,const R& d) : NUMERIC_NODE(T::variable),name(n),reference(d)
        {
        }
        Variable(const std::string& n) : NUMERIC_NODE(T::variable),name(n)
        {
        }
        Variable(const std::string& n,const R& d) : NUMERIC_NODE(T::variable),name(n),reference(d)
        {
        }
        virtual ~Variable()
        {
        }

        virtual void print(std::ostream& out) const
        {
            switch(this->type)
            {
            case T::variable:
                out << name;
                break;
            default:
                out << "variable-desconocido";
            }
        }

        operator R()const
        {
            return reference;
        }
        Variable& operator = (const R& i)
        {
            reference = i;
            return *this;
        }
        R result()const
        {
            return reference;
        }

        unsigned deep()const
        {
            return 0;
        }

    public:
        std::string name;
        R reference;//dato input
    };


    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class T = typen> struct Binopr : public node<T>
    {
    public:
        typedef node<T> ARITHMETIC_BASE;

    public:
        Binopr() :
            a(NULL),b(NULL),
            auto_free(false)
        {
        }
        Binopr(const Binopr* o) :
            ARITHMETIC_BASE(o),
            a(NULL),b(NULL),
            auto_free(true)
        {
            copy_opdos(o);
        }
        Binopr(const Binopr& o) :
            ARITHMETIC_BASE(o)
            ,a(NULL),b(NULL),
            auto_free(true)
        {
            copy_opdos(&o);
        }
        Binopr(T t) : ARITHMETIC_BASE(t)
        {
        }
        //

        void copy_opdos(const Binopr* o)
        {
            a = copy<N,T>(o->a);
            b = copy<N,T>(o->b);
        }

        //
        template<template<typename> typename A, template<typename> typename B>
        Binopr(T t,A<T>* n,B<T>* m,bool autof = true) :
            ARITHMETIC_BASE(t),
            a(n),b(m),
            auto_free(autof)
        {
        }

        //
        template<template<typename,typename> typename A, template<typename,typename> typename B>
        Binopr(T t,A<N,T>* n,B<N,T>* m,bool autof = true) :
            ARITHMETIC_BASE(t),
            a(n),b(m),
            auto_free(autof)
        {
        }

        //
        template<template<typename,typename> typename A, template<typename,typename> typename B>
        Binopr(T t,A<N,T>& n,B<N,T>& m,bool autof = false) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(autof)
        {
        }


        virtual ~Binopr()
        {
            if(auto_free)
            {
                delete a;
                delete b;
                a = NULL;
                b = NULL;
            }
        }

        virtual void print(std::ostream& out) const
        {
            //
            out << " ";
            a->print(out);
            out << " ";
            //
            switch(this->type)
            {
            case typen::addition:
                out << " + ";
                break;
            case typen::subtraction:
                out << " - ";
                break;
            case typen::product:
                out << " * ";
                break;
            case typen::quotient:
                out << " / ";
                break;
            default:
                out << "desconocido";
                break;
            }
            //
            out << " ";
            b->print(out);
            out << " ";
        }



        /*template<template<typename, typename> typename A>
        const A<N,T>* from_a() const
        {
            switch(a->type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
                return static_cast<Binopr<N,T>*>(a);
            case typen::nest:
                return static_cast<Nest<N,T>*>(a);
            case typen::number:
                return static_cast<Number<N,T>*>(a);
            case typen::variable:
                return static_cast<Variable<N,T>*>(a);
            default:
                break;
            }

            return NULL;
        }

        template<template<typename, typename> typename B>
        const B<N,T>* from_b() const
        {
            switch(b->type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
                return static_cast<Binopr<N,T>*>(b);
            case typen::nest:
                return static_cast<Nest<N,T>*>(b);
            case typen::number:
                return static_cast<Number<N,T>*>(b);
            case typen::variable:
                return static_cast<Variable<N,T>*>(b);
            default:
                break;
            }

            return NULL;
        }

        virtual N result2()const
        {
            switch(this->type)
            {
            case typen::addition:
                return from_a()->result() + from_b()->result();
            case typen::subtraction:
                return from_a()->result() - from_b()->result();
            case typen::product:
                return from_a()->result() * from_b()->result();
            case typen::quotient:
                return from_a()->result() / from_b()->result();
            default:
                break;
            }

        }*/

        virtual N result()const
        {
            switch(this->type)
            {
            case typen::addition:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() + static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() + static_cast<Number<N,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data + static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data + static_cast<Number<N,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
                break;
            case typen::subtraction:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() - static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() - static_cast<Number<N,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data - static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data - static_cast<Number<N,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
                break;
            case typen::product:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() * static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() * static_cast<Number<N,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data * static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data * static_cast<Number<N,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
                break;
            case typen::quotient:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() / static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Binopr<N,T>*>(a)->result() / static_cast<Number<N,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data / static_cast<Binopr<N,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Number<N,T>*>(a)->data / static_cast<Number<N,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
                break;
            default:
                throw exception("No se reconoce como una operacion aritmetica valida");
            }
        }

        unsigned deep_a()const
        {
            switch(a->type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
                return 1 + static_cast<Binopr<N,T>*>(a)->deep();
            case typen::nest:
                return 1 + static_cast<Nest<N,T>*>(a)->deep();
            case typen::number:
                return 1;
            case typen::variable:
                return 1;
            default:
                break;
            }

            return 0;
        }
        unsigned deep_b()const
        {
            switch(b->type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
                return 1 + static_cast<Binopr<N,T>*>(b)->deep();
            case typen::nest:
                return 1 + static_cast<Nest<N,T>*>(b)->deep();
            case typen::number:
                return 1;
            case typen::variable:
                return 1;
            default:
                break;
            }

            return 0;
        }
        unsigned deep()const
        {
            unsigned da = deep_a(), db = deep_b();
            if(da > db) return da;
            return db;
        }

    public:
        node<T>* a;
        node<T>* b;
        //bool a_nested,b_nested;
        bool auto_free;
    };

    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class T = typen> struct Nest : public node<T>
    {
    public:
        typedef node<T> NEST_NODE;

    public:
        Nest() : NEST_NODE(typen::nest),content(NULL),auto_free(false)
        {
        }
        Nest(const Nest& o) : NEST_NODE(o),content(NULL),auto_free(true)
        {
            content = copy<N,T>(o.content);
        }
        Nest(const Nest* o) : NEST_NODE(o),content(NULL),auto_free(true)
        {
            content = copy<N,T>(o->content);
        }
        Nest(T t) : NEST_NODE(t),content(NULL),auto_free(false)
        {
        }
        Nest(node<T>* n) : NEST_NODE(typen::nest),content(n),auto_free(false)
        {
        }
        Nest(node<T>& n) : NEST_NODE(typen::nest),content(&n),auto_free(false)
        {
        }
        Nest(T t,node<T>* n) : NEST_NODE(t),content(n),auto_free(false)
        {
        }
        Nest(T t,node<T>* n,bool autof) : NEST_NODE(t),content(n),auto_free(autof)
        {
        }
        virtual ~Nest()
        {
            if(auto_free)
            {
                delete content;
                content = NULL;
                auto_free = false;
            }
        }

        virtual void print(std::ostream& out) const
        {
            switch(content->type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
                static_cast<const Binopr<N>*>(content)->print(out);
                break;
            case typen::nest:
                static_cast<const Nest<N>*>(content)->print(out);
                break;
            case typen::number:
                static_cast<const Number<N>*>(content)->print(out);
                break;
            case typen::variable:
                static_cast<const Variable<N>*>(content)->print(out);
                break;
            default:
                out << "nest-desconocido";
                break;
            }
        }

        virtual N result() const
        {
            switch(content->type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
                return static_cast<const Binopr<N>*>(content)->result();
            case typen::nest:
                return static_cast<const Nest<N>*>(content)->result();
            case typen::number:
                return static_cast<const Number<N>*>(content)->result();
            case typen::variable:
                return static_cast<const Variable<N>*>(content)->result();
            default:
                throw exception("No se reconoce como una operacion aritmetica valida");
                break;
            }
        }

        unsigned deep()const
        {
            switch(content->type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
                return 1 + static_cast<Binopr<N,T>*>(content)->deep();
            case typen::nest:
                return 1 + static_cast<Nest<N,T>*>(content)->deep();
            case typen::number:
                return 1;
            case typen::variable:
                return 1;
            default:
                break;
            }

            return 0;
        }

    public:
        node<T>* content;
        bool auto_free;
    };

}

#endif
