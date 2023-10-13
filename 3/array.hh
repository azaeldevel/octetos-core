
#ifndef OCTETOS_CORE_V3_ARRAYS
#define OCTETOS_CORE_V3_ARRAYS

#include <iostream>
#include <initializer_list>
#include "numbers.hh"
#include "entity.hh"
#include "Exception.hh"
#include <memory>

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
        T data[S];
#pragma GCC diagnostic pop

    public:
        using Index = I;
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
            if(l.size() > S) throw std::logic_error("La cantidad de datos execede la capacidad del objeto");
            //static_assert(l.size() == S,"La cantiad de datos afrecidos no es exacto");

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
            static_assert(b + s < S,"Fuera de rango, b + s < S");
            const T* a = (const T*)this;
            a += b;
            return *(const array<T,s,I>*)a;
        }

        T* begin()
        {
            return data;
        }
        const T* begin() const
        {
            return data;
        }

        T* end()
        {
            return data + S;
        }
        const T* end() const
        {
            return data + S;
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
    private:
        typedef array<T,0,size_t> ARRAY;
    protected:
        size_t S;
        T* data;
        //bool free;

    public:
        using Index = size_t;

    public:
        array() : S(0),data(NULL)
        {
        }
        /*array(size_t s, const T& v) : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = v;
        }*/
        array(Index s) : S(s),data(new T[S])
        {
        }
        /*array(size_t s, const T* v) : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = v[i];
        }*/
        array(size_t s, T const* v) : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = v[i];
        }
        /*constexpr explicit sequence(const T v[L])
        {
            for(size_t i = 0; i < L; i++) data[i] = v;
        }*/
        array(const std::initializer_list<T>& l) : S(l.size()),data(new T[S])
        {
            //if(l.size() < S) throw exception("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            //if(l.size() > S) throw exception("La cantidad de datos exeede la capacidad del objeto");

            const T* c = std::data(l);
            for(size_t i = 0; i < l.size(); i++)
            {
                data[i] = c[i];
            }
        }
        array(const ARRAY& s)  : S(s.S),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];
        }
        array(ARRAY&& s)  : S(s.S)
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

            throw std::out_of_range("El indice " + std::to_string(i) + ", esta fuera del rango");
        }
        T& at(size_t i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("El indice " + std::to_string(i) + ", esta fuera del rango");
        }
        array& operator =(const ARRAY& s)
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

        std::shared_ptr<ARRAY> sub(size_t b,size_t s) const
        {
            if(b + s >= S) throw exception("Fuera de rango, b + s deve ser menor que al alongitud del arreglo actual.");
            const T* a = *this;
            return std::shared_ptr<ARRAY>(new ARRAY(s,a + b));
        }


        T* begin()
        {
            return data;
        }
        const T* begin() const
        {
            return data;
        }

        T* end()
        {
            return data + S;
        }
        const T* end() const
        {
            return data + S;
        }
        void resize(size_t s)
        {
            if(data) delete[] data;
            S = s;
            data = new T[S];
        }


#ifdef OCTETOS_CORE_V3_TDD
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

