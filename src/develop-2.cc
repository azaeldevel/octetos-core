
#include <iostream>
#include <cstring>
#include "lexer-semver-v3.hh"

namespace v3 = oct::core::v3;



int main(int argc, char* argv[])
{
	const char* input1 = "269.56.9-alpha+archlinux";
	if(v3::strlen(input1) != std::strlen(input1))
	{
		std::cout << "strlen : fallo\n";
	}
	v3::lc::Tokens semver_tk1;
	typedef std::array<std::array<v3::lc::Transition<v3::lc::Tokens,v3::lc::Status>,v3::lc::MAX_SIMBOLS>,4> TT_BASE;
	v3::lc::Semver_TT<char,v3::lc::Tokens,v3::lc::Status,TT_BASE> semver_tt_1;
	std::string token_str;
	v3::Buffer semver_buff1(input1);
	v3::lc::A semver_lex1(semver_tt_1,semver_buff1);
	v3::lc::A<char, v3::lc::Tokens, v3::lc::Status, TT_BASE>::Content content;
	std::cout << "input1 : " << input1 << "\n";
	//semver_lex1.echo(true);

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if(semver_lex1.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	if (semver_lex1.next('.'))
	{
		if (semver_lex1.is_accepted()) std::cout << "Aceptado '.'\n";
		else std::cout << "Rechazado '.'\n";
		std::cout << "\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex1.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	if (semver_lex1.next('.'))
	{
		if (semver_lex1.is_accepted()) std::cout << "Aceptado '.'\n";
		else std::cout << "Rechazado '.'\n";
		std::cout << "\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex1.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	if (semver_lex1.next('-'))
	{
		if (semver_lex1.is_accepted()) std::cout << "Aceptado '-'\n";
		else std::cout << "Rechazado '-'\n";
		std::cout << "\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex1.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	if (semver_lex1.next('+'))
	{
		if (semver_lex1.is_accepted()) std::cout << "Aceptado '+'\n";
		else std::cout << "Rechazado '+'\n";
		std::cout << "\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex1.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	std::cout << "\n\n\n";
	
	std::list<std::string> tokens;
	const char* input2 = "269.5t6.9-lapha2";
	v3::Buffer semver_buff2(input2);
	v3::lc::A semver_lex2(semver_tt_1, semver_buff2);
	std::cout << "input2 : " << input2 << "\n";

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex2.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	if (semver_lex2.next('.'))
	{
		if (semver_lex2.is_accepted()) std::cout << "Aceptado '.'\n";
		else std::cout << "Rechazado '.'\n";
		std::cout << "\n";
	}

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex2.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex2.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	if (semver_lex2.next('.'))
	{
		if (semver_lex2.is_accepted()) std::cout << "Aceptado '.'\n";
		else std::cout << "Rechazado '.'\n";
		std::cout << "\n";
	}

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex2.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";

	if (semver_lex2.next('-'))
	{
		if (semver_lex2.is_accepted()) std::cout << "Aceptado '-'\n";
		else std::cout << "Rechazado '-'\n";
		std::cout << "\n";
	}

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << " : ";
	if (semver_lex2.is_accepted()) std::cout << "Aceptado\n";
	else std::cout << "Rechazado\n";
	std::cout << "\n";
	

	return EXIT_SUCCESS;
}
