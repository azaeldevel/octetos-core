
#include <iostream>


#include "lexer-TTC-v3.hh"

namespace core_here = oct::core::v3;
const std::vector<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
const std::vector<char> lower = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const std::vector<char> upper = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const std::vector<char> graphic = { '!','"','#','%','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','[','\\',']','^','_','{','|','}','~'};
const std::vector<char> display = { '\a','\b','\f','\n','\r','\t','\v'};
const std::vector<char> not_c = {' '};

const std::vector<char> alphabet = {' ','\a','\b','\f','\n','\r','\t','\v','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','!','"','#','%','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','[','\\',']','^','_','{','|','}','~'};

typedef core_here::lex::TTC<char,core_here::lex::Tokens, core_here::lex::State,1,128> TT;

int main(int argc, char* argv[])
{
    std::cout << "///>>>C section\n\n\n";
	///>>>C
	std::filesystem::path file1_c90 = "C:\\Users\\Azael\\Documents\\develop\\octetos\\OCC\\tests\\main-ansi-90.c";
	//const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	core_next::Buffer<char> buff1_c90(str_c90);
	TT tt_c90(alphabet);
	std::cout << "Size TT : " << tt_c90.size() << "\n";
	std::cout << "Listing states\n";
	tt_c90.print(std::cout);
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
