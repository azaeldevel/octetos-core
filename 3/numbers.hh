
#ifndef OCTETOS_CORE_V3_NUMBERS_HH
#define OCTETOS_CORE_V3_NUMBERS_HH

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
#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif


namespace oct::core::v3
{
	template<typename T> concept natural = std::same_as<T, unsigned char> || std::same_as<T, unsigned short> || std::same_as<T, unsigned int> || std::same_as<T, unsigned long> || std::same_as<T, unsigned long long> || std::same_as<T, size_t>;
    template<typename T> concept integer = std::same_as<T, signed char> || std::same_as<T, signed short> || std::same_as<T, signed short> || std::same_as<T, signed int> || std::same_as<T, signed long> || std::same_as<T, signed long long> || natural<T>;
    template<typename T> concept real = std::same_as<T, float> || std::same_as<T, double>  || std::same_as<T, long double> || integer<T>;
    template<typename T> concept number = real<T>;


}


#endif
