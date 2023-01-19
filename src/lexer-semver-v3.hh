
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
		Status operators = 3;
		TT<Symbol,Token,Status,TT_BASE>::initial(operators);

		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'0',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'1',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'2',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'3',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'4',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'5',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'6',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'6',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'8',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'9',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'a',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'b',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'c',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'d',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'e',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'f',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'g',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'h',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'i',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'j',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'k',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'l',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'m',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'n',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'o',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'p',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'q',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'r',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'s',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'t',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'u',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'v',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'w',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'x',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'y',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'z',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'A',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'B',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'C',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'D',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'E',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'F',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'G',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'H',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'I',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'J',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'K',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'L',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'M',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'N',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'O',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'P',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Q',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'R',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'S',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'T',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'U',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'V',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'W',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'X',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Y',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Z',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'.',(Tokens)'.');
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'+',(Tokens)'+');
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'-',(Tokens)'-');

		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'0',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'1',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'2',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'3',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'4',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'5',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'6',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'6',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'8',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'9',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'a',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'b',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'c',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'d',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'e',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'f',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'g',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'h',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'i',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'j',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'k',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'l',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'m',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'n',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'o',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'p',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'q',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'r',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'s',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'t',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'u',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'v',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'w',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'x',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'y',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'z',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'A',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'B',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'C',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'D',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'E',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'F',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'G',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'H',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'I',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'J',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'K',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'L',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'M',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'N',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'O',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'P',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Q',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'R',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'S',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'T',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'U',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'V',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'W',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'X',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Y',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Z',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'.',(Tokens)'.');
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'+',(Tokens)'+');
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'-',(Tokens)'-');

		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'0',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'1',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'2',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'3',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'4',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'5',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'6',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'6',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'8',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'9',Tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::prefix(number,'+');
		TT<Symbol,Token,Status,TT_BASE>::prefix(number,'-');
		TT<Symbol,Token,Status,TT_BASE>::prefix(number,'.');

		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'a',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'b',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'c',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'d',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'e',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'f',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'g',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'h',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'i',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'j',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'k',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'l',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'m',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'n',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'o',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'p',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'q',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'r',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'s',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'t',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'u',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'v',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'w',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'x',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'y',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'z',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'A',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'B',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'C',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'D',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'E',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'F',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'G',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'H',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'I',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'J',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'K',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'L',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'M',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'N',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'O',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'P',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'Q',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'R',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'S',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'T',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'U',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'V',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'W',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'X',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'Y',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'Z',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'0',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'1',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'2',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'3',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'4',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'5',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'6',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'6',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'8',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'9',Tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::prefix(string,'+');
		TT<Symbol,Token,Status,TT_BASE>::prefix(string,'-');
		TT<Symbol,Token,Status,TT_BASE>::prefix(string,'.');
	}

private:

};


}

#endif
