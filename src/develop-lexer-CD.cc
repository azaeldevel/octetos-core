
#include <iostream>


#include "lexer-TTC-v3.hh"

enum class Tokens : int
	{//https://www.charset.org/utf-8,https://www.asciitable.com/,https://www.rapidtables.com/code/text/ascii-table.html
		command = -100,
		eoi,//end of input
		none,
		//ASCII>>>
		NUL = 0,
		SOH,
		STX,
		ETX,
		EOT,
		ENQ,
		ACK,
		BEL,
		BS,
		TAB,
		LF,
		VT,
		FF,
		CR,
		SO,
		SI,
		DLE,
		DC1,
		DC2,
		DC3,
		DC4,
		NAK,
		SYN,
		ETB,
		CAN,
		EM,
		SUB,
		ESC,
		FS,
		GS,
		RS,
		US = 31,
		space,
		exclamation_mark,
		double_quote,
		symbol_numbers,
		symbol_money,
		percen,
		ampersan,
		single_quote,
		parenthesis_open,
		parenthesis_close,
		asterisk,
		plus,
		minus,
		dot,
		symbol_diagonal,
		digit_0 = 48,
		digit_1,
		digit_2,
		digit_3,
		digit_4,
		digit_5,
		digit_6,
		digit_7,
		digit_8,
		digit_9,
		symbol_column,
		semicolumn,
		less,
		equal,
		grater,
		question,
		arroba,
		//>>upper case
		char_A = 65,
		char_B,
		char_C,
		char_D,
		char_E,
		char_F,
		char_G,
		char_H,
		char_I,
		char_J,
		char_K,
		char_L,
		char_M,
		char_N,
		char_O,
		char_P,
		char_Q,
		char_R,
		char_S,
		char_T,
		char_U,
		char_V,
		char_W,
		char_X,
		char_Y,
		char_Z,
		//>>
		brackets_open,
		diagonal_inverted,
		brackets_close,
		hat,
		guion_down,
		//>>>
		char_a = 97,
		char_b,
		char_c,
		char_d,
		char_e,
		char_f,
		char_g,
		char_h,
		char_i,
		char_j,
		char_k,
		char_l,
		char_m,
		char_n,
		char_o,
		char_p,
		char_q,
		char_r,
		char_s,
		char_t,
		char_u,
		char_v,
		char_w,
		char_x,
		char_y,
		char_z,
		curly_brackets_open,
		bar,
		curly_brackets_close,
		umlaut,
		EuroSign = 218,
		//>>>Extended ASCII






		y_Diaeresis = 255,//ÿ
		//>>>UTF-8
		a_Macron = 256,

		s_Coptic = 999,
		//Inicode >>>


		//>>>Tokens
		base = 0x110000,
		new_line,
		keyword_auto,
		keyword_break,
		keyword_case,
		keyword_char,
		keyword_const,
		keyword_continue,
		keyword_default,
		keyword_do,
		keyword_double,
		keyword_else,
		keyword_enum,
		keyword_extern,
		keyword_float,
		keyword_for,
		keyword_goto,
		keyword_if,
		keyword_int,
		keyword_long,
		keyword_register,
		keyword_return,
		keyword_short,
		keyword_signed,
		keyword_sizeof,
		keyword_static,
		keyword_struct,
		keyword_switch,
		keyword_typedef,
		keyword_union,
		keyword_unsigned,
		keyword_void,
		keyword_volatil,
		keyword_while,
		identifier,
		integer,

	};

namespace core_here = oct::core::v3;
const std::vector<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
const std::vector<char> lower = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const std::vector<char> upper = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
const std::vector<char> graphic = { '!','"','#','%','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','[','\\',']','^','_','{','|','}','~'};
const std::vector<char> display = { '\a','\b','\f','\n','\r','\t','\v'};
const std::vector<char> not_c = {' '};
const std::vector<char> alphabet = {' ','\a','\b','\f','\n','\r','\t','\v','0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','!','"','#','%','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','[','\\',']','^','_','{','|','}','~'};
const std::vector<char> symbols_end_words = {' ','\a','\b','\f','\n','\r','\t','\v','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','!','"','#','%','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','[','\\',']','^','_','{','|','}','~'};
const std::vector<char> symbols_identifier_begin = {'_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const std::vector<char> symbols_identifier = {'0','1','2','3','4','5','6','7','8','9','_','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const std::vector<core_here::lex::pair_keyword<char, Tokens>> keywords = {
		{"auto",Tokens::keyword_auto},
		{"break",Tokens::keyword_break},
		{"case",Tokens::keyword_case},
		{"char",Tokens::keyword_char},
		{"const",Tokens::keyword_const},
		{"continue",Tokens::keyword_continue},
		{"default",Tokens::keyword_default},
		{"do",Tokens::keyword_do},
		{"double",Tokens::keyword_double},
		{"else",Tokens::keyword_else},
		{"enum",Tokens::keyword_enum},
		{"extern",Tokens::keyword_extern},
		{"float",Tokens::keyword_float},
		{"for",Tokens::keyword_for},
		{"goto",Tokens::keyword_goto},
		{"if",Tokens::keyword_if},
		{"int",Tokens::keyword_int},
		{"long",Tokens::keyword_long},
		{"register",Tokens::keyword_register},
		{"return",Tokens::keyword_return},
		{"short",Tokens::keyword_short},
		{"signed",Tokens::keyword_signed},
		{"sizeof",Tokens::keyword_sizeof},
		{"static",Tokens::keyword_static},
		{"struct",Tokens::keyword_struct},
		{"switch",Tokens::keyword_switch},
		{"typedef",Tokens::keyword_typedef},
		{"union",Tokens::keyword_union},
		{"unsigned",Tokens::keyword_unsigned},
		{"void",Tokens::keyword_void},
		{"volatil",Tokens::keyword_volatil},
		{"while",Tokens::keyword_while}
	};

typedef core_here::lex::TTC<char,Tokens, core_here::lex::State,1,128> TT;

	template<typename Token> std::string to_string(Token t)
	{
		std::string str;

		if (t < Token::base)
		{
			return core_next::lex::to_string(t);
		}
		else if (t > Token::base)
		{
			if (t > Token::keyword_auto)
			{
				return "keyword auto";
			}
			else if (t > Token::keyword_break)
			{
				return "keyword break";
			}
			else if (t > Token::keyword_case)
			{
				return "keyword case";
			}
		}

		return std::to_string((int)t);
	}

int main(int argc, char* argv[])
{
    std::cout << "///>>>C section\n\n\n";
	///>>>C
	std::filesystem::path file1_c90 = "C:\\Users\\Azael\\Documents\\develop\\octetos\\OCC\\tests\\main-ansi-90.c";
	//const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	const char* str_c90 = "auto char break switch volatil void int 923456789 5 j a0 aabcd a1_test z juan contianer09 _09cont _09cont % ? #";
	core_next::Buffer<char> buff1_c90(str_c90);
	TT tt_c90(alphabet);
	for (const auto& p : keywords)
	{
		tt_c90.word(p.string,p.token, symbols_end_words,core_here::lex::Flag::error);
	}
	tt_c90.almost_one(digits,Tokens::integer,symbols_end_words,core_here::lex::Flag::error);

    //core_here::lex::State identifier = tt_c90.one(symbols_end_words,Tokens::identifier,symbols_end_words,core_here::lex::Flag::only_free);
    //tt_c90.some(symbols_identifier, Tokens::identifier, symbols_end_words,core_here::lex::Flag::join_same,identifier);



	std::cout << "Size TT : " << tt_c90.size() << "\n";
	/*std::cout << "Listing states\n";
	tt_c90.print(std::cout);
	std::cout << "\n";*/
	core_next::lex::Lexer<char,Tokens, core_here::lex::State,TT> lex_c90(tt_c90, buff1_c90);

	std::cout << "\n\n";
	Tokens tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::keyword_auto)
	{
		std::cout << "Fallo, se espera keyword auto, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::keyword_char)
	{
		std::cout << "Fallo, se espera keywod char, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}
	//std::cout << "\n";

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::keyword_break)
	{
		std::cout << "Fallo, se espera keywod break, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::keyword_switch)
	{
		std::cout << "Fallo, se espera keywod switch, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::keyword_volatil)
	{
		std::cout << "Fallo, se espera keywod volatil, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::keyword_void)
	{
		std::cout << "Fallo, se espera keywod void, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::keyword_int)
	{
		std::cout << "Fallo, se espera keywod int, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::integer)
	{
		std::cout << "Fallo, se espera integer, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::integer)
	{
		std::cout << "Fallo, se espera integer, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	tk_c90 = lex_c90.next();
	if (tk_c90 != Tokens::space)
	{
		std::cout << "Fallo, se espera space, se encontro " << to_string(tk_c90) << " - " << std::to_string((int)tk_c90) << "\n";
	}

	return EXIT_SUCCESS;
}
