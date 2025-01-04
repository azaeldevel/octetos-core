
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
#include "numbers.hh"

#ifdef OCTETOS_CORE_V3_TDD
    #include <iostream>
#endif

namespace oct::core::v3::ast
{

    enum class typen
    {
        //command = -100,
        //eoi,//end of input
        none,

        //ASCII>>>
        NUL = 0,
        SOH,
        STX,
        ETX,
        EOT,
        ENQ,
        ACK,
        BEL,
        BS,
        TAB,
        LF,
        VT,
        FF,
        CR,
        SO,
        SI,
        DLE,
        DC1,
        DC2,
        DC3,
        DC4,
        NAK,
        SYN,
        ETB,
        CAN,
        EM,
        SUB,
        ESC,
        FS,
        GS,
        RS,
        US = 31,
        space,
        exclamation_mark,
        double_quote,
        symbol_numbers,
        symbol_money,
        percen,
        ampersan,
        single_quote,
        parenthesis_open,
        parenthesis_close,
        asterisk,
        plus,
        minus,
        dot,
        symbol_diagonal,
        digit_0		= 48,
        digit_1,
        digit_2,
        digit_3,
        digit_4,
        digit_5,
        digit_6,
        digit_7,
        digit_8,
        digit_9,
        symbol_column,
        semicolumn,
        less,
        equal,
        grater,
        question,
        arroba,
        //>>upper case
        char_A		= 65,
        char_B,
        char_C,
        char_D,
        char_E,
        char_F,
        char_G,
        char_H,
        char_I,
        char_J,
        char_K,
        char_L,
        char_M,
        char_N,
        char_O,
        char_P,
        char_Q,
        char_R,
        char_S,
        char_T,
        char_U,
        char_V,
        char_W,
        char_X,
        char_Y,
        char_Z,
        //>>

        //>>>
        char_a		=	97,
        char_b,
        char_c,
        char_d,
        char_e,
        char_f,
        char_g,
        char_h,
        char_i,
        char_j,
        char_k,
        char_l,
        char_m,
        char_n,
        char_o,
        char_p,
        char_q,
        char_r,
        char_s,
        char_t,
        char_u,
        char_v,
        char_w,
        char_x,
        char_y,
        char_z,

        EuroSign	= 218,
        //>>>Extended ASCII






        y_Diaeresis = 255,//ÿ
        //>>>UTF-8
        a_Macron	= 256,

        s_Coptic	= 999,
        //Inicode >>>


        //>>>Tokens
        base	= 0x110000,
        root,
        operation,
        number,
        arithmetic,
            addition,
            subtraction,
            product,
            quotient,
        nest,
            number_nested,
            nested_number,
            nested_nested,
        algebra,
            variable,

        keywords,

        statement,
            rvalue,

    };


    template<class N,class T> struct Nest;


    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<typename T = typen> struct node
    {
    public:
        node() : type(typen::none)
        {
        }
        node(T t) : type(t)
        {
        }
        node(const node& n) : type(n.type)
        {
        }
        node(const node* n) : type(n->type)
        {
        }
        virtual ~node()
        {
        }

        virtual void print(std::ostream& out) const
        {
            switch(this->type)
            {
            case typen::number:
                out << "Numero";
                break;
            case typen::arithmetic:
                out << "aritmetica";
                break;
            case typen::addition:
                out << "adiccion";
                break;
            case typen::subtraction:
                out << "substracion";
                break;
            case typen::product:
                out << "producto";
                break;
            case typen::quotient:
                out << "cociente";
                break;
            case typen::variable:
                out << "variable";
                break;
            default:
                out << "node-desconocido";
                break;
            }
        }


        bool is_arithmetic()const
        {
            switch(type)
            {
            case typen::addition:
            case typen::subtraction:
            case typen::product:
            case typen::quotient:
            case typen::nest:
                return true;
            default:
                return false;
                break;
            }
        }
        bool is_numeric()const
        {
            if(type == typen::number) return true;
            return false;
        }
        bool is_variable()const
        {
            if(type == typen::variable) return true;
            return false;
        }
    public:
        T type;
    };


    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<typename T = typen,typename N = node<T>> struct Node : public N, public array<N*>
    {
    public:
        typedef array<N*> ARRAY_BASE;

    public:
        Node() = default;
        Node(size_t s) : ARRAY_BASE(s)
        {
        }
        Node(T t) : N(t)
        {
        }
        Node(T t,size_t s) : N(t),ARRAY_BASE(s)
        {
        }
        Node(const Node& n) : N(n),ARRAY_BASE(n)
        {
        }
        Node(Node&& n) : N(n),ARRAY_BASE(std::move(n))
        {
        }
        virtual ~Node()
        {
        }

    };



    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<number D,typename T = typen,typename N = node<T>> struct Math : public Node<T,N>
    {
    public:
        typedef Node<T,N> NODE_BASE;

    public:
        Math() = default;
        Math(size_t s) : NODE_BASE(s)
        {
        }
        Math(T t) : NODE_BASE(t)
        {
        }
        Math(T t,size_t s) : NODE_BASE(t,s)
        {
        }
        Math(const Math& n) : NODE_BASE(n)
        {
        }
        Math(Math&& n) : NODE_BASE(std::move(n))
        {
        }
        virtual ~Math()
        {
        }

        D result() const
        {
            if(this->type == typen::rvalue)
            {
                for(size_t i = 0; i < this->size(); i++)
                {

                }
            }
        }

    };


    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class T = typen> struct Numeric : public node<T>
    {
    public:
        typedef node<T> NUMBER_NODE;

    public:
        Numeric() : NUMBER_NODE(typen::number),data(0)
        {
        }
        Numeric(const Numeric& o) : NUMBER_NODE(o),data(o.data)
        {
        }
        Numeric(const Numeric* o) : NUMBER_NODE(o),data(o->data)
        {
        }
        Numeric(T t) : NUMBER_NODE(t),data(0)
        {
        }
        Numeric(N d) : NUMBER_NODE(typen::number),data(d)
        {
        }
        Numeric(T t,N d) : NUMBER_NODE(t),data(d)
        {
        }
        virtual ~Numeric()
        {
        }

        virtual void print(std::ostream& out) const
        {
            switch(this->type)
            {
            case typen::number:
                out << N(data);
                break;
            case typen::variable:
                out << N(data);
                break;
            default:
                out << "Number-desconocido";
            }
        }

        virtual N result()const
        {
            return data;
        }

    public:
        N data;
    };



    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class T = typen> struct Variable : public Numeric<N,T>
    {
    public:
        typedef Numeric<N,T> NUMERIC_NODE;

    public:
        Variable() : NUMERIC_NODE(typen::variable)
        {
        }
        Variable(const Variable& o) : NUMERIC_NODE(o),name(o.name)
        {
        }
        Variable(const Variable* o) : NUMERIC_NODE(o),name(o->name)
        {
        }
        Variable(T t) : NUMERIC_NODE(t)
        {
        }
        Variable(N d) : NUMERIC_NODE(typen::variable,d)
        {
        }
        Variable(const char* n) : NUMERIC_NODE(typen::variable),name(n)
        {
        }
        Variable(const std::string& n) : NUMERIC_NODE(typen::variable),name(n)
        {
        }
        Variable(const std::string& n,N d) : NUMERIC_NODE(typen::variable,d),name(n)
        {
        }
        virtual ~Variable()
        {
        }

        virtual void print(std::ostream& out) const
        {
            switch(this->type)
            {
            case typen::number:
                out << N(this->data);
                break;
            case typen::variable:
                out << name;
                break;
            default:
                out << "variable-desconocido";
            }
        }

    public:
        std::string name;
    };

    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N,class M = N,class T = typen> struct Arithmetic : public node<T>
    {
    public:
        typedef node<T> ARITHMETIC_BASE;

    public:
        Arithmetic() :
            a(NULL),b(NULL),
            auto_free(false)
        {
        }
        Arithmetic(const Arithmetic* o) :
            ARITHMETIC_BASE(o),
            a(NULL),b(NULL),
            auto_free(true)
        {
            copy_opdos(o);
        }
        Arithmetic(const Arithmetic& o) :
            ARITHMETIC_BASE(o)
            ,a(NULL),b(NULL),
            auto_free(true)
        {
            copy_opdos(&o);
        }
        Arithmetic(T t) : ARITHMETIC_BASE(t)
        {
        }
        //

        void copy_opdos(const Arithmetic* o)
        {
            if(o->a->is_arithmetic())
            {
                a = (node<T>*)new Arithmetic((const Arithmetic*)o->a);
            }
            else
            {
                a = (node<T>*)new Numeric<N>((const Numeric<N>*)o->a);
            }
            if(o->b->is_arithmetic())
            {
                b = (node<T>*)new Arithmetic((const Arithmetic*)o->b);
            }
            else
            {
               b = (node<T>*)new Numeric<N>((const Numeric<N>*)o->b);
            }
            //this->type = o->type;
        }
        //
        Arithmetic(T t,Numeric<N,T>& n,Numeric<M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Arithmetic<N,M,T>& n,Numeric<M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Numeric<N,T>& n,Arithmetic<N,M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Arithmetic<N,M,T>& n,Arithmetic<N,M,T>& m) :
            ARITHMETIC_BASE(t)
            ,a(&n),b(&m),
            auto_free(false)
        {
        }

        //
        Arithmetic(T t,Numeric<N,T>* n,Numeric<M,T>* m) :
            ARITHMETIC_BASE(t),
            a(n),b(m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Arithmetic<N,M,T>* n,Numeric<M,T>* m) :
            ARITHMETIC_BASE(t),
            a(n),b(m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Numeric<N,T>* n,Arithmetic<N,M,T>* m) :
            ARITHMETIC_BASE(t),
            a(n),b(m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Arithmetic<N,M,T>* n,Arithmetic<N,M,T>* m) :
            ARITHMETIC_BASE(t),
            a(n),b(m),
            auto_free(false)
        {
        }

        //
        Arithmetic(T t,Nest<N,T>& n,Numeric<M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Numeric<N,T>& n,Nest<N,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Nest<N,T>& n,Nest<N,T>& m) :
            ARITHMETIC_BASE(t)
            ,a(&n),b(&m),
            auto_free(false)
        {
        }

        //
        Arithmetic(T t,Nest<N,T>& n,Arithmetic<N,M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(false)
        {
        }
        Arithmetic(T t,Arithmetic<N,M,T>& n,Nest<N,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),
            auto_free(false)
        {
        }


        virtual ~Arithmetic()
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


        virtual N result()const
        {
            switch(this->type)
            {
            case typen::addition:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() + static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() + static_cast<Numeric<M,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data + static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data + static_cast<Numeric<M,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
                break;
            case typen::subtraction:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() - static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() - static_cast<Numeric<M,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data - static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data - static_cast<Numeric<M,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
                break;
            case typen::product:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() * static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() * static_cast<Numeric<M,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data * static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data * static_cast<Numeric<M,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
                break;
            case typen::quotient:
                if(a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() / static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Arithmetic<N,M,T>*>(a)->result() / static_cast<Numeric<M,T>*>(b)->data;
                }
                else if(!a->is_arithmetic() and b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data / static_cast<Arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a->is_arithmetic() and !b->is_arithmetic())
                {
                    return static_cast<Numeric<N,T>*>(a)->data / static_cast<Numeric<M,T>*>(b)->data;
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
        Nest(const Nest& o) : NEST_NODE(o),content(o.content),auto_free(o.auto_free)
        {
        }
        Nest(const Nest* o) : NEST_NODE(o),content(o->content),auto_free(o->auto_free)
        {
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
                out << "(";
                static_cast<const Arithmetic<N>*>(content)->print(out);
                out << ")";
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
                return static_cast<const Arithmetic<N>*>(content)->result();
            default:
                throw exception("No se reconoce como una operacion aritmetica valida");
                break;
            }
        }

    public:
        node<T>* content;
        bool auto_free;
    };

}

#endif
