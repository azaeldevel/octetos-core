

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

namespace oct::core::v3
{

    class Entity
    {

    };


	//https://en.cppreference.com/w/cpp/string/byte/atoi
	/**
	*\brief Convierte el string dao en el intero indicado
	*/
	template<std::signed_integral T, typename C> T to_number(const C* str)
	{
		while (std::isspace(static_cast<unsigned char>(*str)))
		{
			++str;
		}

		bool negative = false;

		if (*str == '+')
		{
			++str;
		}
		else if (*str == '-')
		{
			++str;
			negative = true;
		}

		T result = 0;
		for (; std::isdigit(static_cast<unsigned char>(*str)); ++str)
		{
			T digit = *str - '0';
			result *= 10;
			result -= digit; // calculate in negatives to support INT_MIN, LONG_MIN,..
		}

		return negative ? result : -result;
	}
	/**
	*\brief Convierte el string dao en el intero indicado
	*/
	template<std::unsigned_integral T, typename C> T to_number(const C* str)
	{
		while (std::isspace(static_cast<unsigned char>(*str)))
		{
			++str;
		}

		bool negative = false;

		if (*str == '+')
		{
			++str;
		}
		else if (*str == '-')
		{
			++str;
			negative = true;
			//throw error
		}

		T result = 0;
		for (; std::isdigit(static_cast<unsigned char>(*str)); ++str)
		{
			T digit = *str - '0';
			result *= 10;
			result -= digit; // calculate in negatives to support INT_MIN, LONG_MIN,..
		}

		return result;
	}

}

#endif
