
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
	case oct::core::v3::lc::semver_tokens::dot:
		std::cout << "dot";
		break;
	case oct::core::v3::lc::semver_tokens::minus:
		std::cout << "minus";
		break;
	case oct::core::v3::lc::semver_tokens::plus:
		std::cout << "plus";
		break;
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}
bool lexing(const char* input)
{
	std::cout << "Reading : " << input << "\n";
	
	oct::core::v3::lc::A<char,oct::core::v3::lc::semver_tokens,oct::core::v3::lc::Status>::TT semver_tt;
	oct::core::v3::lc::Status initial_status = semver_tt.add_status();
	//std::cout << "status : " << initial_status << "\n";	
	oct::core::v3::lc::Status major = semver_tt.add_status();
	oct::core::v3::lc::Status majorPrefix = semver_tt.add_status();
	oct::core::v3::lc::Status minor = semver_tt.add_status();
	oct::core::v3::lc::Status minorPrefix = semver_tt.add_status();
	oct::core::v3::lc::Status patch = semver_tt.add_status();
	oct::core::v3::lc::Status patchPrefix = semver_tt.add_status();
	oct::core::v3::lc::Status stage = semver_tt.add_status();
	oct::core::v3::lc::Status build = semver_tt.add_status();
	
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
	
	
	//const char* input3 = "23";
	oct::core::v3::lc::Buffer semver_buff3(input);
	oct::core::v3::lc::A<char,oct::core::v3::lc::semver_tokens,oct::core::v3::lc::Status> semver_lex3(semver_tt,semver_buff3);

	oct::core::v3::lc::semver_tokens semver_tk3 = semver_lex3.next();
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
	const char* input = "269";
	//lexing(NULL);
	
	//lexing("2");
	
	//lexing("23");
	
	//lexing("");
	
	//lexing("269");
	
	//lexing("269.56");
	
	lexing("269.56.9");
	
	return EXIT_SUCCESS;
}
