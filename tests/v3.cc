

#include "v3.hh"

#if defined(__linux__)
    #include <Exception-v3.hh>
    #include <Version-v3.hh>
    #include <string.h>
    #include <iostream>
	#include "dfa-semver-v3.hh"
#elif defined(_WIN32) || defined(_WIN64)
    #include <core/src/Exception-v3.hh>
    #include <core/src/Version-v3.hh>

    #include <string.h>
#else
	#error "Plataforma desconocida"
#endif


using namespace oct::core::v3;

int v3_init(void)
{
	return 0;
}

int v3_clean(void)
{
	return 0;
}


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
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}

void v3_lc_innier_semver()
{
	const char* input = "269.56.9-alpha+archlinux";
	
	lc::TT<char,lc::tokens,lc::Status> semver_tt;
	lc::Status initial_status = semver_tt.add_status();
	semver_tt.initial(initial_status);	
	lc::Status number = semver_tt.add_status();
	semver_tt.initial(number);
	lc::Status string = semver_tt.add_status();
	semver_tt.initial(string);
	lc::Status operators = semver_tt.add_status();
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

	oct::core::v3::lc::tokens semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
	//semver_lex3.echo(false);
#endif
	CU_ASSERT(semver_lex3.is_accepted());
}
void v3_lc_semver()
{
	const char* input1 = "269.56.9-alpha+archlinux";
	oct::core::v3::lc::Semver_TT<char,oct::core::v3::lc::tokens,oct::core::v3::lc::Status> semver_tt_1;

	oct::core::v3::lc::Buffer semver_buff1(input1);
	oct::core::v3::lc::A<char,oct::core::v3::lc::tokens,oct::core::v3::lc::Status> semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	oct::core::v3::lc::tokens semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
	//semver_lex3.echo(false);
#endif
	CU_ASSERT(semver_lex1.is_accepted());
}
void v3_lc_semver2()
{
	const char* input1 = "269.5-alpha+archlinux";
	oct::core::v3::lc::Semver_TT<char,oct::core::v3::lc::tokens,oct::core::v3::lc::Status> semver_tt_1;

	oct::core::v3::lc::Buffer semver_buff1(input1);
	oct::core::v3::lc::A<char,oct::core::v3::lc::tokens,oct::core::v3::lc::Status> semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	oct::core::v3::lc::tokens semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
	//semver_lex3.echo(false);
#endif
	CU_ASSERT(semver_lex1.is_accepted());
}
void v3_lc_semver_rejects()
{
	const char* input1 = "2s9.5-alpha+archlinux";
	lc::Semver_TT<char,lc::tokens,lc::Status> semver_tt_1;

	lc::Buffer semver_buff1(input1);
	lc::A<char,lc::tokens,lc::Status> semver_lex1(semver_tt_1,semver_buff1);
	semver_lex1.echo(true);
	lc::tokens semver_tk1 = semver_lex1.next();
	/*CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == oct::core::v3::lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
	//semver_lex3.echo(false);
#endif
	CU_ASSERT(semver_lex1.is_accepted());*/
}

void v3_developing()
{
	
}

void v3_reduced_parser()
{
	try
	{
		throw oct::core::v3::Exception("0123456789");
	}
	catch(const Exception& ex)
	{
		CU_ASSERT(ex.code() == 0);
		//std::cout << "Error : " << ex.what() << "\n";
	}
	try
	{
		throw oct::core::v3::Exception("0123456789",__FILE__,__LINE__);
	}
	catch(const Exception& ex)
	{
		//std::cout << "Error : " << ex.describe() << "\n";
		CU_ASSERT(ex.code() == 0);
	}	
	try
	{
		throw oct::core::v3::Exception(1,__FILE__,__LINE__);
	}
	catch(const Exception& ex)
	{
		//std::cout << ex.describe() << "\n";
		CU_ASSERT(ex.code() == 1);
	}

	
	Semver ver15;
	CU_ASSERT(ver15.parse("5.30"));
	CU_ASSERT(ver15.get_major() == 5);
	CU_ASSERT(ver15.get_minor() == 30);
	
	Semver ver16;
	CU_ASSERT(ver16.parse("5.30-alpha"));
	CU_ASSERT(ver16.get_major() == 5);
	CU_ASSERT(ver16.get_minor() == 30);
	//std::cout << "str : " << ver16.get_stage() << "\n";
	CU_ASSERT(strcmp(ver16.get_stage(),"alpha") == 0);

	Semver ver17;
	CU_ASSERT(ver17.parse("5.30-alpha+mountain"));
	CU_ASSERT(ver17.get_major() == 5);
	CU_ASSERT(ver17.get_minor() == 30);
	std::cout << "str version : " << ver17.get_stage() << "\n";
	CU_ASSERT(strcmp(ver17.get_stage(),"alpha") == 0);
	//std::cout << "str : " << ver17.getBuild() << "\n";
	CU_ASSERT(strcmp(ver17.get_build(), "mountain") == 0);

	Semver ver18;
	CU_ASSERT(ver18.parse("5.30+mountain"));
	CU_ASSERT(ver18.get_major() == 5);
	CU_ASSERT(ver18.get_minor() == 30);
	//CU_ASSERT(strcmp(ver18.getBuild(), "mountain") == 0);	

	Semver ver19("4.25-alpha");
	CU_ASSERT(ver18 > ver19);
	CU_ASSERT(ver19 < ver18);	
}
