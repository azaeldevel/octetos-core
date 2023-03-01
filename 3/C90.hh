
/*
 * main.cc
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 *
 * Octetos Compuler Collection is free software: you can redistribute it and/or modify it
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
#include <vector>
#include <algorithm>

#include "Buffer.hh"
#include "Lexer-TTA.hh"
#include "Lexer-TTB.hh"


namespace core_here = oct::core::v3;
namespace oct::cc::v0::c90
{
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
	template<typename Token> std::string to_string(Token t)
	{
		std::string str;

		if (t < Token::base)
		{
			return core_here::lex::to_string(t);
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
	template<typename Token> std::string category(Token t)
	{
		std::string str;

		if (t <= Token::US)
		{

		}
		else if (t >= Token::digit_0 and t <= Token::digit_9)
		{
			return "Digito";
		}
		else if (t >= Token::char_a and t <= Token::char_z)
		{
			return "Minuscula";
		}
		else if (t >= Token::char_A and t <= Token::char_Z)
		{
			return "Mayuscusla";
		}
		else if (t >= Token::keyword_auto and t <= Token::keyword_while)
		{
			return "Keyword";
		}
		else if (t == Token::integer)
		{
			return "Entero";
		}
		else if (t == Token::identifier)
		{
			return "Identificador";
		}
		else if (t >= Token::exclamation_mark and t <= Token::symbol_diagonal)
		{
			//char msg[] = {'?','\0'};
			//msg[0] = (char) t;
			return "Simbolo";
		}
		else if (t >= Token::symbol_column and t <= Token::arroba)
		{
			//char msg[] = {'?','\0'};
			//msg[0] = (char) t;
			return "Simbolo";
		}
		else if (t >= Token::curly_brackets_open and t <= Token::umlaut)
		{
			//char msg[] = {'?','\0'};
			//msg[0] = (char) t;
			return "Simbolo";
		}
		else if (t >= Token::brackets_open and t <= Token::guion_down)
		{
			//char msg[] = {'?','\0'};
			//msg[0] = (char) t;
			return "Simbolo";
		}

		return str;
	}


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

	typedef core_here::lex::TTA<char, Tokens, core_here::lex::State> TT_CC;
	class TTA : public TT_CC
	{
	private:
		const std::vector<char> digits = {'0','1','2','3','4','5','6','7','8','9'};
		const std::vector<char> lower = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
		const std::vector<char> upper = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
		const std::vector<char> graphic = { '!','"','#','%','\'','(',')','*','+',',','-','.','/',':',';','<','=','>','?','[','\\',']','^','_','{','|','}','~'};
		const std::vector<char> display = { '\a','\b','\f','\n','\r','\t','\v'};
		const std::vector<char> not_c = {' '};
		const int simbols_amount = 99;

	public:
		constexpr TTA()
		{
			create();
			make();
		}
		constexpr TTA(const TTA& obj) : TT_CC(obj)
		{
		}
		constexpr TTA(const TTA&& obj) : TT_CC(obj)
		{
		}

		constexpr void make()
		{
			_simbols.reserve(simbols_amount);
			for (char c : digits)
			{
				_simbols.push_back(c);
			}
			for (char c : lower)
			{
				_simbols.push_back(c);
			}
			for (char c : upper)
			{
				_simbols.push_back(c);
			}
			for (char c : graphic)
			{
				_simbols.push_back(c);
			}
			for (char c : display)
			{
				_simbols.push_back(c);
			}
			for (char c : not_c)
			{
				_simbols.push_back(c);
			}
			sort_symbols();

			std::vector<char> symbols_end_words(37);
			for (char c : graphic)
			{
				if(c == '_') continue;
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
			symbols_end_words.push_back('\0');

			for (const auto& p : keywords)
			{
				word(p.string,p.token, symbols_end_words,core_here::lex::Flag::error);
			}

			almost_one(digits, Tokens::integer, symbols_end_words,core_here::lex::Flag::error);

			std::vector<char> symbols_identifier_begin;
			symbols_identifier_begin.reserve(lower.size() + upper.size() + 1);
			for (char c : lower)
			{
				symbols_identifier_begin.push_back(c);
			}
			for (char c : upper)
			{
				symbols_identifier_begin.push_back(c);
			}
			symbols_identifier_begin.push_back('_');
			core_here::lex::State state_identifier = one(symbols_identifier_begin, Tokens::identifier, symbols_end_words,core_here::lex::Flag::only_free);
			std::vector<char> symbols_identifier;
			symbols_identifier.reserve(lower.size() + upper.size() + digits.size() + 1);
			for (char c : lower)
			{
				symbols_identifier.push_back(c);
			}
			for (char c : upper)
			{
				symbols_identifier.push_back(c);
			}
			for (char c : digits)
			{
				symbols_identifier.push_back(c);
			}
			symbols_identifier.push_back('_');
			some(symbols_identifier, Tokens::identifier, symbols_end_words,core_here::lex::Flag::join_same,state_identifier);

			/*for (char c : graphic)
			{
				if(c == '_') continue;
				one(c, (Tokens)c, symbols_end_words, core_here::lex::Flag::error);
			}*/

			/*for (char c : display)
			{
				one(c, (Tokens)c, symbols_end_words, core_here::lex::Flag::error);
			}*/
		}


	private:

	};


	constexpr auto create_lexer_a()
	{
		TTA tt;
		return tt;
	}


	constexpr size_t amount_symbols = 99;
	constexpr size_t amount_transitions = 128;
	constexpr size_t amount_states = 300;
	constexpr size_t amount_end_word = 37;
	constexpr size_t amount_keywords = 32;
	typedef core_here::lex::TTB<char,Tokens,core_here::lex::State,amount_states,amount_transitions,amount_symbols> TTB_BASE;
	class TTB : public TTB_BASE
	{
	public:
		constexpr static core_here::lex::pair_keyword<char, Tokens> keywords[32] = {
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
	constexpr static size_t amount_graphic = 29;
	constexpr static size_t amount_display = 7;
	constexpr static size_t amount_digits = 10;
	constexpr static size_t amount_identifier_begin = 53;
	constexpr static size_t amount_identifier = 63;

	public:
		constexpr TTB()
		{
			make_symbols();
			make_transitions();
		}

		core_here::lex::State get_state_last()const
		{
            return state_last;
		}
	private:
		constexpr void make_symbols()
		{
			symbols[0] = '\a';
			symbols[1] = '\b';
			symbols[2] = '\f';
			symbols[3] = '\n';
			symbols[4] = '\r';
			symbols[5] = '\t';
			symbols[6] = '\v';
			size_t position = 7;
			for(size_t i = ' '; i < '$'; i++,position++)
			{
				symbols[position] = i;
			}
			for(size_t i = '%'; i < '0'; i++,position++)
			{
				symbols[position] = i;
			}
			//digitos
			for(size_t i = '0'; i < ':'; i++,position++)
			{
				symbols[position] = i;
			}
			for(size_t i = ':'; i < '@'; i++,position++)
			{
				symbols[position] = i;
			}
			for(size_t i = 'A'; i < '['; i++,position++)
			{
				symbols[position] = i;
			}
			for(size_t i = '['; i < 96; i++,position++)
			{
				symbols[position] = i;
			}
			for(size_t i = 'a'; i < '{'; i++,position++)
			{
				symbols[position] = i;
			}
			for(size_t i = '{'; i < 127; i++,position++)
			{
				symbols[position] = i;
			}
			if(position != amount_symbols)
			{
				error = core_here::lex::errors::fail_create_symbols;
				return;
			}

			symbols_end_words[0] = '\a';
			symbols_end_words[1] = '\b';
			symbols_end_words[2] = '\f';
			symbols_end_words[3] = '\n';
			symbols_end_words[4] = '\r';
			symbols_end_words[5] = '\t';
			symbols_end_words[6] = '\v';
			position = 7;
			for(size_t i = ' '; i < '$'; i++,position++)
			{
				symbols_end_words[position] = i;
			}
			for(size_t i = '%'; i < '0'; i++,position++)
			{
				symbols_end_words[position] = i;
			}
			for(size_t i = ':'; i < '@'; i++,position++)
			{
				symbols_end_words[position] = i;
			}
			for(size_t i = '['; i < 96; i++,position++)
			{
				symbols_end_words[position] = i;
			}
			for(size_t i = '{'; i < 127; i++,position++)
			{
				symbols_end_words[position] = i;
			}
			if(position != amount_end_word)
			{
				error = core_here::lex::errors::fail_create_end_word;
				return;
			}

			position = 0;
			for(size_t i = '!'; i < '$'; i++,position++)
			{
				symbols_graphic[position] = i;
			}
			for(size_t i = '%'; i < '0'; i++,position++)
			{
				symbols_graphic[position] = i;
			}
			for(size_t i = ':'; i < '@'; i++,position++)
			{
				symbols_graphic[position] = i;
			}
			for(size_t i = '['; i < 96; i++,position++)
			{
				symbols_graphic[position] = i;
			}
			for(size_t i = '{'; i < 127; i++,position++)
			{
				symbols_graphic[position] = i;
			}
			if(position != amount_graphic)
			{
				error = core_here::lex::errors::fail_create_graphic_symbols;
				return;
			}

			symbols_display[0] = '\a';
			symbols_display[1] = '\b';
			symbols_display[2] = '\f';
			symbols_display[3] = '\n';
			symbols_display[4] = '\r';
			symbols_display[5] = '\t';
			symbols_display[6] = '\v';

			symbols_digits[0] = '0';
			symbols_digits[1] = '1';
			symbols_digits[2] = '2';
			symbols_digits[3] = '3';
			symbols_digits[4] = '4';
			symbols_digits[5] = '5';
			symbols_digits[6] = '6';
			symbols_digits[7] = '7';
			symbols_digits[8] = '8';
			symbols_digits[9] = '9';

			position = 0;
			for(size_t i = 'A'; i < '['; i++,position++)
			{
				symbols_identifier_begin[position] = i;
			}
			for(size_t i = 'a'; i < '{'; i++,position++)
			{
				symbols_identifier_begin[position] = i;
			}
			symbols_identifier_begin[52] = '_';
			if(position + 1 != amount_identifier_begin)
			{
				error = core_here::lex::errors::fail_create_identifier_begin;
				return;
			}

			position = 0;
			for(size_t i = 'A'; i < '['; i++,position++)
			{
				symbols_identifier[position] = i;
			}
			for(size_t i = 'a'; i < '{'; i++,position++)
			{
				symbols_identifier[position] = i;
			}
			for(size_t i = '0'; i < ':'; i++,position++)
			{
				symbols_identifier[position] = i;
			}
			symbols_identifier[62] = '_';
			if(position + 1 != amount_identifier)
			{
				error = core_here::lex::errors::fail_create_identifier;
				return;
			}
		}
		constexpr void make_transitions()
		{
			state_last = create();
			if(state_last != 0)
			{
				error = core_here::lex::errors::fail_create_firts_estate;
				return;
			}
			for (size_t i = 0 ; i < amount_keywords; i++)
			{
				state_last = word(keywords[i].string,keywords[i].token, symbols_end_words,amount_end_word,core_here::lex::Flag::error);
                if(state_last < 0) return;
			}

			state_last = almost_one(symbols_digits,amount_digits, Tokens::integer, symbols_end_words,amount_end_word,core_here::lex::Flag::error);
			if(state_last < 0) return;

			state_last = one(symbols_identifier_begin,amount_identifier_begin, Tokens::identifier, symbols_end_words,amount_end_word,core_here::lex::Flag::only_free);
            if(state_last < 0) return;

            state_last = some(symbols_identifier,amount_identifier, Tokens::identifier, symbols_end_words,amount_end_word,core_here::lex::Flag::join_same,state_last);
            if(state_last < 0) return;

			/*
			for (size_t i = 0 ; i < amount_graphic; i++)
			{
				if(symbols_graphic[i] == '_') continue;
				state_last = one(symbols_graphic[i], (Tokens)symbols_graphic[i], symbols_end_words, amount_end_word, core_here::lex::Flag::error);
				if(state_last < 0) return;
			}
			*/
			/*
			for (size_t i = 0 ; i < amount_display; i++)
			{
				if(symbols_display[i] == '_') continue;
				one(symbols_display[i], (Tokens)symbols_display[i], symbols_end_words, amount_end_word, core_here::lex::Flag::error);
			}
			*/
		}


	private:
        core_here::lex::State state_last;
		char symbols_end_words[amount_end_word];
		char symbols_graphic[amount_graphic];
		char symbols_display[amount_display];
		char symbols_digits[amount_digits];
		char symbols_identifier_begin[amount_identifier_begin];
		char symbols_identifier[amount_identifier];
	};

	constexpr auto create_lexer_b()
	{
		TTB ttb;

		return ttb;
	}

}
