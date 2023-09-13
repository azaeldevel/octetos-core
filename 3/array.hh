
#ifndef OCTETOS_CORE_V3_ARRAYS
#define OCTETOS_CORE_V3_ARRAYS

#include <iostream>
#include <initializer_list>
#include "numbers.hh"
#include "entity.hh"
#include "Exception.hh"

namespace oct::core::v3
{
    /**
    *\brief Representa una secuacion continua de datos, eqiuvalante al sequence
    *\param T Tipo de dato de la secuencia
    *\param S La cantidad de datos, si es 0, la asignacion es dinamica
    **/
    template<typename T,index auto S = 0,index I = size_t> class array
    {
    private:
        typedef array<T,S,I> ARRAY;

    protected:
        T data[S];

    public:
        array() = default;
        constexpr array(const T& v)
        {
            for(I i = 0; i < S; i++) data[i] = v;
        }
        /*constexpr explicit sequence(const T v[L])
        {
            for(size_t i = 0; i < L; i++) data[i] = v;
        }*/
        constexpr array(const std::initializer_list<T>& l)
        {
            //std::cout << "l.size() = " << l.size()<< "\n";
            if(l.size() < S) throw std::logic_error("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw exception("La cantidad de datos execede la capacidad del objeto");
            //static_assert(l.size() == S,"La captidad de objetos afrecido no es exacta");

            const T* c = std::data(l);
            for(I i = 0; i < S; i++)
            {
                data[i] = c[i];
            }
        }
        constexpr array(const ARRAY& s)
        {
            for(I i = 0; i < S; i++) data[i] = s.data[i];
        }

        constexpr T& operator [](I i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr const T& operator [](I i) const
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr const T& at(I i) const
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr T& at(I i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("Indice fuera de rango");
        }
        constexpr array& operator =(const ARRAY& s)
        {
            for(I i = 0; i < S; i++) data[i] = s.data[i];

            return *this;
        }
        constexpr array& operator = (const std::initializer_list<T>& l)
        {
            //std::cout << "l.size() = " << l.size()<< "\n";
            if(l.size() < S) throw std::logic_error("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw std::logic_error("La cantidad de datos execede la capacidad del objeto");

            const T* c = std::data(l);
            for(I i = 0; i < S; i++)
            {
                data[i] = c[i];
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


        constexpr I size() const
        {
            return S;
        }

        template<index auto b ,index auto s> constexpr const array<T,s,I>& sub() const
        {
            static_assert(b + s >= S,"Fuera de rango, b + s < S");

            const T* a = (const T*)this;
            a += b;

            return *(const array<T,s,I>*)s;
        }



#ifdef OCTETOS_CORE_V3_TDD
        void print(std::ostream& out, bool delim = false) const
        {
            if(delim) out << "(";
                for(I i = 0; i < S; i++)
                {
                    if(i > 0) out << ",";
                    out << data[i];
                }
            if(delim) out << ")";
        }
        void printLn(std::ostream& out, bool delim = false) const
        {
            if(delim) out << "(";
                for(I i = 0; i < S; i++)
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
    template<typename T> class array<T,0,size_t>
    {
    protected:
        size_t S;
        T* data;
        //bool free;

    public:
        array() : S(0),data(NULL)
        {
        }
        array(size_t s, const T& v) : S(s)
        {
            data = new T[S];
            for(size_t i = 0; i < S; i++) data[i] = v;
        }
        array(size_t s, T* v) : S(s)
        {
            data = new T[S];
            for(size_t i = 0; i < S; i++) data[i] = v[i];
        }
        /*constexpr explicit sequence(const T v[L])
        {
            for(size_t i = 0; i < L; i++) data[i] = v;
        }*/
        array(const std::initializer_list<T>& l) : S(l.size()),data(new T[S])
        {
            if(l.size() < S) throw exception("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw exception("La cantidad de datos exeede la capacidad del objeto");

            const T* c = std::data(l);
            for(size_t i = 0; i < l.size(); i++)
            {
                data[i] = c[i];
            }
        }
        array(const array& s)  : S(s.S)
        {
            data = new T[S];
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];
        }
        array(array&& s)  : S(s.S)
        {
            data = s.data;
            s.data = NULL;
        }
        ~array()
        {
            if(data)
            {
                delete[] data;
                data = NULL;
            }
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
            S = s.S;
            data = new T[S];
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];

            return *this;
        }
        array& operator = (std::initializer_list<T> l)
        {
            S = l.size();

            if(data) delete[] data;
            data = new T[S];
            const T* c = std::data(l);
            for(size_t i = 0; i < l.size(); i++)
            {
                data[i] = c[i];
            }

            return *this;
        }

        operator T*()
        {
            return data;
        }
        operator const T*() const
        {
            return data;
        }
        operator void*()
        {
            return data;
        }
        operator const void*() const
        {
            return data;
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

