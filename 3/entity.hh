

#ifndef OCTETOS_CORE_V3_ENTITY_HH
#define OCTETOS_CORE_V3_ENTITY_HH

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


#include <concepts>
#include <cctype>
#include <cstddef>

#ifdef __linux__
    #ifdef LINUX_ARCH

    #elif defined LINUX_DEBIAN

    #elif defined LINUX_GENTOO

    #else
        //#error "Sistema operativo desconocido."
    #endif
#elif defined _WIN32

#elif defined _WIN64

#else
    //#error "Sistema operativo desconocido."
#endif

namespace oct::core::v3
{

    class Entity
    {

    };


    class Temporary
    {
    public:

    };

}

#endif
