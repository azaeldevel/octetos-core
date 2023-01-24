
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


}

#endif
