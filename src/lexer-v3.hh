

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

#include "Buffer-v3.hh"

namespace oct::core::v3::lex
{
typedef int State;
typedef int Token;
typedef size_t Index;
static const unsigned char ASCII_LENGTH = 128;

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
	tokens	= 0x110000,
	number,
		integer,
		decimal,//incluye punto flotante
		digit,//cararte digito
	string,
		letter,//caracter
	identifier,
	keyword,
	softword,
	expresion,

};

const char* to_string(Tokens t)
{
	switch (t)
	{
	case Tokens::none:
		return "none";
	case Tokens::space:
		return "' '";
	case Tokens::plus:
		return "'+'";
	case Tokens::minus:
		return "'-'";
	case Tokens::dot:
		return "'.'";


	case Tokens::number:
		return "number";
	case Tokens::integer:
		return "integer";
	case Tokens::decimal:
		return "decimal";
	case Tokens::letter:
		return "letter";
	case Tokens::string:
		return "string";
	case Tokens::identifier:
		return "identifier";
	case Tokens::softword:
		return "softword";
	case Tokens::expresion:
		return "expresion";
	}

	return NULL;
}

template<typename C> bool is_whitespace(C c)
{
	switch(c)
	{
		case ' ':
		case '\t':
		case '\n':
			return true;
		default :
			return false;
	}
	return false;
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
	//finalized,
	error,//el simbolo no se esperaba
	unknow,//simbolo que no pertenece al lenguaje
	//terminate,//terminar de enmediato, sin embargo no tienne efecto en el estado actual del automamta(podria decirse qu es lo mismo que el buffer se termine),acceptable --> terminate, rejectable --> terminate
};
const char* to_string(Indicator i)
{
	switch(i)
	{
		case Indicator::none: return "none";
		//case Indicator::acceptable: return "acceptable";
		case Indicator::accept: return "accept";
		case Indicator::reject: return "reject";
		//case Indicator::rejectable: return "rejectable";
		case Indicator::prefix: return "prefix";
		case Indicator::error: return "error";
		case Indicator::unknow: return "unknow";
		//case Indicator::terminate: return "terminate";
	}

	return "Unknow";
}

	template<typename Token,typename State/*Status*/>
	struct Transition
	{
		Indicator indicator;
		State next;
		Token token;
		bool seted;

		Transition() : indicator(Indicator::unknow),next(-1), token(Token::none), seted(false)
		{
		}
		Transition(const Transition& obj) = default;

		/*
		const Transition& operator =(const Transition& obj)
		{
			indicator = obj.indicator;
			next = obj.next;
			token = obj.token;
			seted = obj.seted;

			return *this;
		}
		*/

		void print(std::ostream& out) const
		{
			out << next << " - ";
			std::string strtoken = std::to_string((int)token);
			out << strtoken << " - ";
			out << to_string(indicator);
		}
	};

	template<typename Symbol, typename Token>
	struct pair_keyword
	{
		const Symbol* string;
		Token token;
	};

	template<typename Symbol /*Input*/,typename Token,typename State/*Status*/>
	class TT : public std::vector<std::vector<Transition<Token, State>>>
	{
	public:
		typedef std::vector<Transition<Token, State>> TT_SYMBOLS;
		typedef std::vector<TT_SYMBOLS> TT_BASE;
		static const State EMPTY_STATE = -1;
		static const State EMPTY_INPUT = -2;
		static const State USED = -3;

		static constexpr  unsigned int length_transition()
		{
			//if (typeid(Symbol) == typeid(char)) return 128;//ascci table
			
			return 128;
		}
		constexpr State create(size_t to_add = 1)
		{
			size_t size_inital = TT_BASE::size();
			TT_BASE::resize(size_inital + to_add);
			if (TT_BASE::size() != size_inital + to_add) exception("El tamaño del contenedor no es el adecuado.");
			size_t size_post = TT_BASE::size();
			size_t base_post = size_inital > 0 ? size_inital - 1 : 0;
			//static_assert(TT_BASE::capacity() == to_add, "El contenedor no se ajusto al tamanp requerido");
			for (size_t i = base_post; i < size_post; i++)
			{
				TT_BASE::at(i).resize(length_transition());
				//initial(i);
			}

			return State(TT_BASE::size() - 1);
		}

	public:
		constexpr TT(const std::vector<Symbol>& ss) : _simbols(ss)
		{
			std::sort(_simbols.begin(), _simbols.end(), [](int a, int b)
				{
					return a < b;
				});
			State inital_state = create();
		}
		constexpr TT(const TT& tt) : TT_BASE(tt), _simbols(tt._simbols)
		{
			TT_BASE::resize(tt.size());
			for (size_t s = 0; s < tt.size(); s++)
			{
				TT_BASE::at(s).resize(tt.size());
				for (size_t t = 0; t < tt.at(s).size(); t++)
				{
					TT_BASE::at(s)[t] = tt.at(s)[t];
				}
			}
		}

		/*constexpr bool initial(State status)
		{
			for(size_t i = 0; i < length_transition(); i++)
			{
				//std::cout << "initial : " << status << " - " << i << "\n";
				TT_BASE::at(status)[i].next = -1;
				TT_BASE::at(status)[i].token = Token::none;
				TT_BASE::at(status)[i].indicator = Indicator::unknow;
				TT_BASE::at(status)[i].seted = false;
			}
			return true;
		}*/
		
		constexpr const std::vector<Symbol>& simbols() const
		{
			return _simbols;
		}

		int check(std::ostream& out, Indicator indicator = Indicator::unknow, State state = initial_state) const
		{
			if (state < 0) return 0;
			if (state >= TT_BASE::size()) return 0;//caso base

			int erros = 0;

			for (Symbol s = 0; s < TT_BASE::at(state).size(); s++)//cheking para cada simbolo en el estado actual
			{
				if (indicator == Indicator::none)
				{
					if (TT_BASE::at(state)[s].indicator == Indicator::none)
					{
					}
					else if (TT_BASE::at(state)[s].indicator == Indicator::prefix)
					{
					}
					else if (TT_BASE::at(state)[s].indicator == Indicator::accept)
					{
					}
					else
					{
						out << state << ":" << Symbol(s) << " - " << "Unavez que se estable un estado como inidicador none, los estados posteriores solo puede ser, none, prefix, acceptable, accept\n";
						erros++;
					}
				}
				else if (indicator == Indicator::prefix)
				{
					if (TT_BASE::at(state)[s].indicator == Indicator::none)
					{
					}
					else if (TT_BASE::at(state)[s].indicator == Indicator::accept)
					{
					}
					else if (TT_BASE::at(state)[s].indicator == Indicator::reject)
					{
					}
					else
					{
						out << state << ":" << Symbol(s) << " - " << "Unavez que se estable un estado como inidicador prefix, los estados posteriores none, acceptable, accept\n";
						erros++;
					}
				}
				if (state == TT_BASE::at(state)[s].next) return 0;
				erros += check(out, TT_BASE::at(state)[s].indicator, TT_BASE::at(state)[s].next);
			}


			return erros;
		}

		void print(std::ostream & out, State state = initial_state)
		{
			if (state > TT_BASE::size() - 1) return;//caso base

			for (Symbol s = 0; s < TT_BASE::at(state).size(); s++)
			{
				if (TT_BASE::at(state)[s].next >= 0)
				{
					if (state == initial_state) out << "|-";
					else out << "\t|-";
					if(s <= Symbol(Token::US)) out << state << "--control char-->" << TT_BASE::at(state)[s].next << " ";
					else out << state << "--'" << s << "'-->" << TT_BASE::at(state)[s].next << " ";
					out << to_string(TT_BASE::at(state)[s].indicator) << " ";
					if(TT_BASE::at(state)[s].token > Token::none) out << std::to_string((int)TT_BASE::at(state)[s].token) << " ";
					out << "\n";
					if (TT_BASE::at(state)[s].next >= 0) 
					{
						if (TT_BASE::at(state)[s].next == state) 
						{
							out << "\t|->*\n";
							return;
						}
						else if (TT_BASE::at(state)[s].next > initial_state)
						{
							print(out, TT_BASE::at(state)[s].next);
						}
					}
				}
			}
		}

		
		constexpr State word(const char* str, Token token, const std::vector<Symbol>& prefixs)
		{
			size_t sz_str = std::strlen(str);
			if (sz_str == 0) return EMPTY_INPUT;
			State state_current = initial_state, state_max = initial_state;
			Symbol input;
			for (size_t i = 0; i < sz_str; i++)//reading char by char..
			{
				input = str[i];
				if (TT_BASE::at(state_current)[input].seted)
				{
					state_current = TT_BASE::at(state_current)[input].next;
					continue;
				}
				else
				{
					TT_BASE::at(state_current)[input].seted = true;
					TT_BASE::at(state_current)[input].indicator = Indicator::none;
					if (i + 1 < sz_str)//si hay mas texto que leer de la palabra
					{
						state_max = create();
						TT_BASE::at(state_current)[input].next = state_max;
						state_current = state_max;
					}
				}
			}
			state_max = create();
			TT_BASE::at(state_current)[input].next = state_max;
			for (size_t k = 0; k < length_transition(); k++)
			{
				if (std::find(prefixs.begin(), prefixs.end(), Symbol(k)) == prefixs.end()) continue;

				TT_BASE::at(state_max)[k].next = 0;
				TT_BASE::at(state_max)[k].token = token;
				TT_BASE::at(state_max)[k].indicator = Indicator::accept;
				TT_BASE::at(state_max)[k].seted = true;
			}

			return state_max;
		}

		constexpr State repeat(State state_current,Symbol input, Token token, const std::vector<Symbol>& prefixs)
		{
		}
		constexpr State almost_one(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs)
		{
			State state_current = initial_state, state_max = initial_state;
			if (simbols.empty()) return EMPTY_INPUT;
			Symbol input;

			//verificacion
			for (size_t i = 0; i < simbols.size(); i++)//reading char by char..
			{
				input = simbols[i];
				if (TT_BASE::at(state_current)[input].next >= 0) return USED;
			}

			//
			state_max = create();
			for (size_t i = 0; i < simbols.size(); i++)//reading char by char..
			{
				input = simbols[i];
				TT_BASE::at(state_current)[input].next = state_max;
				TT_BASE::at(state_current)[input].indicator = Indicator::acceptable;
				TT_BASE::at(state_current)[input].token = token;
			}
			for (size_t i = 0; i < simbols.size(); i++)//reading char by char..
			{
				input = simbols[i];
				TT_BASE::at(state_max)[input].next = state_max;
				TT_BASE::at(state_max)[input].indicator = Indicator::acceptable;
				TT_BASE::at(state_max)[input].token = token;
			}

			return state_max;
		}


	private:
		
	private:
		std::vector<Symbol> _simbols;
		static const State initial_state = 0;
	};

	template<typename Symbol /*Input*/>
	struct TokenDefinition
	{
		const Symbol* base;
		size_t length;

		void load(std::string& str) const
		{
			str.insert(0, base, length);
		}
	};

/**
*\brief DFA type A
*
*/
template<typename Symbol /*Input*/,typename Token,typename State/*State*/>
class A
{
public:

public:
	A(const TT<Symbol,Token, State>& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),actual_state(false),index(0),actual_status(0),initial_status(0)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
		_echo = false;
#endif
	}

    Token next()
	{
        actual_status = initial_status;
        actual_state = false;
		actual_transition = NULL;
		prev_transition = NULL;
		token_start = index;
		token_end = 0;
		prefix_transition = NULL;
		bool prefix_ended = false;
	    const Symbol* buff = (const Symbol*)*buffer;
		prefix_start = 0;

        while(index < buffer->size() and actual_status < table->size())
        {
            //std::cout << "whiel : Step 0\n";


            //std::cout << "whiel : Step 1\n";
            //>>>reading data
            {
                input = buff[index];
                actual_transition = (const Transition<Token, State>*) &(table->at(actual_status).at(input));
                next_status = actual_transition->next;

				//--prefix-->accept|reject
				if (actual_transition->indicator == Indicator::prefix)
				{
					prefix_transition = actual_transition;
					prefix_start = index;
					//std::cout << "iniciando ...by prefix\n"; 
					//actual_transition->print(std::cout);
					//std::cout << "\n";
				}
				else if (actual_transition->indicator == Indicator::accept) prefix_ended = true;
				else if (actual_transition->indicator == Indicator::reject) prefix_ended = true;

				//>>>

			}

            //std::cout << "whiel : Step 2\n";
            //>>>working
            {
				//std::cout << "Input : '" << int(input) << "'\n";
				//std::cout << "Input : '" << int('\n') << "'\n";
				/*if (input == '\f') std::cout << "-" << actual_status << "--'new page'->" << next_status << "\n";
				else if (input == '\n') std::cout << "-" << actual_status << "--'new line'->" << next_status << "\n";
				else if (input == '\r') std::cout << "-" << actual_status << "--'carrier return'->" << next_status << "\n";
				else std::cout << "-" << actual_status << "--'" << input << "'->"  << next_status << "\n";*/
				/*std::cout << "Index : '" << index << "'\n"; */
				
				//>>>

            }

            //std::cout << "whiel : Step 3\n";
            //>>>finalizing
            {
				//verificando terminacion
				bool terminate_and_advance = false;
				if (prefix_transition and prefix_ended)
				{
					//std::cout << "terminating ...by prefix\n";
					index = prefix_start;
					break;
				}
				else if (actual_transition->indicator == Indicator::accept)
				{
					//std::cout << "terminating ...\n";
					break;
				}
				else if (actual_transition->indicator == Indicator::unknow) terminate_and_advance = true;
				else if (actual_transition->indicator == Indicator::error) terminate_and_advance = true;
				else if (actual_transition->indicator == Indicator::reject) terminate_and_advance = true;
				if (terminate_and_advance)
				{
					index++;
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
		/*
		if (actual_state == Indicator::accept)
		{
			std::cout << "Acepted\n";
		}
		else if (actual_state == Indicator::reject)
		{
			std::cout << "Rejected\n";
		}
		else
		{

		}
		*/
#endif
		if (actual_transition->indicator == Indicator::accept)
		{
			actual_state = true;
			return actual_transition->token;
		}
		else if (prefix_transition and prefix_ended)
		{
			//std::cout << "Return token : ";
			//prefix_transition->print(std::cout);
			//std::cout << "\n";
			//std::cout << "Input : '" << input << "'\n";
			//std::cout << "Index : '" << index << "'\n";
			//std::cout << "Token : '" << int(prefix_transition->token) << "'\n";
			actual_state = true;
			index = index - prefix_start + 1;
			return actual_transition->token;
		}
		else if (actual_transition->indicator == Indicator::error)
		{
			actual_state = false;
			return (Token)input;
		}
		else if (actual_transition->indicator == Indicator::unknow)
		{
			actual_state = false;
			return (Token)input;
		}
		else if (actual_transition->indicator == Indicator::reject)
		{
			actual_state = false;
			return (Token)input;
		}
		else
		{//fin de la entreada?
			if (index == buffer->size())
			{
				if (actual_transition->indicator == Indicator::accept)
				{
					actual_state = true;
					return actual_transition->token;
				}
				else if (actual_transition->indicator == Indicator::acceptable)
				{
					actual_state = true;
					return actual_transition->token;
				}

				actual_state = false;
				return (Token)input;//se retorna el ultomo token
			}
		}

		return Token::eoi;
	}
	Tokens next(TokenDefinition<Symbol>& content)
	{
		Tokens token = next();
		if (token <= Tokens::none) return token;
		if (token_start >= token_end) return token;

		content.base = (const Symbol*)*buffer;
		content.base += token_start;
		content.length = token_end - token_start;

		return token;
	}
	bool next(const Symbol* str)
	{
		size_t leng = strlen(str);
		const Symbol* buf = (const Symbol*)*buffer;
		buf += index;
		if (strncmp(buf, str, leng) == 0)
		{
			actual_state = true;
			index += leng;
			return true;
		}
		else
		{
			actual_state = false;
			return false;
		}
	}
	bool next(Symbol s)
	{
		const Symbol* buf = (const Symbol*)*buffer;
		buf += index;
		if (buf[0] == s)
		{
			actual_state = true;
			index++;
			return true;
		}
		else
		{
			actual_state = false;
			return false;
		}
	}
#ifdef OCTETOS_CORE_ENABLE_DEV
	void echo(bool e)
	{
		_echo = e;
	}
#endif
	bool is_accepted() const
	{
		return actual_state;
	}
	Indicator get_indicator () const
	{
		return actual_transition ? actual_transition->indicator : Indicator::none;
	}
private:


private:
	const TT<Symbol,Token, State>* table;
	Buffer<Symbol>* buffer;
	Symbol input;
	bool actual_state;//estado del automata actual
	size_t index,token_start,token_end;//prefix_index
    const Transition<Token, State> *actual_transition, *prev_transition, *prefix_transition;
	State actual_status,next_status;//numero del estado actual del automata
    const State initial_status;
    bool prefix_start;
#ifdef OCTETOS_CORE_ENABLE_DEV
	bool _echo;
#endif

};







template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/>
class B
{
public:
	B()
	{

	}

private:
	Status actual;
};


}


#endif
