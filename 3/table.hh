#ifndef OCTETOS_CORE_TABLE_HH_INCLUDED
#define OCTETOS_CORE_TABLE_HH_INCLUDED

#include "array.hh"

namespace oct::core::v3
{

    /**
    *\brief  Representa una secuencia continua de datos
    *\param T Tipo de dato de la secuencia
    **/
    template<typename T> class table : public array<T>
    {
    private:
        typedef array<T> BASE;
        constexpr static size_t factor = 2;

    protected:
        size_t max_S;

    public:
        table() : max_S(0)
        {
        }
        table(size_t s) : BASE(s)
        {
        }
        table(T const* v,size_t s) : BASE(v,s)
        {
        }
        table(T* v,size_t s) : BASE(v,s)
        {
        }
        table(const std::initializer_list<T>& l) : BASE(l)
        {
        }
        table(const BASE& s)  : BASE(s)
        {
        }
        table(BASE&& s)  : BASE::S(s.S),BASE::data(s.data)
        {
            s.data = NULL;
            s.S = 0;
        }

        ~table()
        {
        }

        void push_back(const T& a)
        {
            if(BASE::S < max_S)
            {
                BASE::data[BASE::S] = a;//there is one more element
                BASE::S++;
            }
            else
            {
                max_S = BASE::S + (BASE::S / factor) + 1;
                size_t s = BASE::S + 1;
                T* new_data = new T[max_S];
                size_t i = 0;
                for(;i < BASE::S; i++)
                {
                    new_data[i] = BASE::data[i];
                }
                new_data[i] = a;

                T* old_data = BASE::data;
                BASE::data = new_data;
                BASE::S = s;
                delete[] old_data;
            }
        }
        void push_back(const table& a)
        {
            if(BASE::S < max_S)
            {
                size_t i = BASE::S;
                for(size_t j = 0;j < a.S; j++)
                {
                    BASE::data[i + j] = a[j];
                }
                BASE::S = BASE::S + a.S;
            }
            else
            {
                max_S = BASE::S + ((BASE::S + a.S) / factor) + 1;
                T* new_data = new T[max_S];
                size_t i = 0;
                for(;i < BASE::S; i++)
                {
                    new_data[i] = BASE::data[i];
                }
                for(size_t j = 0;j < a.S; j++)
                {
                    new_data[i + j] = a[j];
                }

                T* old_data = BASE::data;
                BASE::data = new_data;
                BASE::S = BASE::S + a.S;
                delete[] old_data;
            }
        }
    };
}

#endif // OCTETOS_CORE_TABLE_HH_INCLUDED
