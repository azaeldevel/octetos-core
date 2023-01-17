
#ifndef OCTETOS_CORE_DFA_SEMVER_V3_HH
#define OCTETOS_CORE_DFA_SEMVER_V3_HH

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
			
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'0',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'1',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'2',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'3',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'4',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'5',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'6',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'6',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'8',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'9',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'a',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'b',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'c',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'d',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'e',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'f',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'g',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'h',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'i',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'j',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'k',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'l',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'m',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'n',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'o',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'p',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'q',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'r',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'s',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'t',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'u',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'v',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'w',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'x',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'y',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'z',oct::core::v3::lc::tokens::string,string);	
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'A',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'B',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'C',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'D',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'E',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'F',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'G',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'H',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'I',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'J',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'K',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'L',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'M',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'N',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'O',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'P',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Q',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'R',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'S',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'T',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'U',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'V',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'W',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'X',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Y',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(initial_status,'Z',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'.',(oct::core::v3::lc::tokens)'.');
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'+',(oct::core::v3::lc::tokens)'+');
		TT<Symbol,Token,Status,TT_BASE>::accept(initial_status,'-',(oct::core::v3::lc::tokens)'-');
		
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'0',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'1',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'2',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'3',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'4',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'5',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'6',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'6',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'8',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(number,'9',oct::core::v3::lc::tokens::number,number);
		TT<Symbol,Token,Status,TT_BASE>::prefix(number,'+',0);
		TT<Symbol,Token,Status,TT_BASE>::prefix(number,'-',0);
		TT<Symbol,Token,Status,TT_BASE>::prefix(number,'.',0);
		
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'a',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'b',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'c',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'d',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'e',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'f',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'g',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'h',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'i',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'j',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'k',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'l',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'m',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'n',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'o',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'p',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'q',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'r',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'s',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'t',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'u',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'v',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'w',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'x',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'y',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'z',oct::core::v3::lc::tokens::string,string);	
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'A',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'B',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'C',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'D',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'E',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'F',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'G',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'H',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'I',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'J',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'K',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'L',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'M',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'N',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'O',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'P',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'Q',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'R',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'S',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'T',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'U',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'V',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'W',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'X',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'Y',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'Z',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'0',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'1',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'2',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'3',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'4',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'5',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'6',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'6',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'8',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::acceptable(string,'9',oct::core::v3::lc::tokens::string,string);
		TT<Symbol,Token,Status,TT_BASE>::prefix(string,'+',0);
		TT<Symbol,Token,Status,TT_BASE>::prefix(string,'-',0);
		TT<Symbol,Token,Status,TT_BASE>::prefix(string,'.',0);
	}

private:
	
};


}

#endif