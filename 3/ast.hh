
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
    template<class R,class T> struct Variable;
    template<class R,class T> struct Numeric;
    template<class R,class T> struct Binopr;
    template<class R,class T> struct Nest;

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

}

#endif
