
#include <iostream>
#include <cstring>
#include "lexer-semver-v3.hh"

namespace v3 = oct::core::v3;


void print(v3::lc::tokens tk,const char* input)
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
	case v3::lc::tokens::none:
		std::cout << "None";
		break;
	case v3::lc::tokens::number:
		std::cout << "Number";
		break;
	case v3::lc::tokens::dot:
		std::cout << "dot";
		break;
	case v3::lc::tokens::minus:
		std::cout << "minus";
		break;
	case v3::lc::tokens::plus:
		std::cout << "plus";
		break;
	case v3::lc::tokens::string:
		std::cout << "string";
		break;
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	const char* input1 = "269.56.9-alpha+archlinux";
	typedef std::array<std::array<v3::lc::Transition<v3::lc::tokens,v3::lc::Status>,v3::lc::MAX_SIMBOLS>,4> TT_BASE;
	v3::lc::Semver_TT<char,v3::lc::tokens,v3::lc::Status,TT_BASE> semver_tt_1;

	v3::lc::Buffer semver_buff1(input1);
	v3::lc::A semver_lex1(semver_tt_1,semver_buff1);
	//semver_lex1.echo(true);
	
	v3::lc::tokens semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	//std::cout << "\n";
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);
	
	//semver_tk1 = semver_lex1.next();
	//print(semver_tk1,input1);

	
	return EXIT_SUCCESS;
}
