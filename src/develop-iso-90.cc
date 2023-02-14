
/*
 * main.cc
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 * 
 * CC is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CC is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <array>

#include "Buffer-v3.hh"
#include "lexer-v3.hh"


enum class Tokens_C90 : int
{//https://www.charset.org/utf-8,https://www.asciitable.com/,https://www.rapidtables.com/code/text/ascii-table.html
	none = -1,
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

	EuroSign = 218,
	//>>>Extended ASCII






	y_Diaeresis = 255,//ÿ
	//>>>UTF-8
	a_Macron = 256,

	s_Coptic = 999,
	//Inicode >>>


	//>>>Tokens
	tokens = 0x110000,
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
	identifier


};
constexpr size_t initial_lex_c_90 = 0;
constexpr size_t max_status_c_90 = 4;

constexpr std::array digits {'0','1','2','3','4','5','6','7','8','9'};
constexpr std::array lower = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','y','z'};
constexpr std::array upper = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','Y','Z'};
constexpr std::array graphic = { '!','"','#','%','%','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','[','\\',']','^','_','{','|','}','~'};
constexpr std::array display = { '\a','\b','\f','\n','\r','\t','\v'};
constexpr std::array not_c = {' '};
struct pair_keyword
{
	const char* string;
	Tokens_C90 token;
};
constexpr pair_keyword keywords[] = {
	{"auto",Tokens_C90::keyword_auto},
	{"break",Tokens_C90::keyword_break},
	{"case",Tokens_C90::keyword_case},
	{"char",Tokens_C90::keyword_char},
	{"const",Tokens_C90::keyword_const},
	{"continue",Tokens_C90::keyword_continue},
	{"default",Tokens_C90::keyword_default},
	{"do",Tokens_C90::keyword_do},
	{"double",Tokens_C90::keyword_double}
};

typedef core_next::lex::TT<char, Tokens_C90, core_next::lex::State> LexC90;

constexpr LexC90 create_tt_c90()
{
	const int simbols_amount = 97;
	std::vector<char> symbols;
	symbols.reserve(simbols_amount);
	for (char c : digits)
	{
		symbols.push_back(c);
	}
	for (char c : lower)
	{
		symbols.push_back(c);
	}
	for (char c : upper)
	{
		symbols.push_back(c);
	}
	for (char c : graphic)
	{
		symbols.push_back(c);
	}
	for (char c : display)
	{
		symbols.push_back(c);
	}
	for (char c : not_c)
	{
		symbols.push_back(c);
	}

	std::vector<char> symbols_end_words(37);
	for (char c : graphic)
	{
		symbols_end_words.push_back(c);
	}
	for (char c : display)
	{
		symbols_end_words.push_back(c);
	}
	for (char c : not_c)
	{
		symbols_end_words.push_back(c);
	}
	
	//static_assert(symbols.size() == simbols_amount,"La cantidad de sumbolos en el lenguaje no es correcta");

	LexC90 c90(symbols);
	/*
	for (const pair_keyword& p : keywords)
	{
		c90.word(p.string,p.token, symbols_end_words);
	}
	*/
	c90.word(keywords[0].string, keywords[0].token, symbols_end_words);
	return c90;
}

int main()
{
	std::filesystem::path file1_c90 = "C:\\Users\\Azael\\Documents\\develop\\octetos\\OCC\\tests\\main-ansi-90.c";
	const char* str_c90 = "auto char break";
	core_next::Buffer<char> buff1_c90(str_c90);
	auto tt_c90 = create_tt_c90();
	std::cout << "TT listing...\n";
	tt_c90.print(std::cout);
	std::cout << "\n";
	//core_next::lex::A lex_c90(tt_c90, buff1_c90);

	/*for (char c : tt_c90.simbols())
	{
		std::cout << c << "\n";
	}*/

	if(tt_c90.simbols().size() != 97) std::cout << "La cantidad de simbolo es : " << tt_c90.simbols().size() << ", sin embargo, deve ser 97\n";

	//Tokens_C90 tk_c90 = lex_c90.next();
	std::cout << "TT size : " << tt_c90.size() << "\n";


	return EXIT_SUCCESS;
}

