
#ifndef OCTETOS_CORE_LC_SEMVER_V3_HH
#define OCTETOS_CORE_LC_SEMVER_V3_HH

#include "lexer.hh"

namespace oct::core::v3::lc
{


constexpr TT<char, Tokens, Status> creat_tt_semver()
{
	TT<char, Tokens, Status> semver(3);
	Status initial_status = 0;
	semver.initial(initial_status);
	Status number = 1;
	semver.initial(number);
	Status string = 2;
	semver.initial(string);

	semver.numbers(initial_status, Tokens::number, number);
	semver.alphabet(initial_status, Tokens::string, string);

	semver.numbers(number, Tokens::number, number);

	semver.numbers(string, Tokens::string, string);
	semver.alphabet(string, Tokens::string, string);

	return semver;
}

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
