
#ifndef OCTETOS_CORE_LC_SEMVER_V3_HH
#define OCTETOS_CORE_LC_SEMVER_V3_HH

#include "lexer.hh"

namespace oct::core::v3::lc
{

template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/,typename TT_BASE/*Status*/>
class Semver_TT : public TT<Symbol,Token,Status,TT_BASE>
{
public:
	constexpr Semver_TT()
	{
		init();
	}
	constexpr void init()
	{
		Status initial_status = 0;
		TT<Symbol, Token, Status, TT_BASE>::initial(initial_status);
		Status number = 1;
		TT<Symbol, Token, Status, TT_BASE>::initial(number);
		Status string = 2;
		TT<Symbol, Token, Status, TT_BASE>::initial(string);
		
		TT<Symbol, Token, Status, TT_BASE>::numbers(initial_status,Tokens::number,number);
		TT<Symbol, Token, Status, TT_BASE>::alphabet(initial_status,Tokens::string,string);

		TT<Symbol, Token, Status, TT_BASE>::numbers(number,Tokens::number,number);

		TT<Symbol, Token, Status, TT_BASE>::numbers(string,Tokens::string, string);
		TT<Symbol, Token, Status, TT_BASE>::alphabet(string,Tokens::string, string);


	}

private:

};

template<typename Symbol /*Input*/, typename Token, typename Status/*Status*/, typename TT_BASE/*Status*/>
class Integer_TT : public TT<Symbol, Token, Status, TT_BASE>
{
public:
	constexpr Integer_TT()
	{
		init();
	}
	constexpr void init()
	{
		Status initial_status = 0;
		TT<Symbol, Token, Status, TT_BASE>::initial(initial_status);
		Status integer = 1;
		TT<Symbol, Token, Status, TT_BASE>::initial(integer);

		TT<Symbol, Token, Status, TT_BASE>::numbers(initial_status, Tokens::integer, integer);
		TT<Symbol, Token, Status, TT_BASE>::numbers(integer, Tokens::integer, integer);

	}

private:

};

template<typename Symbol /*Input*/, typename Token, typename Status/*Status*/, typename TT_BASE/*Status*/>
class Real_TT : public TT<Symbol, Token, Status, TT_BASE>
{
public:
	constexpr Real_TT()
	{
		init();
	}
	constexpr void init()
	{
		Status initial_status = 0;
		TT<Symbol, Token, Status, TT_BASE>::initial(initial_status);
		Status integer = 1;
		TT<Symbol, Token, Status, TT_BASE>::initial(integer);
		Status dot = 2;
		TT<Symbol, Token, Status, TT_BASE>::initial(dot);
		Status decimal = 2;
		TT<Symbol, Token, Status, TT_BASE>::initial(decimal);

		TT<Symbol, Token, Status, TT_BASE>::numbers(initial_status, Tokens::integer, integer);
		TT<Symbol, Token, Status, TT_BASE>::numbers(integer, Tokens::integer, integer);

		TT<Symbol, Token, Status, TT_BASE>::symbol(initial_status, Tokens('.'), dot, '.');
		TT<Symbol, Token, Status, TT_BASE>::symbol(integer, Tokens('.'), dot, '.');

		TT<Symbol, Token, Status, TT_BASE>::numbers(dot, Tokens::decimal, decimal);
		TT<Symbol, Token, Status, TT_BASE>::numbers(decimal, Tokens::decimal, decimal);


	}

private:

};


}

#endif
