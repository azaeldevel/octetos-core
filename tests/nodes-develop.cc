#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <chrono>

#include "../3/nodes.hh"

namespace core = oct::core::v3;

    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class Number : public core::node<T>
    {
    private:
        T number;
    public:
        Number() = default;
        Number(const T& n) : number(n)
        {
        }
        virtual ~Number() = default;

        virtual operator T() const
        {
            return number;
        }
        Number& operator =(const T& n)
        {
            number = n;
            return *this;
        }
    };


    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class operation : public core::Node<T>
    {
    private:
        typedef core::Node<T> BASE;

    public:
        operation() = default;
        operation(core::node<T>& a,core::node<T>& b) : BASE(2)
        {
            BASE::at(0) = &a;
            BASE::at(1) = &b;
        }
        virtual ~operation() = default;
        void set(core::node<T>& a,core::node<T>& b)
        {
            if(BASE::size() != 2) BASE::resize(2);
            BASE::at(0) = &a;
            BASE::at(1) = &b;
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class Addition : public operation<T>
    {
    private:
        typedef operation<T> BASE;

    public:
        Addition() = default;
        Addition(core::node<T>& a,core::node<T>& b) : BASE(a,b)
        {
        }
        virtual ~Addition() = default;

        virtual operator T() const
        {
            return T(*BASE::at(0)) + T(*BASE::at(1));
        }

    };

    /**
    *\brief Representa el nodo de un arbol
    *\param T data type
    *\param S Selector de clase
    **/
    template<class T> class Subtration : public operation<T>
    {
    private:
        typedef operation<T> BASE;

    public:
        Subtration() = default;
        Subtration(core::node<T>& a,core::node<T>& b) : BASE(a,b)
        {
        }
        virtual ~Subtration() = default;

        virtual operator T() const
        {
            return T(*BASE::at(0)) - T(*BASE::at(1));
        }
    };


int main(int argc, char *argv[])
{
    Number<float> num1(5.0f);
    Number<float> num2(1.9f);
    Number<float> num3(3.9f);
    Addition<float> op1(num1,num2);
    Addition<float> op2(op1,num3);
    Subtration<float> op3(op2,num2);
    std::cout <<"Developing...\n";
    float result = op1;
    float result2 = op2;
    float result3 = op3;
    std::cout <<"Result 1 : " << result << "\n";
    std::cout <<"Result 2 : " << result2 << "\n";
    std::cout <<"Result 3 : " << result3 << "\n";


    return EXIT_SUCCESS;
}