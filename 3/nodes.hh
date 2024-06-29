
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

#include "array.hh"

#ifdef OCTETOS_CORE_V3_TDD
    #include <iostream>
#endif

namespace oct::core::v3::nodes
{

    class node
    {
    public:
        enum class Types
        {
            none,
            number,
            expression,
            expression_numeric,
        };

    public:
        node();
        node(Types t);

        node* is_number();
        Types get_type();

        virtual void print(std::ostream& out) const = 0;

    private:
        Types type;
    };

    class Number : public node
    {
    public:
        enum class Types
        {
            none,
            sc,
            uc,
            ss,
            us,
            si,
            ui,
            ul,
            sl,
            ull,
            sll,
            f,
            d,
            ld,

        };
    public:
        typedef node BASE;
        union number_t
        {
            signed char sc;
            unsigned char uc;
            signed short ss;
            unsigned short us;
            signed int si;
            unsigned int ui;
            signed long sl;
            unsigned long ul;
            signed long long sll;
            unsigned long long ull;
            float f;
            double d;
            long double ld;
        };

    public:
        Number() = default;
        Number(signed char);
        Number(unsigned char);
        Number(signed short);
        Number(unsigned short);
        Number(signed int);
        Number(unsigned int);
        Number(signed long);
        Number(unsigned long);
        Number(signed long long);
        Number(unsigned long long);
        Number(float);
        Number(double);
        Number(long double);

        Number* is_signed_char();
        Number* is_unsigned_char();
        Number* is_signed_short();
        Number* is_unsigned_short();
        Number* is_signed_int();
        Number* is_unsigned_int();
        Number* is_signed_long();
        Number* is_unsigned_long();
        Number* is_signed_long_long();
        Number* is_unsigned_long_long();
        Number* is_float();
        Number* is_double();
        Number* is_long_double();
        Types get_type();

        virtual void print(std::ostream& out) const;

    private:
        Types type;
        number_t number;
    };


    class Expression : public node
    {
    public:
        Expression();
        Expression(node::Types);
    };

    /**
    *\brief Representa un expresion numerica
    */
    class Numeric : public Expression
    {


    public:
        Numeric();
        Numeric(node::Types);

    public:
    private:
    };

    /**
    *\brief Representa un operacion binaria
    */
    class Operation : public Numeric
    {
    public:
        enum class Types : char
        {
            none,
            addition = '+',
            subtraction = '-',
            product = '*',
            divition = '/',
        };

    public:
        Operation();
        Operation(Types,Number&,Number&);
        Operation(Types,Number&,Operation&);
        Operation(Types,Operation&,Number&);
        Operation(Types,Operation&,Operation&);
        Operation(char,Number&,Number&);
        Operation(char,Number&,Operation&);
        Operation(char,Operation&,Number&);
        Operation(char,Operation&,Operation&);

        virtual void print(std::ostream& out) const;
    protected:
        Types type;
        node *left,*right;
    };


}

#endif
