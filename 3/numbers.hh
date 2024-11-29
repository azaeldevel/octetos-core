
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
#include <variant>
#include <limits>
#include <cctype>
#include <cmath>

#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif




namespace oct::core::v3
{
    class Real;
	template<typename T> concept natural = std::same_as<T, unsigned char> || std::same_as<T, unsigned short> || std::same_as<T, unsigned int> || std::same_as<T, unsigned long> || std::same_as<T, unsigned long long> || std::same_as<T, std::size_t>;
    template<typename T> concept integer = std::same_as<T, signed char> || std::same_as<T, signed short> || std::same_as<T, signed short> || std::same_as<T, signed int> || std::same_as<T, signed long> || std::same_as<T, signed long long> || natural<T>;
    template<typename T> concept real = std::same_as<T, float> || std::same_as<T, double>  || std::same_as<T, long double> || integer<T>;
    template<typename T> concept number = real<T> || std::same_as<T, Real>;

    template<typename T> concept decimal = std::same_as<T, float> || std::same_as<T, double>  || std::same_as<T, long double>;
    template<typename T> concept index = integer<T> || requires(T v)
    {
        v >= 0;
    };


    template<typename T> struct convertion_to_real
    {
    };
    template<> struct convertion_to_real<unsigned char>
    {
        using type = float;
    };
    template<> struct convertion_to_real<signed char>
    {
        using type = float;
    };
    template<> struct convertion_to_real<unsigned short>
    {
        using type = float;
    };
    template<> struct convertion_to_real<signed short>
    {
        using type = float;
    };
    template<> struct convertion_to_real<unsigned int>
    {
        using type = float;
    };
    template<> struct convertion_to_real<signed int>
    {
        using type = float;
    };
    template<> struct convertion_to_real<unsigned long int>
    {
        using type = double;
    };
    template<> struct convertion_to_real<signed long int>
    {
        using type = double;
    };
    template<> struct convertion_to_real<unsigned long long int>
    {
        using type = long double;
    };
    template<> struct convertion_to_real<signed long long int>
    {
        using type = long double;
    };
    template<> struct convertion_to_real<float>
    {
        using type = float;
    };
    template<> struct convertion_to_real<double>
    {
        using type = double;
    };
    template<> struct convertion_to_real<long double>
    {
        using type = long double;
    };


    template<typename T> constexpr bool equal(const T& a,const T& b, const T& epsilon = std::numeric_limits<T>::epsilon())
    {
        if( a < b)
        {
            T r = b - a;
            if(r > epsilon) return false;
            //else if(r < epsilon) return false;
        }
        else if (a > b)
        {
            T r = a - b;
            if(r > epsilon) return false;
            //else if(r < epsilon) return false;
        }

        return true;
    }

    template<typename T> constexpr bool diff(const T& a,const T& b, const T& epsilon = std::numeric_limits<T>::epsilon())
    {
        if( a < b)
        {
            T r = b - a;
            if(r > epsilon) return true;
            //else if(r < epsilon) return true;
        }
        else if (a > b)
        {
            T r = a - b;
            if(r > epsilon) return true;
            //else if(r < epsilon) return true;
        }

        return false;
    }


    class Number : public std::variant<signed char,unsigned char,signed int,unsigned int,signed long,signed long long,unsigned long long,float,double,long double>
    {
    public:
        typedef std::variant<signed char,unsigned char,signed int,unsigned int,signed long,signed long long,unsigned long long,float,double,long double> BASE;
    public:
        Number() = default;
        Number(number auto const& v) : BASE(v)
        {
        }
    };


    class _Number
    {
    public:
        union types
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

        enum class selectors : char
        {
            sc,
            uc,
            ss,
            us,
            si,
            ui,
        };

    public:
        _Number() = default;
        _Number(signed char sc) : selection(selectors::sc)
        {
            type.sc = sc;
        }
        _Number(unsigned char uc) : selection(selectors::uc)
        {
            type.uc = uc;
        }
        _Number(signed short ss) : selection(selectors::ss)
        {
            type.sc = ss;
        }
        _Number(unsigned short us) : selection(selectors::us)
        {
            type.uc = us;
        }
        _Number(signed int si) : selection(selectors::si)
        {
            type.si = si;
        }
        _Number(unsigned int ui) : selection(selectors::ui)
        {
            type.ui = ui;
        }

        template <class T> T get();

    private:
        selectors selection;
        types type;
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

		if (*str == '+')
		{
			++str;
		}
		else if (*str == '-')
		{
			++str;
			//throw error
		}

		T result = 0;
		for (; std::isdigit(static_cast<unsigned char>(*str)); ++str)
		{
			T digit = *str - '0';
			result *= 10;
			result += digit;
		}

		return result;
	}




    /**
    *\brief convirte radianes a grados
    */
    template<number T>
    constexpr T radian_to_degree(T angle)
    {
        return (T(180)/std::numbers::pi) * angle;
    }

    /**
    *\brief convirte grados a radianes
    */
    template<number T>
    constexpr T degree_to_radian(T angle)
    {
        return (std::numbers::pi/T(180)) * angle;
    }

    /**
    *\brief distance entre los dos punto(mediante teorema de pitagoras)
    */
    template<number T>
    constexpr T distance(const T& x, const T& y)
    {
        return std::sqrt(std::pow(x,T(2)) + std::pow(y,T(2)));
    }
}


#endif
