
/*
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 *
 * CC is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CC is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "nodes.hh"



namespace oct::core::v3::nodes
{

    node::node() : type(Types::none)
    {
    }
    node::node(node::Types t) : type(t)
    {
    }

    node* node::is_number()
    {
        if(type == Types::number) return this;
        return NULL;
    }
    node::Types node::get_type()
    {
        return type;
    }















    Number::Number(signed char n) : Number::BASE(node::Types::number),type(Types::sc)
    {
        number.sc = n;
    }
    Number::Number(unsigned char n) : Number::BASE(node::Types::number),type(Types::uc)
    {
        number.uc = n;
    }
    Number::Number(signed short n) : Number::BASE(node::Types::number),type(Types::ss)
    {
        number.ss = n;
    }
    Number::Number(unsigned short n) : Number::BASE(node::Types::number),type(Types::us)
    {
        number.us = n;
    }
    Number::Number(signed int n) : Number::BASE(node::Types::number),type(Types::si)
    {
        number.si = n;
    }
    Number::Number(unsigned int n) : Number::BASE(node::Types::number),type(Types::ui)
    {
        number.ui = n;
    }
    Number::Number(signed long n) : Number::BASE(node::Types::number),type(Types::sl)
    {
        number.sl = n;
    }
    Number::Number(unsigned long n) : Number::BASE(node::Types::number),type(Types::ul)
    {
        number.ul = n;
    }
    Number::Number(signed long long n) : Number::BASE(node::Types::number),type(Types::sll)
    {
        number.sll = n;
    }
    Number::Number(unsigned long long n) : Number::BASE(node::Types::number),type(Types::ul)
    {
        number.ull = n;
    }
    Number::Number(float n) : Number::BASE(node::Types::number),type(Types::f)
    {
        number.f = n;
    }
    Number::Number(double n) : Number::BASE(node::Types::number),type(Types::d)
    {
        number.d = n;
    }
    Number::Number(long double n) : Number::BASE(node::Types::number),type(Types::ld)
    {
        number.ld = n;
    }


    Number* Number::is_signed_char()
    {
        if(type == Types::sc) return this;
        return NULL;
    }
    Number* Number::is_unsigned_char()
    {
        if(type == Types::uc) return this;
        return NULL;
    }
    Number* Number::is_signed_short()
    {
        if(type == Types::ss) return this;
        return NULL;
    }
    Number* Number::is_unsigned_short()
    {
        if(type == Types::us) return this;
        return NULL;
    }
    Number* Number::is_signed_int()
    {
        if(type == Types::si) return this;
        return NULL;
    }
    Number* Number::is_unsigned_int()
    {
        if(type == Types::ui) return this;
        return NULL;
    }

    void Number::print(std::ostream& out, bool delim) const
    {
        switch(type)
        {
        case Types::uc:
            out << number.uc;
            break;
        case Types::sc:
            out << number.sc;
            break;
        case Types::us:
            out << number.us;
            break;
        case Types::ss:
            out << number.ss;
            break;
        case Types::ui:
            out << number.ui;
            break;
        case Types::si:
            out << number.si;
            break;
        case Types::ul:
            out << number.ul;
            break;
        case Types::sl:
            out << number.sl;
            break;
        case Types::ull:
            out << number.ull;
            break;
        case Types::sll:
            out << number.sl;
            break;
        case Types::f:
            out << number.f;
            break;
        case Types::d:
            out << number.d;
            break;
        case Types::op:
        default:
            break;
        }
    }

}
