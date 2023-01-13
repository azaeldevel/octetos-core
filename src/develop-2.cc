
#include <iostream>
#include <cstring>
#include "dfa-semver-v3.hh"


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
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}
void lexing(const char* input)
{
	oct::core::v3::lc::A<char,oct::core::v3::lc::semver_tokens,oct::core::v3::lc::Status>::TT semver_tt;
	oct::core::v3::lc::Status initial_status = semver_tt.add_status();
	//std::cout << "status : " << initial_status << "\n";
	
	oct::core::v3::lc::Status major = semver_tt.add_status();
	//std::cout << "status : " << status1 << "\n";
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
	semver_tt.prefix(major,'.');
	semver_tt.prefix(major,'-');
	semver_tt.prefix(major,'+');	
	oct::core::v3::lc::Status majorPrefix = semver_tt.add_status();
	oct::core::v3::lc::Status minor = semver_tt.add_status();
	oct::core::v3::lc::Status patch = semver_tt.add_status();
	oct::core::v3::lc::Status stage = semver_tt.add_status();
	oct::core::v3::lc::Status build = semver_tt.add_status();
	semver_tt.acceptable(majorPrefix,'.',oct::core::v3::lc::semver_tokens::number,minor);
	semver_tt.acceptable(majorPrefix,'-',oct::core::v3::lc::semver_tokens::number,stage);
	semver_tt.acceptable(majorPrefix,'+',oct::core::v3::lc::semver_tokens::number,build);	
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
	semver_tt.prefix(minor,'.');
	semver_tt.prefix(minor,'-');
	semver_tt.prefix(minor,'+');
	//const char* input3 = "23";
	oct::core::v3::lc::Buffer semver_buff3(input);
	oct::core::v3::lc::A<char,oct::core::v3::lc::semver_tokens,oct::core::v3::lc::Status> semver_lex3(semver_tt,semver_buff3);
	oct::core::v3::lc::semver_tokens semver_tk3 = semver_lex3.next();
	//print(semver_tk3,input);
}

int main(int argc, char* argv[])
{
	//lexing(NULL);
	
	//lexing("2");
	
	//lexing("23");
	
	//lexing("");
	
	//lexing("269");	

	lexing("269.");	
	
	return EXIT_SUCCESS;
}
