

#include "v3.hh"

#if defined(__linux__)
    #include <src/Exception-v3.hh>
    #include <src/Version-v3.hh>
    #include <string.h>
    #include <iostream>
	#include <src/lexer-semver-v3.hh>
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


void print(lc::tokens tk,const char* input)
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
	case lc::tokens::none:
		std::cout << "None";
		break;
	case lc::tokens::number:
		std::cout << "Number";
		break;
	case lc::tokens::dot:
		std::cout << "dot";
		break;
	case lc::tokens::minus:
		std::cout << "minus";
		break;
	case lc::tokens::plus:
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
	typedef std::array<std::array<lc::Transition<lc::tokens,lc::Status>,lc::MAX_SIMBOLS>,4> TT_BASE;
	lc::TT<char,lc::tokens,lc::Status,TT_BASE> semver_tt;
	lc::Status initial_status = 0;
	semver_tt.initial(initial_status);	
	lc::Status number = 1;
	semver_tt.initial(number);
	lc::Status string = 2;
	semver_tt.initial(string);
	lc::Status operators = 3;
	semver_tt.initial(operators);
	
	semver_tt.acceptable(initial_status,'0',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'1',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'2',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'3',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'4',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'5',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'6',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'6',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'8',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'9',lc::tokens::number,number);
	semver_tt.acceptable(initial_status,'a',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'b',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'c',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'d',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'e',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'f',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'g',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'h',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'i',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'j',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'k',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'l',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'m',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'n',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'o',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'p',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'q',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'r',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'s',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'t',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'u',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'v',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'w',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'x',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'y',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'z',lc::tokens::string,string);	
	semver_tt.acceptable(initial_status,'A',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'B',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'C',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'D',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'E',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'F',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'G',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'H',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'I',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'J',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'K',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'L',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'M',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'N',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'O',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'P',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'Q',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'R',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'S',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'T',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'U',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'V',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'W',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'X',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'Y',lc::tokens::string,string);
	semver_tt.acceptable(initial_status,'Z',lc::tokens::string,string);
	semver_tt.accept(initial_status,'.',(lc::tokens)'.');
	semver_tt.accept(initial_status,'+',(lc::tokens)'+');
	semver_tt.accept(initial_status,'-',(lc::tokens)'-');
	
	semver_tt.acceptable(number,'0',lc::tokens::number,number);
	semver_tt.acceptable(number,'1',lc::tokens::number,number);
	semver_tt.acceptable(number,'2',lc::tokens::number,number);
	semver_tt.acceptable(number,'3',lc::tokens::number,number);
	semver_tt.acceptable(number,'4',lc::tokens::number,number);
	semver_tt.acceptable(number,'5',lc::tokens::number,number);
	semver_tt.acceptable(number,'6',lc::tokens::number,number);
	semver_tt.acceptable(number,'6',lc::tokens::number,number);
	semver_tt.acceptable(number,'8',lc::tokens::number,number);
	semver_tt.acceptable(number,'9',lc::tokens::number,number);
	semver_tt.prefix(number,'+',0);
	semver_tt.prefix(number,'-',0);
	semver_tt.prefix(number,'.',0);
	
	semver_tt.acceptable(string,'a',lc::tokens::string,string);
	semver_tt.acceptable(string,'b',lc::tokens::string,string);
	semver_tt.acceptable(string,'c',lc::tokens::string,string);
	semver_tt.acceptable(string,'d',lc::tokens::string,string);
	semver_tt.acceptable(string,'e',lc::tokens::string,string);
	semver_tt.acceptable(string,'f',lc::tokens::string,string);
	semver_tt.acceptable(string,'g',lc::tokens::string,string);
	semver_tt.acceptable(string,'h',lc::tokens::string,string);
	semver_tt.acceptable(string,'i',lc::tokens::string,string);
	semver_tt.acceptable(string,'j',lc::tokens::string,string);
	semver_tt.acceptable(string,'k',lc::tokens::string,string);
	semver_tt.acceptable(string,'l',lc::tokens::string,string);
	semver_tt.acceptable(string,'m',lc::tokens::string,string);
	semver_tt.acceptable(string,'n',lc::tokens::string,string);
	semver_tt.acceptable(string,'o',lc::tokens::string,string);
	semver_tt.acceptable(string,'p',lc::tokens::string,string);
	semver_tt.acceptable(string,'q',lc::tokens::string,string);
	semver_tt.acceptable(string,'r',lc::tokens::string,string);
	semver_tt.acceptable(string,'s',lc::tokens::string,string);
	semver_tt.acceptable(string,'t',lc::tokens::string,string);
	semver_tt.acceptable(string,'u',lc::tokens::string,string);
	semver_tt.acceptable(string,'v',lc::tokens::string,string);
	semver_tt.acceptable(string,'w',lc::tokens::string,string);
	semver_tt.acceptable(string,'x',lc::tokens::string,string);
	semver_tt.acceptable(string,'y',lc::tokens::string,string);
	semver_tt.acceptable(string,'z',lc::tokens::string,string);	
	semver_tt.acceptable(string,'A',lc::tokens::string,string);
	semver_tt.acceptable(string,'B',lc::tokens::string,string);
	semver_tt.acceptable(string,'C',lc::tokens::string,string);
	semver_tt.acceptable(string,'D',lc::tokens::string,string);
	semver_tt.acceptable(string,'E',lc::tokens::string,string);
	semver_tt.acceptable(string,'F',lc::tokens::string,string);
	semver_tt.acceptable(string,'G',lc::tokens::string,string);
	semver_tt.acceptable(string,'H',lc::tokens::string,string);
	semver_tt.acceptable(string,'I',lc::tokens::string,string);
	semver_tt.acceptable(string,'J',lc::tokens::string,string);
	semver_tt.acceptable(string,'K',lc::tokens::string,string);
	semver_tt.acceptable(string,'L',lc::tokens::string,string);
	semver_tt.acceptable(string,'M',lc::tokens::string,string);
	semver_tt.acceptable(string,'N',lc::tokens::string,string);
	semver_tt.acceptable(string,'O',lc::tokens::string,string);
	semver_tt.acceptable(string,'P',lc::tokens::string,string);
	semver_tt.acceptable(string,'Q',lc::tokens::string,string);
	semver_tt.acceptable(string,'R',lc::tokens::string,string);
	semver_tt.acceptable(string,'S',lc::tokens::string,string);
	semver_tt.acceptable(string,'T',lc::tokens::string,string);
	semver_tt.acceptable(string,'U',lc::tokens::string,string);
	semver_tt.acceptable(string,'V',lc::tokens::string,string);
	semver_tt.acceptable(string,'W',lc::tokens::string,string);
	semver_tt.acceptable(string,'X',lc::tokens::string,string);
	semver_tt.acceptable(string,'Y',lc::tokens::string,string);
	semver_tt.acceptable(string,'Z',lc::tokens::string,string);
	semver_tt.acceptable(string,'0',lc::tokens::string,string);
	semver_tt.acceptable(string,'1',lc::tokens::string,string);
	semver_tt.acceptable(string,'2',lc::tokens::string,string);
	semver_tt.acceptable(string,'3',lc::tokens::string,string);
	semver_tt.acceptable(string,'4',lc::tokens::string,string);
	semver_tt.acceptable(string,'5',lc::tokens::string,string);
	semver_tt.acceptable(string,'6',lc::tokens::string,string);
	semver_tt.acceptable(string,'6',lc::tokens::string,string);
	semver_tt.acceptable(string,'8',lc::tokens::string,string);
	semver_tt.acceptable(string,'9',lc::tokens::string,string);
	semver_tt.prefix(string,'+',0);
	semver_tt.prefix(string,'-',0);
	semver_tt.prefix(string,'.',0);	
	
	//const char* input3 = "23";
	lc::Buffer semver_buff3(input);
	lc::A<char,lc::tokens,lc::Status,TT_BASE> semver_lex3(semver_tt,semver_buff3);

	lc::tokens semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == lc::tokens::string);
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
	typedef std::array<std::array<lc::Transition<lc::tokens,lc::Status>,lc::MAX_SIMBOLS>,4> TT_BASE;
	lc::Semver_TT<char,lc::tokens,lc::Status,TT_BASE> semver_tt_1;

	lc::Buffer semver_buff1(input1);
	lc::A<char,lc::tokens,lc::Status,TT_BASE> semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	lc::tokens semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::string);
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
	typedef std::array<std::array<lc::Transition<lc::tokens,lc::Status>,lc::MAX_SIMBOLS>,4> TT_BASE;
	lc::Semver_TT<char,lc::tokens,lc::Status,TT_BASE> semver_tt_1;

	lc::Buffer semver_buff1(input1);
	lc::A<char,lc::tokens,lc::Status,TT_BASE> semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	lc::tokens semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::string);
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
	typedef std::array<std::array<lc::Transition<lc::tokens,lc::Status>,lc::MAX_SIMBOLS>,4> TT_BASE;
	lc::Semver_TT<char,lc::tokens,lc::Status,TT_BASE> semver_tt_1;

	lc::Buffer semver_buff1(input1);
	lc::A<char,lc::tokens,lc::Status,TT_BASE> semver_lex1(semver_tt_1,semver_buff1);
	semver_lex1.echo(true);
	lc::tokens semver_tk1 = semver_lex1.next();
	/*CU_ASSERT(semver_tk1 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::string);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex1.is_accepted());
	
	semver_tk1 = semver_lex1.next();
	CU_ASSERT(semver_tk1 == lc::tokens::string);
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
