
/**
 *
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
 *
 * */

#include <concepts>
#include <variant>
#include <limits>
#include <cctype>

#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

#include "numbers.hh"

namespace oct::core::v3
{

    template <> signed char _Number::get<signed char>()
    {
        return type.sc;
    }
    template <> unsigned char _Number::get<unsigned char>()
    {
        return type.uc;
    }
    template <> signed short _Number::get<signed short>()
    {
        return type.ss;
    }
    template <> unsigned short _Number::get<unsigned short>()
    {
        return type.us;
    }
    template <> signed int _Number::get<signed int>()
    {
        return type.si;
    }
    template <> unsigned int _Number::get<unsigned int>()
    {
        return type.ui;
    }
}


