
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
        number,
        arithmetic,
            addition,
            subtraction,
            product,
            quotient,
            number_nested,
            nested_number,
            nested_nested,

        keywords,

        statement,


    };

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
        node(const T& t) : type(t)
        {
        }
        node(const node& n) : type(n.type)
        {
        }
        node(const node* n) : type(n->type)
        {
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


#ifdef OCTETOS_CORE_V3_TDD
        virtual void print(std::ostream& out) const
        {
        }
#endif



    };

    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N=float,class T = typen> struct numeric : public node<T>
    {
    public:
        typedef node<T> NUMBER_NODE;

    public:
        numeric() = default;
        numeric(T t) : NUMBER_NODE(t)
        {
        }
        numeric(N d) : data(d)
        {
        }
        numeric(const numeric& o) : NUMBER_NODE(o),data(o.data)
        {
        }
        numeric(const numeric* o) : NUMBER_NODE(o),data(o->data)
        {
        }

    public:
        N data;
    };


    /**
    *\brief Crea un nodo
    *\param T parametro de plantilla para determinar el tipo de nodo
    **/
    template<class N=float,class M = N,class T = typen> struct arithmetic : public node<T>
    {
    public:
        typedef node<T> ARITHMETIC_BASE;

    public:
        arithmetic() : a(NULL),b(NULL),a_nested(false),b_nested(false),auto_free(false)
        {
        }
        arithmetic(const arithmetic* o) :
            ARITHMETIC_BASE(o),a(NULL),b(NULL),
            a_nested(o->a_nested),b_nested(o->b_nested),
            auto_free(true)
        {
            copy_opdos(o);
        }
        arithmetic(const arithmetic& o) :
            ARITHMETIC_BASE(o),a(NULL),b(NULL),
            a_nested(o.a_nested),b_nested(o.b_nested),
            auto_free(true)
        {
            copy_opdos(&o);
        }
        arithmetic(T t) : ARITHMETIC_BASE(t)
        {
        }
        arithmetic(numeric<N,T>* n,numeric<M,T>* m) :
            ARITHMETIC_BASE(typen::arithmetic)
            ,a(n),b(m),a_nested(false),b_nested(false),
            auto_free(false)
        {
        }
        arithmetic(numeric<N,T>& n,numeric<M,T>& m) :
            ARITHMETIC_BASE(typen::arithmetic),a(&n),b(&m),
            a_nested(false),b_nested(false),
            auto_free(false)
        {
        }
        arithmetic(T t,numeric<N,T>* n,numeric<M,T>* m) :
            ARITHMETIC_BASE(t),
            a(n),b(m),a_nested(false),b_nested(false),
            auto_free(false)
        {
        }
        arithmetic(T t,numeric<N,T>& n,numeric<M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),a_nested(false),b_nested(false),
            auto_free(false)
        {
        }
        void copy_opdos(const arithmetic* o)
        {
            if(o->a_nested)
            {
                a = (node<T>*)new arithmetic((const arithmetic*)o->a);
            }
            else
            {
                a = (node<T>*)new numeric<N>((const numeric<N>*)o->a);
            }
            if(o->b_nested)
            {
                b = (node<T>*)new arithmetic((const arithmetic*)o->b);
            }
            else
            {
               b = (node<T>*)new numeric<N>((const numeric<N>*)o->b);
            }
            //this->type = o->type;
        }
        ~arithmetic()
        {
            if(auto_free)
            {
                delete a;
                delete b;
                a = NULL;
                b = NULL;
            }
        }

        //nested
        arithmetic(T t,arithmetic<N,M,T>& n,numeric<M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),a_nested(true),b_nested(false),
            auto_free(false)
        {
        }
        arithmetic(T t,numeric<N,T>& n,arithmetic<N,M,T>& m) :
            ARITHMETIC_BASE(t),
            a(&n),b(&m),a_nested(false),b_nested(true),
            auto_free(false)
        {
        }
        arithmetic(T t,arithmetic<N,M,T>& n,arithmetic<N,M,T>& m) :
            ARITHMETIC_BASE(t),a(&n),b(&m),
            a_nested(true),b_nested(true),
            auto_free(false)
        {
        }

        N result()const
        {
            switch(this->type)
            {
            case typen::addition:
                if(a_nested and b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() + static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(a_nested and !b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() + static_cast<numeric<M,T>*>(b)->data;
                }
                else if(!a_nested and b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data + static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a_nested and !b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data + static_cast<numeric<M,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
            case typen::subtraction:
                if(a_nested and b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() - static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(a_nested and !b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() - static_cast<numeric<M,T>*>(b)->data;
                }
                else if(!a_nested and b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data - static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a_nested and !b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data - static_cast<numeric<M,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
            case typen::product:
                if(a_nested and b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() * static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(a_nested and !b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() * static_cast<numeric<M,T>*>(b)->data;
                }
                else if(!a_nested and b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data * static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a_nested and !b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data * static_cast<numeric<M,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
            case typen::quotient:
                if(a_nested and b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() / static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(a_nested and !b_nested)
                {
                    return static_cast<arithmetic<N,M,T>*>(a)->result() / static_cast<numeric<M,T>*>(b)->data;
                }
                else if(!a_nested and b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data / static_cast<arithmetic<N,M,T>*>(b)->result();
                }
                else if(!a_nested and !b_nested)
                {
                    return static_cast<numeric<N,T>*>(a)->data / static_cast<numeric<M,T>*>(b)->data;
                }
                else
                {
                    throw exception("No se reconoce como una operacion aritmetica valida");
                }
            default:
                throw exception("No se reconoce como una operacion aritmetica valida");
            }
        }

    public:
        node<T>* a;
        node<T>* b;
        bool a_nested,b_nested;
        bool auto_free;
    };


}

#endif
