
#include <iostream>
#include <cstring>
#include "lexer-semver-v3.hh"

using namespace oct::core::v3;

int main(int argc, char* argv[])
{
	const char* input1 = "269.56.9-alpha+archlinux";
	lc::Semver_TT<char,lc::tokens,lc::Status> semver_tt_1;

	lc::Buffer semver_buff1(input1);
	lc::A<char,lc::tokens,lc::Status> semver_lex1(semver_tt_1,semver_buff1);
	
	
	return EXIT_SUCCESS;
}
