

#ifndef OCTETOS_CORE_LEXER_V3_HH
#define OCTETOS_CORE_LEXER_V3_HH



/**
 *
 *  This file is part of octetos-core.
 *  octetos-core is a core C/C++ Octeto's library.
 *  Copyright (C) 2018  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#include <cstddef>
#include <array>
#include <string>
#include <list>
#include <algorithm>
#include <initializer_list>
#include <iterator>

#include "core.hh"
#include "Buffer-v3.hh"

namespace oct::core::v3::lex
{
typedef int State;
typedef size_t Index;

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
	digit_0		= 48,
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
	char_A		= 65,
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
	char_a		=	97,
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

	EuroSign	= 218,
	//>>>Extended ASCII






	y_Diaeresis = 255,//ÿ
	//>>>UTF-8
	a_Macron	= 256,

	s_Coptic	= 999,
	//Inicode >>>


	//>>>Tokens
	base	= 0x110000,


};

template<typename Token> std::string to_string(Token t)
{
	std::string str;

	if (t <= Token::US)
	{
		return "control char";
	}
	else if (t >= Token::digit_0 or t <= Token::digit_9)
	{
		std::string str_token(0,char(t));
		str = "Digito '" + str_token + "'";
		return str;
	}
	else if (t >= Token::char_A or t <= Token::char_Z)
	{
		std::string str_token(0,char(t));
		str = "Letra '" + str_token + "'";
		return str;
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


template<typename C> bool equal(const C* initial, const C* target)
{
	size_t lengInitial = length(initial);
	if(lengInitial == 0) return false;
	//if(initial[lengInitial] != '\0') return false;

	size_t lengTarget = length(target);
	if(lengTarget == 0) return false;
	//if(target[lengTarget] != '\0') return false;

	if(lengInitial != lengTarget) return false;

	for(size_t i = 0; i < lengInitial; i++)
	{
		if(initial[i] != target[i]) return false;
	}

	return true;
}

enum class Indicator : State
{
	none,//no es us estado determinado, sin mebago, no cambia el estado previo por lo que se podria decir no no tiene efecto en el estado
	accept,//estado de aceptacion, sin embargo deve terminar de inmediato
	acceptable,//equivalente a none, sin embargo, puede equvaler a acepted en cietas circunstacion
	reject,//rechazar y terminar de imendiato
	rejectable,//equivalente a none, sin embargo, puede equvaler a rejet en cietas circunstacion
	prefix,//prefijo de analisis, un vez establecido es valido hasta encontrar el proximo accept, no sera en otro caso valido.
	error,//el simbolo no se esperaba
	unknow,//simbolo que no pertenece al lenguaje
};
const char* to_string(Indicator i)
{
	switch(i)
	{
		case Indicator::none: return "none";
		case Indicator::acceptable: return "acceptable";
		case Indicator::accept: return "accept";
		case Indicator::reject: return "reject";
		case Indicator::rejectable: return "rejectable";
		case Indicator::prefix: return "prefix";
		case Indicator::error: return "error";
		case Indicator::unknow: return "unknow";
	}

	return "Unknow";
}

	template<typename Token,typename State/*Status*/>
	struct Transition
	{
		Indicator indicator;
		State next;
		Token token;

		constexpr Transition() : indicator(Indicator::none),next(-1), token(Token::none)
		{
		}

	};

	template<typename Symbol, typename Token>
	struct pair_keyword
	{
		const Symbol* string;
		Token token;
	};

	/*
	*\brief Para indicar a la clase TT la decicion que deve tomar en caso de conflictos al momente de crear transisiones
	*/
	enum class Flag
	{
		none,
		error,
		extend,//busca entre las posibles transiciones posibles conbionacioness
		only_free,//solo operara sobre las transisciones libres
		join_same,//realiza la operacion, pero reultilizara el o los estados posbles para el token inidcado
	};

	enum errors
	{
		none,
		fail_create_firts_estate,
		fail_on_word_not_symbol,
		fail_on_word_null_transition,
		fail_on_used_null_transition,
		fail_on_create_no_memory,
		fail_on_word_used_transition,
		fail_on_one_not_symbol,
		fail_on_one_used_transition,
		fail_create_graphic_symbols,
		fail_create_symbols,
		fail_create_end_word,
		fail_on_one_empty,
		fail_create_identifier_begin,
        fail_create_identifier,
        fail_on_prefixing_conflict,

	};
	const char* to_string(errors e)
	{
		switch(e)
		{
			case errors::none: return "Ninguno";
			case errors::fail_create_firts_estate: return "Fallo en el contructor al create el estado inical";
			case errors::fail_on_word_not_symbol: return "Fallo en la funcion word, en encontro un simbolo que no pertenece al lenguaje";
			case errors::fail_on_word_null_transition: return "Se returno una transicion nula(word), muy probablement devido a indices fuera de rango";
			case errors::fail_on_used_null_transition: return "Se returno una transicion nula(is_used), muy probablement devido a indices fuera de rango";
			case errors::fail_on_create_no_memory: return "No hay memori disponible en para crear mas estados";
			case errors::fail_on_word_used_transition: return "En la fuoncion one, la tranciones esta ocuada(is_used)";
			case errors::fail_on_one_not_symbol: return "Fallo en la funcion one, en encontro un simbolo que no pertenece al lenguaje";
			case errors::fail_on_one_used_transition: return "En la funcion one, la tranciones esta ocupada(is_used)";
			case errors::fail_create_graphic_symbols: return "En la funcion c90::TT::make_symbols, fallo al crear los simbolos 'graphic'";
			case errors::fail_create_symbols: return "En la funcion c90::TT::make_symbols, fallo al crear los simbolos del lenguaje";
			case errors::fail_create_end_word: return "En la funcion c90::TT::make_symbols, fallo al crear los simbolos de 'palabra final '";
			case errors::fail_on_one_empty: return "En la funcion c90::TT::one, Entrada vacia";
			case errors::fail_create_identifier_begin: return "En la funcion c90::TT::make_symbols, al crear los simbolos inicio de identificador";
			case errors::fail_create_identifier: return "En la funcion c90::TT::make_symbols, al crear los simbolos de identificador";
			case errors::fail_on_prefixing_conflict: return "En la funion, prefixig, se tecto cofilicto en los prefijos";
		}

		return "Error desconocido";
	}


	template<typename Symbol /*Input*/, typename Token>
	struct Tokenized
	{
		const Symbol* base;
		size_t length;
		Token token;

		operator std::string()const
		{
			std::string str;
			str.insert(0, base, length);
			return str;
		}
	};

template<typename Symbol /*Input*/,typename Token,typename State/*State*/,typename TT>
class Lexer
{
public:

public:
	Lexer(const TT& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),index(0),actual_status(0),initial_status(0)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
		_echo = false;
#endif
	}

    Token next()
	{
        actual_status = initial_status;
		actual_transition = NULL;
		prev_transition = NULL;
		token_start = index;
		token_end = 0;
		prefix_transition = NULL;
		acceptable_transition = NULL;
		bool prefix_ended = false;
		bool acceptable_ended = false;
	    const Symbol* buff = (const Symbol*)*buffer;
		prefix_start = 0;

        while(index < buffer->size() and (size_t)actual_status < table->size())
        {
            //std::cout << "whiel : Step 0\n";


            //std::cout << "whiel : Step 1\n";
            //>>>reading data
            {
                input = buff[index];
                actual_transition = table->get(actual_status,input);
                next_status = actual_transition->next;

				//--prefix-->accept|reject
				if (actual_transition->indicator == Indicator::prefix)
				{
					prefix_transition = actual_transition;
					prefix_start = index;
				}
				else if (actual_transition->indicator == Indicator::accept) prefix_ended = true;
				else if (actual_transition->indicator == Indicator::reject) prefix_ended = true;

				//--acceptable-->accept|reject
				/*if (actual_transition->indicator == Indicator::acceptable and not acceptable_ended)
				{
					acceptable_transition = actual_transition;
				}
				else if (actual_transition->indicator == Indicator::accept) acceptable_ended = true;
				else if (actual_transition->indicator == Indicator::reject) acceptable_ended = true;*/
				//>>>

				//--acceptable-->acceptable|accept
				if (actual_transition->indicator == Indicator::acceptable and not acceptable_ended)
				{
					acceptable_transition = actual_transition;
				}
				else if (actual_transition->indicator == Indicator::accept) acceptable_ended = true;
				else if (actual_transition->indicator == Indicator::reject) acceptable_ended = true;
				//>>>

			}

            //std::cout << "whiel : Step 2\n";
            //>>>working
            {
				//std::cout << "Input : '" << int(input) << "'\n";
				//std::cout << "Input : '" << int('\n') << "'\n";
				if (input == '\f') std::cout << "-" << actual_status << "--'new page'->" << next_status << "\n";
				else if (input == '\n') std::cout << "-" << actual_status << "--'new line'->" << next_status << "\n";
				else if (input == '\r') std::cout << "-" << actual_status << "--'carrier return'->" << next_status << "\n";
				else std::cout << "-" << actual_status << "--'" << input << "'->"  << next_status << "\n";
				/*std::cout << "Index : '" << index << "'\n"; */

				//>>>

            }

            //std::cout << "whiel : Step 3\n";
            //>>>finalizing
            {
				//verificando terminacion
				bool terminate_and_advance = false;
				if (acceptable_transition and acceptable_ended)
				{
					//std::cout << "terminating ...by prefix\n";
					token_end = index - 1;
					break;
				}
				else if (prefix_transition and prefix_ended)
				{
					//std::cout << "terminating ...by prefix\n";
					index = prefix_start;
					break;
				}
				else if (actual_transition->indicator == Indicator::accept)
				{
					//std::cout << "terminating ...\n";
					token_end = index - 1;
					break;
				}
				else if (actual_transition->indicator == Indicator::unknow) terminate_and_advance = true;
				else if (actual_transition->indicator == Indicator::error) terminate_and_advance = true;
				else if (actual_transition->next < 0) terminate_and_advance = true;
				if (terminate_and_advance)
				{
					index++;
					token_end = index;
					//std::cout << "terminating ...\n";
					break;
				}
            }

			//repetir loop
			{
				index++;
				token_end = index;
				actual_status = next_status;
				prev_transition = actual_transition;

			}
        }
#ifdef OCTETOS_CORE_ENABLE_DEV
#endif
		if (not actual_transition)
		{
			//std::cout << "terminating ...\n";
			return Token::none;
		}
		else if (actual_transition->indicator == Indicator::acceptable and index == buffer->size())
		{
			return actual_transition->token;
		}
		else if (acceptable_transition and acceptable_ended)
		{
			return actual_transition->token;
		}
		else if (actual_transition->indicator == Indicator::accept)
		{
			return actual_transition->token;
		}
		else if (prefix_transition and prefix_ended)
		{
			index = index - prefix_start + 1;
			return actual_transition->token;
		}
		else if (actual_transition->indicator == Indicator::error)
		{
			return (Token)input;
		}
		else if (actual_transition->indicator == Indicator::unknow)
		{
			return (Token)input;
		}
		else if(actual_transition->next < 0)
		{
			return (Token)input;
		}
		else
		{//fin de la entreada?
			if (index == buffer->size())
			{
				if (actual_transition->indicator == Indicator::accept)
				{
					return actual_transition->token;
				}
				else if (actual_transition->indicator == Indicator::acceptable)
				{
					return actual_transition->token;
				}

				return (Token)input;//se retorna el ultomo token
			}
		}

		return Token::eoi;
	}

	Token next(Tokenized<Symbol,Token>& content)
	{
		Token token = next();
		if (token <= Token::none) return token;
		if (token_start >= token_end) return token;

		content.base = (const Symbol*)*buffer;
		content.base += token_start;
		content.length = token_end - token_start;
		content.token = token;

		return token;
	}
#ifdef OCTETOS_CORE_ENABLE_DEV
	void echo(bool e)
	{
		_echo = e;
	}
#endif

private:


private:
	const TT* table;
	Buffer<Symbol>* buffer;
	Symbol input;
	size_t index,token_start,token_end;//prefix_index
    const Transition<Token, State> *actual_transition, *prev_transition, *prefix_transition, *acceptable_transition;
	State actual_status,next_status;//numero del estado actual del automata
    const State initial_status;
    bool prefix_start;
#ifdef OCTETOS_CORE_ENABLE_DEV
	bool _echo;
#endif

};

}


#endif
