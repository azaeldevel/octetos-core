
#ifndef OCTETOS_CORE_V3_ARRAYS
#define OCTETOS_CORE_V3_ARRAYS

#include <iostream>
#include <initializer_list>
#include "numbers.hh"
#include "entity.hh"
//#include "Exception.hh"
#include <memory>
#include <string>

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
#ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wpedantic"
#endif
        T data[S];
#ifdef __GNUC__
    #pragma GCC diagnostic pop
#endif
    public:
        using Index = I;
        array() = default;
        constexpr array(const T& v)
        {
            for(I i = 0; i < S; i++) data[i] = v;
        }
        constexpr array(const T& v1,const T& v2)
        {
            data[0] = v1;
            data[1] = v2;
        }
        constexpr array(const T& v1,const T& v2,const T& v3)
        {
            data[0] = v1;
            data[1] = v2;
            data[2] = v3;
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
        T& front()
        {
            return data[0];
        }
        T& back()
        {
            return data[S - 1];
        }
        const T& front() const
        {
            return data[0];
        }
        const T& back() const
        {
            return data[S - 1];
        }

        /*template<size_t s> array<T,S + s> push_back(const array<T,s>& a)
        {
            array<T,S + s> newa;
            size_t i = 0;
            for(;i < S; i++)
            {
                newa[i] = data[i];
            }
            for(size_t j = 0;j < s; j++)
            {
                newa[i + j] = a[j];
            }
        }*/

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
    *\brief Representa una secuencia continua de datos
    *\param T Tipo de dato de la secuencia
    *\param L 0 para que la asignacion sea dinamica
    **/
    template<typename T> class array<T,0>
    {
    private:
        typedef array<T,0> ARRAY;
    protected:
        size_t S;
        T* data;
        //bool free;

    public:
        //using Index = size_t;

    public:
        array() : S(0),data(NULL)
        {
        }
        /*array(size_t s, const T& v) : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = v;
        }*/
        array(size_t s) : S(s),data(new T[S])
        {
        }
        /*array(size_t s, const T* v) : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = v[i];
        }*/
        array(T const* v,size_t s) : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = v[i];
        }
        array(T* v,size_t s) : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = v[i];
        }
        /*constexpr explicit sequence(const T v[L])
        {
            for(size_t i = 0; i < L; i++) data[i] = v;
        }*/
        array(const std::initializer_list<T>& l) : S(l.size()),data(new T[S])
        {
            if(l.size() < S) throw std::domain_error("La cantidad de datos indicados no es suficuente para inicializar el objeto");
            if(l.size() > S) throw std::domain_error("La cantidad de datos exeede la capacidad del objeto");

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
        array(const T& d)  : S(1),data(new T[S])
        {
            data[0] = d;
        }
        array(const T& d1,const T& d2)  : S(2),data(new T[S])
        {
            data[0] = d1;
            data[1] = d2;
        }
        array(const T& d1,const T& d2,const T& d3)  : S(3),data(new T[S])
        {
            data[0] = d1;
            data[1] = d2;
            data[2] = d3;
        }
        /*template<size_t s> array(const array<T,s>& a)  : S(s),data(new T[S])
        {
            for(size_t i = 0; i < S; i++) data[i] = a.data[i];
        }*/
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
            return data[i];
            //throw std::out_of_range("El indice " + std::to_string(i) + ", esta fuera del rango " + std::to_string(S));
        }
        const T& operator [](size_t i) const
        {
           return data[i];
        //throw std::out_of_range("El indice " + std::to_string(i) + ", esta fuera del rango " + std::to_string(S));
        }
        const T& at(size_t i) const
        {
            if(i < S) return data[i];

            throw std::out_of_range("El indice " + std::to_string(i) + ", esta fuera del rango " + std::to_string(S));
        }
        T& at(size_t i)
        {
            if(i < S) return data[i];

            throw std::out_of_range("El indice " + std::to_string(i) + ", esta fuera del rango " + std::to_string(S));
        }
        array& operator =(const ARRAY& s)
        {
            S = s.S;
            data = new T[S];
            for(size_t i = 0; i < S; i++) data[i] = s.data[i];

            return *this;
        }
        array& operator = (const std::initializer_list<T>& l)
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
            if(b + s >= S) throw std::domain_error("Fuera de rango, b + s deve ser menor que al alongitud del arreglo actual.");
            const T* a = *this;
            return std::shared_ptr<ARRAY>(new ARRAY(a + b,s));
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
            T* new_data = new T[S + s];
            size_t i = 0;
            for(;i < S; i++)
            {
                new_data[i] = data[i];
            }

            T* old_data = data;
            data = new_data;
            S = S + s;
            delete[] old_data;
        }
        T& front()
        {
            return data[0];
        }
        T& back()
        {
            return data[S - 1];
        }
        const T& front() const
        {
            return data[0];
        }
        const T& back() const
        {
            return data[S - 1];
        }


        void push_back(const array& a)
        {
            T* new_data = new T[S + a.S];
            size_t i = 0;
            for(;i < S; i++)
            {
                new_data[i] = data[i];
            }
            for(size_t j = 0;j < a.S; j++)
            {
                new_data[i + j] = a[j];
            }

            T* old_data = data;
            data = new_data;
            S = S + a.S;
            delete[] old_data;
        }
        void push_back(const T& a)
        {
            size_t s = S + 1;
            T* new_data = new T[s];
            size_t i = 0;
            for(;i < S; i++)
            {
                new_data[i] = data[i];
            }
            new_data[i] = a;

            T* old_data = data;
            data = new_data;
            S = s;
            delete[] old_data;
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

