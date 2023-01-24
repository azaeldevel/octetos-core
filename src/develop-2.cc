
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
	typedef std::array<std::array<v3::lc::Transition<v3::lc::Tokens,v3::lc::Status>,v3::lc::ASCII_LENGTH>,3> TT_BASE;
	v3::lc::Semver_TT<char,v3::lc::Tokens,v3::lc::Status,TT_BASE> semver_tt_1;
	std::string token_str;
	v3::Buffer semver_buff1(input1);
	const char* buf_start = (const char*)semver_buff1;
	size_t length = strlen(input1);
	const char* buff_end = buf_start + length;
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
	std::cout << token_str << "\n";
	if (not semver_lex1.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 3) std::cout << "Fail\n";
	if (token_str.compare("269") != 0) std::cout << "Fail : " << token_str << "\n";

	if (semver_lex1.next('.'))
	{
		std::cout << ".\n";
		if (not semver_lex1.is_accepted()) std::cout << "Rechazado '.'\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex1.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 2) std::cout << "Fail\n";
	if(token_str.compare("56") != 0) std::cout << "Fail : " << token_str << "\n";

	if (semver_lex1.next('.'))
	{
		std::cout << ".\n";
		if (not semver_lex1.is_accepted()) std::cout << "Rechazado '.'\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex1.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 1) std::cout << "Fail\n";
	if (token_str.compare("9") != 0) std::cout << "Fail : " << token_str << "\n";

	if (semver_lex1.next('-'))
	{
		std::cout << "-\n";
		if (not semver_lex1.is_accepted()) std::cout << "Rechazado '-.'\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex1.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 5) std::cout << "Fail\n";
	if (token_str.compare("alpha") != 0) std::cout << "Fail : " << token_str << "\n";

	if (semver_lex1.next('+'))
	{
		std::cout << "+\n";
		if (not semver_lex1.is_accepted()) std::cout << "Rechazado '+'\n";
	}

	semver_tk1 = semver_lex1.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex1.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 9) std::cout << "Fail\n";
	if (token_str.compare("archlinux") != 0) std::cout << "Fail : " << token_str << "\n";

	std::cout << "\n\n\n";
	
	std::list<std::string> tokens;
	const char* input2 = "269.5t6.9-alpha2";
	v3::Buffer semver_buff2(input2);
	v3::lc::A semver_lex2(semver_tt_1, semver_buff2);
	buf_start = (const char*)semver_buff2;
	length = strlen(input2);
	buff_end = buf_start + length;
	std::cout << "input2 : " << input2 << "\n";

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex2.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 3) std::cout << "Fail\n";
	if (token_str.compare("269") != 0) std::cout << "Fail : " << token_str << "\n";

	if (semver_lex2.next('.'))
	{
		std::cout << ".\n";
		if (not semver_lex2.is_accepted()) std::cout << "Rechazado '.'\n";
	}

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex2.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 1) std::cout << "Fail\n";
	if (token_str.compare("5") != 0) std::cout << "Fail : " << token_str << "\n";

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex2.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 2) std::cout << "Fail length\n";
	if (token_str.compare("t6") != 0) std::cout << "Fail : " << token_str << "\n";

	if (semver_lex2.next('.'))
	{
		std::cout << ".\n";
		if (not semver_lex2.is_accepted()) std::cout << "Rechazado '.'\n";
	}

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex2.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 1) std::cout << "Fail length\n";
	if (token_str.compare("9") != 0) std::cout << "Fail : " << token_str << "\n";

	if (semver_lex2.next('-'))
	{
		std::cout << "-\n";
		if (not semver_lex2.is_accepted()) std::cout << "Rechazado '-'\n";
	}

	semver_tk1 = semver_lex2.next(content);
	//semver_lex1.token_to_string(token_str);
	//std::cout << "token_str : " << token_str << "\n";
	//print(semver_tk1,input1);
	token_str.clear();
	content.load(token_str);
	std::cout << token_str << "\n";
	if (not semver_lex2.is_accepted()) std::cout << "Rechazado\n";
	if (content.length != 6) std::cout << "Fail length\n";
	if (token_str.compare("alpha2") != 0) std::cout << "Fail asas: " << token_str << "\n";
	

	return EXIT_SUCCESS;
}
