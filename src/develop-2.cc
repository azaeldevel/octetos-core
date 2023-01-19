
#include <iostream>
#include <cstring>
#include "lexer-semver-v3.hh"

namespace v3 = oct::core::v3;


void print(v3::lc::Tokens tk,const char* input)
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
	case v3::lc::Tokens::none:
		std::cout << "None";
		break;
	case v3::lc::Tokens::number:
		std::cout << "Number";
		break;
	case v3::lc::Tokens::dot:
		std::cout << "dot";
		break;
	case v3::lc::Tokens::minus:
		std::cout << "minus";
		break;
	case v3::lc::Tokens::plus:
		std::cout << "plus";
		break;
	case v3::lc::Tokens::string:
		std::cout << "string";
		break;
	default:
		std::cout << "Unknown";
	}
	std::cout << "\n";
}

int main(int argc, char* argv[])
{
	const char* input1 = "259.s";
	if(v3::strlen(input1) != std::strlen(input1))
	{
		std::cout << "strlen : fallo\n";
	}
	typedef std::array<std::array<v3::lc::Transition<v3::lc::Tokens,v3::lc::Status>,v3::lc::MAX_SIMBOLS>,4> TT_BASE;
	v3::lc::Semver_TT<char,v3::lc::Tokens,v3::lc::Status,TT_BASE> semver_tt_1;
	std::string token_str;
	v3::Buffer semver_buff1(input1);
	v3::lc::A semver_lex1(semver_tt_1,semver_buff1);
	//std::cout << "token_str : " << token_str << "\n";
	semver_lex1.echo(true);

	v3::lc::Tokens semver_tk1 = semver_lex1.next();
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	std::cout << "\n";

	semver_tk1 = semver_lex1.next();
	////semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	std::cout << "\n";

	semver_tk1 = semver_lex1.next();
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	std::cout << "\n";

	semver_tk1 = semver_lex1.next();
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	std::cout << "\n";

	/*semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);

	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);

	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);

	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);

	semver_tk1 = semver_lex1.next();
	print(semver_tk1,input1);*/

	//semver_tk1 = semver_lex1.next();
	//print(semver_tk1,input1);


	return EXIT_SUCCESS;
}
