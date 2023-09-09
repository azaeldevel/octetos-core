

#include "v3.hh"

#include <string.h>
#include <iostream>
#include <array>
#include <core/3/Lexer-TTA.hh>
#include <core/3/Semver.hh>
#if defined(__linux__)
    //#include <src/Exception-v3.hh>
    //#include <src/Version-v3.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <core/src/Exception-v3.hh>
    //#include <core/src/Version-v3.hh>
#else
	#error "Plataforma desconocida"
#endif


using namespace oct::core::v3;


void print(Semver::Tokens tk,const char* input)
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
	case Semver::Tokens::none:
		std::cout << "None";
		break;
	case Semver::Tokens::number:
		std::cout << "Number";
		break;
	case Semver::Tokens::dot:
		std::cout << "dot";
		break;
	case Semver::Tokens::minus:
		std::cout << "minus";
		break;
	case Semver::Tokens::plus:
		std::cout << "plus";
		break;
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}

void v3_lc_innier_semver()
{
    const std::vector<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
	const char* input = "269.56.9-alpha+archlinux";
	//typedef std::array<std::array<lex::Transition<lex::Tokens,lex::State>,lex::MAX_SIMBOLS>,4> TT_BASE;
	lex::TTA<char,Semver::Tokens,lex::State> semver_tt;
	/*lex::State initial = 0;
	semver_tt.initial(initial);
	lex::State number = 1;
	semver_tt.initial(number);
	lex::State string = 2;
	semver_tt.initial(string);
	lex::State operators = 3;
	semver_tt.initial(operators);*/

	semver_tt.acceptable(initial_status,'0',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'1',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'2',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'3',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'4',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'5',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'6',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'6',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'8',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'9',Semver::Tokens::number,number);
	semver_tt.acceptable(initial_status,'a',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'b',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'c',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'d',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'e',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'f',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'g',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'h',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'i',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'j',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'k',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'l',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'m',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'n',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'o',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'p',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'q',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'r',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'s',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'t',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'u',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'v',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'w',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'x',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'y',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'z',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'A',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'B',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'C',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'D',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'E',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'F',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'G',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'H',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'I',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'J',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'K',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'L',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'M',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'N',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'O',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'P',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'Q',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'R',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'S',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'T',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'U',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'V',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'W',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'X',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'Y',Semver::Tokens::string,string);
	semver_tt.acceptable(initial_status,'Z',Semver::Tokens::string,string);
	semver_tt.accept(initial_status,'.',(Semver::Tokens)'.');
	semver_tt.accept(initial_status,'+',(Semver::Tokens)'+');
	semver_tt.accept(initial_status,'-',(Semver::Tokens)'-');

	semver_tt.acceptable(number,'0',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'1',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'2',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'3',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'4',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'5',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'6',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'6',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'8',Semver::Tokens::number,number);
	semver_tt.acceptable(number,'9',Semver::Tokens::number,number);
	semver_tt.prefix(number,'+',0);
	semver_tt.prefix(number,'-',0);
	semver_tt.prefix(number,'.',0);

	semver_tt.acceptable(string,'a',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'b',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'c',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'d',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'e',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'f',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'g',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'h',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'i',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'j',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'k',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'l',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'m',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'n',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'o',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'p',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'q',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'r',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'s',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'t',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'u',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'v',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'w',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'x',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'y',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'z',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'A',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'B',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'C',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'D',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'E',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'F',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'G',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'H',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'I',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'J',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'K',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'L',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'M',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'N',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'O',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'P',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'Q',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'R',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'S',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'T',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'U',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'V',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'W',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'X',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'Y',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'Z',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'0',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'1',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'2',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'3',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'4',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'5',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'6',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'6',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'8',Semver::Tokens::string,string);
	semver_tt.acceptable(string,'9',Semver::Tokens::string,string);
	semver_tt.prefix(string,'+',0);
	semver_tt.prefix(string,'-',0);
	semver_tt.prefix(string,'.',0);

	//const char* input3 = "23";
	Buffer semver_buff3(input);
	lex::A<char,lex::Tokens,lex::Status,TT_BASE> semver_lex3(semver_tt,semver_buff3);

	lex::Tokens semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::number);
	print(semver_tk3,input);
	std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex3.is_accepted());

	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == Semver::Tokens::string);
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
	typedef std::array<std::array<lex::Transition<lex::Tokens,lex::Status>,lex::MAX_SIMBOLS>,4> TT_BASE;
	lex::Semver_TT<char,lex::Tokens,lex::Status,TT_BASE> semver_tt_1;

	Buffer semver_buff1(input1);
	lex::A<char,lex::Tokens,lex::Status,TT_BASE> semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	lex::Tokens semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::string);
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
	typedef std::array<std::array<lex::Transition<lex::Tokens,lex::Status>,lex::MAX_SIMBOLS>,4> TT_BASE;
	lex::Semver_TT<char,lex::Tokens,lex::Status,TT_BASE> semver_tt_1;

	Buffer semver_buff1(input1);
	lex::A<char,lex::Tokens,lex::Status,TT_BASE> semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	lex::Tokens semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::string);
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
	typedef std::array<std::array<lex::Transition<lex::Tokens,lex::Status>,lex::MAX_SIMBOLS>,4> TT_BASE;
	lex::Semver_TT<char,lex::Tokens,lex::Status,TT_BASE> semver_tt_1;

	Buffer semver_buff1(input1);
	lex::A<char,lex::Tokens,lex::Status,TT_BASE> semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	lex::Tokens semver_tk1 = semver_lex1.next();
	/*CU_ASSERT(semver_tk1 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
#endif
	CU_ASSERT(semver_lex1.is_accepted());

	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == Semver::Tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";
	//semver_lex3.echo(false);
#endif
	CU_ASSERT(semver_lex1.is_accepted());*/
}

void v3_reduced_parser()
{
	/*try
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
	CU_ASSERT(ver19 < ver18);*/
}
