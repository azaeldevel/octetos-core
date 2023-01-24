
#ifndef OCTETOS_CORE_LC_SEMVER_V3_HH
#define OCTETOS_CORE_LC_SEMVER_V3_HH

#include "lexer.hh"

namespace oct::core::v3::lc
{


template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/,typename TT_BASE/*Status*/>
class Semver_TT : public TT<Symbol,Token,Status,TT_BASE>
{
public:
	Semver_TT()
	{
		init();
	}
	void init()
	{
		Status initial_status = 0;
		TT<Symbol,Token,Status,TT_BASE>::initial(initial_status);
		Status number = 1;
		TT<Symbol,Token,Status,TT_BASE>::initial(number);
		Status string = 2;
		TT<Symbol,Token,Status,TT_BASE>::initial(string);
		
		TT<Symbol, Token, Status, TT_BASE>::digits(initial_status,number,Tokens::number);
		TT<Symbol, Token, Status, TT_BASE>::letters(initial_status, string, Tokens::string);

		TT<Symbol, Token, Status, TT_BASE>::digits(number, number, Tokens::number);

		TT<Symbol, Token, Status, TT_BASE>::digits(string, string, Tokens::string);
		TT<Symbol, Token, Status, TT_BASE>::letters(string, string, Tokens::string);


	}

private:

};


}

#endif
