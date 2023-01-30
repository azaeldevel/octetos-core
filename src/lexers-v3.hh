
#ifndef OCTETOS_CORE_LC_SEMVER_V3_HH
#define OCTETOS_CORE_LC_SEMVER_V3_HH

#include "lexer.hh"

namespace oct::core::v3::lc
{

template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/>
class Semver_TT : public TT<Symbol,Token,Status>
{
public:
	constexpr Semver_TT(size_t size) : TT<Symbol, Token, Status>(size)
	{
		init();
	}
	constexpr void init()
	{
		TT<Symbol, Token, Status>::resize(3);
		Status initial_status = 0;
		TT<Symbol, Token, Status>::initial(initial_status);
		Status number = 1;
		TT<Symbol, Token, Status>::initial(number);
		Status string = 2;
		TT<Symbol, Token, Status>::initial(string);
		
		TT<Symbol, Token, Status>::numbers(initial_status,Tokens::number,number);
		TT<Symbol, Token, Status>::alphabet(initial_status,Tokens::string,string);

		TT<Symbol, Token, Status>::numbers(number,Tokens::number,number);

		TT<Symbol, Token, Status>::numbers(string,Tokens::string, string);
		TT<Symbol, Token, Status>::alphabet(string,Tokens::string, string);


	}

private:

};

template<typename Symbol /*Input*/, typename Token, typename Status/*Status*/>
class Integer_TT : public TT<Symbol, Token, Status>
{
public:
	constexpr Integer_TT(size_t size) : TT<Symbol, Token, Status>(size)
	{
		init();
	}
	constexpr void init()
	{
		TT<Symbol, Token, Status>::resize(2);
		Status initial_status = 0;
		TT<Symbol, Token, Status>::initial(initial_status);
		Status integer = 1;
		TT<Symbol, Token, Status>::initial(integer);

		TT<Symbol, Token, Status>::numbers(initial_status, Tokens::integer, integer);
		TT<Symbol, Token, Status>::numbers(integer, Tokens::integer, integer);

	}

private:

};

template<typename Symbol /*Input*/, typename Token, typename Status/*Status*/>
class Real_TT : public TT<Symbol, Token, Status>
{
public:
	constexpr Real_TT(size_t size) : TT<Symbol, Token, Status>(size)
	{
		init();
	}
	constexpr void init()
	{
		TT<Symbol, Token, Status>::resize(3);
		Status initial_status = 0;
		TT<Symbol, Token, Status>::initial(initial_status);
		Status integer = 1;
		TT<Symbol, Token, Status>::initial(integer);
		Status dot = 2;
		TT<Symbol, Token, Status>::initial(dot);
		Status decimal = 2;
		TT<Symbol, Token, Status>::initial(decimal);

		TT<Symbol, Token, Status>::numbers(initial_status, Tokens::integer, integer);
		TT<Symbol, Token, Status>::numbers(integer, Tokens::integer, integer);

		TT<Symbol, Token, Status>::symbol(initial_status, Tokens::dot, dot, '.');
		TT<Symbol, Token, Status>::symbol(integer, Tokens::dot, dot, '.');

		TT<Symbol, Token, Status>::numbers(dot, Tokens::decimal, decimal);
		TT<Symbol, Token, Status>::numbers(decimal, Tokens::decimal, decimal);


	}

private:

};


}

#endif
