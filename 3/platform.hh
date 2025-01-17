
#ifndef OCTETOS_CORE_PLATFORM_V3_HH
#define OCTETOS_CORE_PLATFORM_V3_HH


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



#include <filesystem>

namespace oct::core::v3
{
    enum class platform_type
    {
        None,
        Linux,
        Windows,
        MSYS2,
    };

    constexpr platform_type get_platform_type()
    {
#if linux || __linux__
        return platform_type::Linux;
#elif (defined(_WIN32) || defined(_WIN64))
    #if MSYS2
        return platform_type::MSYS2;
    #else
        return platform_type::Windows;
    #endif
#else
	#error "Plataforma desconocida."
#endif
    }

    std::filesystem::path get_user_directory();
}

#endif
