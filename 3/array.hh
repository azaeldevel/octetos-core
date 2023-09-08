
#ifndef OCTETOS_CORE_V3_ARRAYS
#define OCTETOS_CORE_V3_ARRAYS

#include <iostream>
#include <initializer_list>
#include "entity.hh"
#include "Exception.hh"

namespace oct::core::v3
{
    /**
    *\brief Representa una secuacion continua de datos, eqiuvalante al sequence
    *\param T Tipo de dato de la secuencia
    *\param S La cantidad de datos, si es 0, la asignacion es dinamica
    **/
    template<typename T,size_t S> class array
    {
    protected:
        T data[S];

    public:
        array() = default;
        constexpr array(const T& v)
        {
            for(size_t i = 0; i < S; i++) data[i] = v;
        }
        /*constexpr explicit sequence(const T v[L])
        {
            for(size_t i = 0; i < L; i++) data[i] = v;
        }*/
        constexpr array(const std::initializer_list<T>& l)
        {
            if(l.size() < S) throw std::logic_error("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw std::logic_error("La cantidad de datos execede la capacidad del objeto");

            const T* c = std::data(l);
            for(size_t i = 0; i < l.size(); i++)
            {
                data[i] = c[i];
            }
        }
        constexpr array(const array& s)
        {
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];
        }

        constexpr T& operator [](size_t i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr const T& operator [](size_t i) const
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr const T& at(size_t i) const
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr T& at(size_t i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr array& operator =(const array& s)
        {
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];

            return *this;
        }
        constexpr array& operator = (std::initializer_list<T> l)
        {
            if(l.size() < S) throw std::logic_error("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw std::logic_error("La cantidad de datos execede la capacidad del objeto");

            unsigned char i = 0;
            for(const T& c : l)
            {
                data[i] = c;
                i++;
            }

            return *this;
        }

        constexpr operator T*()
        {
            return data;
        }
        constexpr operator const T*() const
        {
            return data;
        }
        constexpr operator void*()
        {
            return data;
        }
        constexpr operator const void*() const
        {
            return data;
        }


        constexpr size_t size() const
        {
            return S;
        }



#ifdef OCTETOS_NUMBERS_V0_TTD
        void print(std::ostream& out, bool delim = false) const
        {
            if(delim) out << "(";
                for(size_t i = 0; i < S; i++)
                {
                    if(i > 0) out << ",";
                    out << data[i];
                }
            if(delim) out << ")";
        }
        void printLn(std::ostream& out, bool delim = false) const
        {
            if(delim) out << "(";
                for(size_t i = 0; i < S; i++)
                {
                    if(i > 0) out << ",";
                    out << data[i];
                }
            if(delim) out << ")";
            out << "\n";
        }

#endif // OCTETOS_AVERSO_TTD

    private:

    };


    /**
    *\brief Representa una secuacion continua de datos, eqiuvalante al sequence
    *\param T Tipo de dato de la secuencia
    *\param L 0 para que la asignacion sea dinamica
    **/
    template<typename T> class array<T,0>
    {
    protected:
        size_t S;
        T* data;
        bool free;

    public:
        array() = default;
        array(size_t s, const T& v) : S(s),free(true)
        {
            data = new T[S];
            for(size_t i = 0; i < S; i++) data[i] = v;
        }
        array(size_t s, T* v) : S(s),free(false)
        {
            data = v;
        }
        /*constexpr explicit sequence(const T v[L])
        {
            for(size_t i = 0; i < L; i++) data[i] = v;
        }*/
        array(const std::initializer_list<T>& l) : S(l.S),free(true)
        {
            if(l.size() < S) throw std::logic_error("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw std::logic_error("La cantidad de datos execede la capacidad del objeto");

            data = new T[S];
            const T* c = std::data(l);
            for(size_t i = 0; i < l.size(); i++)
            {
                data[i] = c[i];
            }
        }
        array(const array& s)  : S(s.S),free(true)
        {
            data = new T[S];
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];
        }
        ~array()
        {
            if(free) delete[] data;
        }

        T& operator [](size_t i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("La cantidad de datos execede la capacidad del objeto");
        }
        const T& operator [](size_t i) const
        {
            if(i < S) return data[i];

            throw std::out_of_range("La cantidad de datos execede la capacidad del objeto");
        }
        const T& at(size_t i) const
        {
            if(i < S) return data[i];

            throw std::out_of_range("La cantidad de datos execede la capacidad del objeto");
        }
        T& at(size_t i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("La cantidad de datos execede la capacidad del objeto");
        }
        array& operator =(const array& s)
        {
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];

            return *this;
        }
        array& operator = (std::initializer_list<T> l)
        {
            if(l.size() < S) throw std::logic_error("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw std::logic_error("La cantidad de datos execede la capacidad del objeto");

            unsigned char i = 0;
            for(const T& c : l)
            {
                data[i] = c;
                i++;
            }

            return *this;
        }


        size_t size() const
        {
            return S;
        }



#ifdef OCTETOS_OCTETOS_V3_TDD
        void print(std::ostream& out, bool delim = false) const
        {
            if(delim) out << "(";
                for(size_t i = 0; i < S; i++)
                {
                    if(i > 0) out << ",";
                    out << data[i];
                }
            if(delim) out << ")";
        }
        void printLn(std::ostream& out, bool delim = false) const
        {
            if(delim) out << "(";
                for(size_t i = 0; i < S; i++)
                {
                    if(i > 0) out << ",";
                    out << data[i];
                }
            if(delim) out << ")";
            out << "\n";
        }

#endif // OCTETOS_AVERSO_TTD

    private:

    };

}


#endif

