

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


void print(oct::core::v3::lc::semver_tokens tk,const char* input)
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
	case oct::core::v3::lc::semver_tokens::none:
		std::cout << "None";
		break;
	case oct::core::v3::lc::semver_tokens::number:
		std::cout << "Number";
		break;
	case oct::core::v3::lc::semver_tokens::dot:
		std::cout << "dot";
		break;
	case oct::core::v3::lc::semver_tokens::minus:
		std::cout << "minus";
		break;
	case oct::core::v3::lc::semver_tokens::plus:
		std::cout << "plus";
		break;
	case oct::core::v3::lc::semver_tokens::stage:
		std::cout << "stage";
		break;
	case oct::core::v3::lc::semver_tokens::build:
		std::cout << "build";
		break;
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}

void v3_lc_innier_semver()
{
	const char* input = "269.56.9-alpha+archlinux";
	
	oct::core::v3::lc::A<char,oct::core::v3::lc::semver_tokens,oct::core::v3::lc::Status>::TT semver_tt;
	oct::core::v3::lc::Status initial_status = semver_tt.add_status();
	semver_tt.initial(initial_status);
	//std::cout << "status : " << initial_status << "\n";	
	oct::core::v3::lc::Status major = semver_tt.add_status();
	semver_tt.initial(major);
	oct::core::v3::lc::Status majorPrefix = semver_tt.add_status();
	semver_tt.initial(majorPrefix);
	oct::core::v3::lc::Status minor = semver_tt.add_status();
	semver_tt.initial(minor);
	oct::core::v3::lc::Status minorPrefix = semver_tt.add_status();
	semver_tt.initial(minorPrefix);
	oct::core::v3::lc::Status patch = semver_tt.add_status();
	semver_tt.initial(patch);
	oct::core::v3::lc::Status patchPrefix = semver_tt.add_status();
	semver_tt.initial(patchPrefix);
	oct::core::v3::lc::Status stage = semver_tt.add_status();
	semver_tt.initial(stage);
	oct::core::v3::lc::Status stagePrefix = semver_tt.add_status();
	semver_tt.initial(stagePrefix);
	oct::core::v3::lc::Status build = semver_tt.add_status();
	semver_tt.initial(build,oct::core::v3::lc::Indicator::terminate);
	
	semver_tt.acceptable(initial_status,'0',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'1',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'2',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'3',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'4',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'5',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'6',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'6',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'8',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(initial_status,'9',oct::core::v3::lc::semver_tokens::number,major);	
	
	semver_tt.acceptable(major,'0',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'1',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'2',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'3',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'4',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'5',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'6',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'6',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'8',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.acceptable(major,'9',oct::core::v3::lc::semver_tokens::number,major);
	semver_tt.prefix(major,'.',majorPrefix);
	semver_tt.prefix(major,'-',majorPrefix);
	semver_tt.prefix(major,'+',majorPrefix);	
	
	semver_tt.accept(majorPrefix,'.',oct::core::v3::lc::semver_tokens::dot,minor);
	semver_tt.accept(majorPrefix,'-',oct::core::v3::lc::semver_tokens::minus,stage);
	semver_tt.accept(majorPrefix,'+',oct::core::v3::lc::semver_tokens::plus,build);	
	
	semver_tt.acceptable(minor,'0',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'1',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'2',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'3',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'4',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'5',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'6',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'6',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'8',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(minor,'9',oct::core::v3::lc::semver_tokens::number,minor);	
	semver_tt.prefix(minor,'.',minorPrefix);
	semver_tt.prefix(minor,'-',minorPrefix);
	semver_tt.prefix(minor,'+',minorPrefix);
	
	semver_tt.accept(minorPrefix,'.',oct::core::v3::lc::semver_tokens::dot,patch);
	semver_tt.accept(minorPrefix,'-',oct::core::v3::lc::semver_tokens::minus,stage);
	semver_tt.accept(minorPrefix,'+',oct::core::v3::lc::semver_tokens::plus,build);
	
	semver_tt.acceptable(patch,'0',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'1',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'2',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'3',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'4',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'5',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'6',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'6',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'8',oct::core::v3::lc::semver_tokens::number,patch);
	semver_tt.acceptable(patch,'9',oct::core::v3::lc::semver_tokens::number,patch);	
	semver_tt.prefix(patch,'-',patchPrefix);
	semver_tt.prefix(patch,'+',patchPrefix);
	
	semver_tt.accept(patchPrefix,'-',oct::core::v3::lc::semver_tokens::minus,stage);
	semver_tt.accept(patchPrefix,'+',oct::core::v3::lc::semver_tokens::plus,build);
		
	semver_tt.acceptable(stage,'a',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'b',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'c',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'d',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'e',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'f',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'g',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'h',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'i',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'j',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'k',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'l',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'m',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'n',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'o',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'p',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'q',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'r',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'s',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'t',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'u',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'v',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'w',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'x',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'y',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'z',oct::core::v3::lc::semver_tokens::stage,stage);	
	semver_tt.acceptable(stage,'A',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'B',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'C',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'D',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'E',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'F',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'G',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'H',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'I',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'J',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'K',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'L',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'M',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'N',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'O',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'P',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'Q',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'R',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'S',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'T',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'U',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'V',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'W',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'X',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'Y',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'Z',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'0',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'1',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'2',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'3',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'4',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'5',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'6',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'6',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'8',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.acceptable(stage,'9',oct::core::v3::lc::semver_tokens::stage,stage);
	semver_tt.prefix(stage,'+',stagePrefix);
	
	semver_tt.accept(stagePrefix,'+',oct::core::v3::lc::semver_tokens::plus,build);	
	
	semver_tt.acceptable(build,'a',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'b',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'c',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'d',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'e',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'f',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'g',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'h',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'i',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'j',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'k',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'l',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'m',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'n',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'o',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'p',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'q',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'r',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'s',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'t',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'u',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'v',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'w',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'x',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'y',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'z',oct::core::v3::lc::semver_tokens::build,build);	
	semver_tt.acceptable(build,'A',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'B',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'C',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'D',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'E',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'F',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'G',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'H',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'I',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'J',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'K',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'L',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'M',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'N',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'O',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'P',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'Q',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'R',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'S',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'T',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'U',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'V',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'W',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'X',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'Y',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'Z',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'0',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'1',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'2',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'3',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'4',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'5',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'6',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'6',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'8',oct::core::v3::lc::semver_tokens::build,build);
	semver_tt.acceptable(build,'9',oct::core::v3::lc::semver_tokens::build,build);	
	
	//const char* input3 = "23";
	oct::core::v3::lc::Buffer semver_buff3(input);
	oct::core::v3::lc::A<char,oct::core::v3::lc::semver_tokens,oct::core::v3::lc::Status> semver_lex3(semver_tt,semver_buff3);

	oct::core::v3::lc::semver_tokens semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::dot);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::number);
	//print(semver_tk3,input);
	//std::cout << "\n";	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::minus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//semver_lex3.echo(true);
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::stage);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::plus);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
#endif	
	CU_ASSERT(semver_lex3.is_accepted());
	
	semver_tk3 = semver_lex3.next();
	CU_ASSERT(semver_tk3 == oct::core::v3::lc::semver_tokens::build);
#ifdef OCTEOTOS_CAVE_ENABLE_DEV
	//print(semver_tk3,input);
	//std::cout << "\n";	
	//semver_lex3.echo(false);
#endif
	CU_ASSERT(semver_lex3.is_accepted());
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
