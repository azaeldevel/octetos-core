
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

    template<typename T> concept decimal = std::same_as<T, float> || std::same_as<T, double>  || std::same_as<T, long double>;
    template<typename T> concept index = integer<T> || requires(T v)
    {
        v >= 0;
    };


    template<typename T> struct convertion
    {
    };
    template<> struct convertion<unsigned char>
    {
        using type = float;
    };
    template<> struct convertion<signed char>
    {
        using type = float;
    };
    template<> struct convertion<unsigned short>
    {
        using type = float;
    };
    template<> struct convertion<signed short>
    {
        using type = float;
    };
    template<> struct convertion<unsigned int>
    {
        using type = float;
    };
    template<> struct convertion<signed int>
    {
        using type = float;
    };
    template<> struct convertion<unsigned long int>
    {
        using type = double;
    };
    template<> struct convertion<signed long int>
    {
        using type = double;
    };
    template<> struct convertion<unsigned long long int>
    {
        using type = long double;
    };
    template<> struct convertion<signed long long int>
    {
        using type = long double;
    };
    template<> struct convertion<float>
    {
        using type = float;
    };
    template<> struct convertion<double>
    {
        using type = double;
    };
    template<> struct convertion<long double>
    {
        using type = long double;
    };



    /*template<decimal T> bool equal(const T& a,const T& b)
    {
        //if(std::numeric_limits<T>::epsilon() + a > b and std::numeric_limits<T>::epsilon() - a < b) return true;
        T r = a - b;
        if(r > 0)
        {
            if(r > std::numeric_limits<T>::epsilon()) return false;
        }
        else if(r < 0)
        {
            if(r < std::numeric_limits<T>::epsilon()) return false;
        }

        return true;
    }*/
    template<typename T> bool equal(const T& a,const T& b, const T& epsilon = std::numeric_limits<T>::epsilon())
    {
        //if(std::numeric_limits<T>::epsilon() + a > b and std::numeric_limits<T>::epsilon() - a < b) return true;
        T r = a - b;
        //std::cout << "a : " << a << ", b : " << b << ", r : " << r << "\n";
        if(r > 0)
        {
            if(r > epsilon) return false;
        }
        else if(r < 0)
        {
            if(r < -epsilon) return false;
        }

        return true;
    }

    class Real : public std::variant<signed char,unsigned char,signed int,unsigned int,signed long,signed long long,unsigned long long,float,double,long double>
    {
    public:
        typedef std::variant<signed char,unsigned char,signed int,unsigned int,signed long,signed long long,unsigned long long,float,double,long double> BASE;
    public:
        Real() = default;
        Real(real auto const& v) : BASE(v)
        {
        }
        Real(real auto&& v) : BASE(v)
        {
        }

        template<real t> operator t()
        {
            return std::get<t>(*this);
        }
        template<real t> operator t const&() const
        {
            return std::get<t>(*this);
        }
    };
}


#endif
