
#include <iostream>


#include "lexer-TTC-v3.hh"

namespace core_here = oct::core::v3;

typedef core_here::lex::TTC<char,core_here::lex::Tokens, core_here::lex::State,128> TT;

int main(int argc, char* argv[])
{
    std::cout << "///>>>C section\n\n\n";
	///>>>C
	std::filesystem::path file1_c90 = "C:\\Users\\Azael\\Documents\\develop\\octetos\\OCC\\tests\\main-ansi-90.c";
	//const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	core_next::Buffer<char> buff1_c90(str_c90);
	TT tt_c90;
	std::cout << "\n";
	core_next::lex::Lexer<char, core_here::lex::Tokens, core_here::lex::State,TT> lex_c90(tt_c90, buff1_c90);

	/*std::cout << "\n\n";
	occ_here::c90::Tokens tk_c90 = lex_c90.next();
	if (tk_c90 != occ_here::c90::Tokens::keyword_auto)
	{
		std::cout << "Fallo, se espera keyword auto, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}*/

	return EXIT_SUCCESS;
}
