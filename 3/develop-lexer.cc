
#include <iostream>

#include "core.hh"
#include "lexer-v3.hh"

constexpr oct::core::v3::lex::A<char, oct::core::v3::lex::Token, oct::core::v3::lex::State> c_90_lexer()
{
	oct::core::v3::lex::A<char, oct::core::v3::lex::Token, oct::core::v3::lex::State> c_90_tt;

}
int main(int argc, char* argv[])
{
	long number = core_next::to_number<long>("123456789");
	std::cout << "Number : " << number << "\n";
	
	return EXIT_SUCCESS;
}
