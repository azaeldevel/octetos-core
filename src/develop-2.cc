
#include <iostream>
#include <cstring>
#include "dfa-semver-v3.hh"


void print(oct::core::v3::lc::tokens tk,const char* input)
{
	if(input)
	{
		std::cout << "'" << input << "' -> ";
	}
	else
	{
		std::cout << "NULL -> ";
	}
	switch(tk)
	{
	case oct::core::v3::lc::tokens::none:
		std::cout << "None";
		break;
	case oct::core::v3::lc::tokens::number:
		std::cout << "Number";
		break;
	case oct::core::v3::lc::tokens::dot:
		std::cout << "dot";
		break;
	case oct::core::v3::lc::tokens::minus:
		std::cout << "minus";
		break;
	case oct::core::v3::lc::tokens::plus:
		std::cout << "plus";
		break;
	case oct::core::v3::lc::tokens::string:
		std::cout << "string";
		break;
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}
bool lexing(const char* input)
{
	std::cout << "Reading : " << input << "\n";
	
	oct::core::v3::lc::TT<char,oct::core::v3::lc::tokens,oct::core::v3::lc::Status> semver_tt;
	oct::core::v3::lc::Status initial_status = semver_tt.add_status();
	semver_tt.initial(initial_status);	
	oct::core::v3::lc::Status number = semver_tt.add_status();
	semver_tt.initial(number);
	oct::core::v3::lc::Status string = semver_tt.add_status();
	semver_tt.initial(string);
	oct::core::v3::lc::Status operators = semver_tt.add_status();
	semver_tt.initial(operators);
	
	semver_tt.acceptable(initial_status,'0',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'1',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'2',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'3',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'4',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'5',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'6',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'6',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'8',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'9',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'a',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'b',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'c',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'d',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'e',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'f',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'g',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'h',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'i',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'j',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'k',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'l',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'m',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'n',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'o',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'p',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'q',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'r',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'s',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'t',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'u',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'v',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'w',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'x',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'y',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'z',oct::core::v3::lc::tokens::string,string);	
	semver_tt.acceptable(initial_status,'A',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'B',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'C',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'D',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'E',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'F',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'G',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'H',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'I',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'J',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'K',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'L',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'M',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'N',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'O',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'P',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'Q',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'R',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'S',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'T',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'U',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'V',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'W',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'X',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'Y',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'Z',oct::core::v3::lc::tokens::string,string);
	semver_tt.accept(initial_status,'.',(oct::core::v3::lc::tokens)'.');
	semver_tt.accept(initial_status,'+',(oct::core::v3::lc::tokens)'+');
	semver_tt.accept(initial_status,'-',(oct::core::v3::lc::tokens)'-');
	
	semver_tt.acceptable(number,'0',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'1',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'2',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'3',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'4',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'5',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'6',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'6',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'8',oct::core::v3::lc::tokens::number,number);
	semver_tt.acceptable(number,'9',oct::core::v3::lc::tokens::number,number);
	semver_tt.prefix(number,'+',0);
	semver_tt.prefix(number,'-',0);
	semver_tt.prefix(number,'.',0);
	
	semver_tt.acceptable(string,'a',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'b',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'c',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'d',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'e',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'f',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'g',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'h',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'i',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'j',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'k',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'l',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'m',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'n',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'o',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'p',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'q',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'r',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'s',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'t',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'u',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'v',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'w',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'x',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'y',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'z',oct::core::v3::lc::tokens::string,string);	
	semver_tt.acceptable(string,'A',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'B',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'C',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'D',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'E',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'F',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'G',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'H',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'I',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'J',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'K',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'L',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'M',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'N',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'O',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'P',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'Q',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'R',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'S',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'T',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'U',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'V',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'W',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'X',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'Y',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'Z',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'0',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'1',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'2',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'3',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'4',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'5',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'6',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'6',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'8',oct::core::v3::lc::tokens::string,string);
	semver_tt.acceptable(string,'9',oct::core::v3::lc::tokens::string,string);
	semver_tt.prefix(string,'+',0);
	semver_tt.prefix(string,'-',0);
	semver_tt.prefix(string,'.',0);	
	
	//const char* input3 = "23";
	oct::core::v3::lc::Buffer semver_buff3(input);
	oct::core::v3::lc::A<char,oct::core::v3::lc::tokens,oct::core::v3::lc::Status> semver_lex3(semver_tt,semver_buff3);
	semver_lex3.echo(true);
	oct::core::v3::lc::tokens semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";	
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";	
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";	
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";	
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";	
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";	
	
	semver_tk3 = semver_lex3.next();
	print(semver_tk3,input);
	std::cout << "\n";	
	
	bool accepted = semver_lex3.is_accepted();
	if(accepted) std::cout << " : acceptado\n";
	else std::cout << " : rechazado\n";

	return accepted;
}

int main(int argc, char* argv[])
{	
	lexing("269.56.9-alpha+archlinux");
	
	return EXIT_SUCCESS;
}
