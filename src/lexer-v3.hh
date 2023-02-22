

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

	template<typename Symbol,typename Token,typename State>
	class TTA : private std::vector<std::vector<Transition<Token, State>>>
	{
	public:
		typedef std::vector<Transition<Token, State>> TT_SYMBOLS;
		typedef std::vector<TT_SYMBOLS> TT_BASE;
		static const State EMPTY_STATE = -1;
		static const State EMPTY_INPUT = -2;
		static const State USED = -3;
		static const State AMBIGUOS = -4;
		static const State NOT_SYMBOL = -5;
		//static const State EMPTY_TRANSITION = -6;

		static constexpr  unsigned int length_transition()
		{
			//if (typeid(Symbol) == typeid(char)) return 128;//ascci table
			return 128;
		}
		constexpr State create()
		{
			TT_BASE::resize(TT_BASE::size() + 1);
			TT_BASE::at(TT_BASE::size() - 1).resize(length_transition());
			return State(TT_BASE::size() - 1);
		}
		constexpr State create(size_t to_add)
		{
			size_t size_inital = TT_BASE::size();
			TT_BASE::resize(size_inital + to_add);
			if (TT_BASE::size() != size_inital + to_add) exception("El tamaño del contenedor no es el adecuado.");
			size_t size_post = TT_BASE::size();
			size_t base_post = size_inital > 0 ? size_inital - 1 : 0;
			for (size_t i = base_post; i < size_post; i++)
			{
				TT_BASE::at(i).resize(length_transition());
			}

			return State(TT_BASE::size() - 1);
		}

	public:
	    constexpr TTA() = default;
		constexpr TTA(const std::vector<Symbol>& ss) : _simbols(ss)
		{
			sort_symbols();
			State inital_state = create();
		}

		constexpr TTA(const TTA& tt) : TT_BASE(tt), _simbols(tt._simbols)
		{
		}

		constexpr TTA(const TTA&& tt) : TT_BASE(tt), _simbols(tt._simbols)
		{
		}

		constexpr const std::vector<Symbol>& simbols() const
		{
			return _simbols;
		}

		const Transition<Token, State>* get(State state, Symbol simbol) const
		{
			if((size_t)state < TT_BASE::size()) return &TT_BASE::at(state)[simbol];

			return NULL;
		}
		size_t size() const
		{
			return TT_BASE::size();
		}

		int check(std::ostream& out, Indicator indicator = Indicator::none, State state = initial_state) const
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
					else if (TT_BASE::at(state)[s].indicator == Indicator::accept)
					{
					}
					else
					{
						out << state << ":" << Symbol(s) << " - " << "Unavez que se estable un estado como inidicador none, los estados posteriores solo puede ser, none, prefix, acceptable, accept\n";
						erros++;
					}
				}

				if (state == TT_BASE::at(state)[s].next) return 0;
				else if (state > TT_BASE::at(state)[s].next)
				{
					erros += check(out, TT_BASE::at(state)[s].indicator, TT_BASE::at(state)[s].next);
				}

				return 0;
			}


			return erros;
		}

		void print(std::ostream & out, State state = initial_state, int indend = 0)
		{
			if ((size_t)state > TT_BASE::size() - 1) return;//caso base

			for (Symbol s = 0; (size_t)s < TT_BASE::at(state).size(); s++)
			{
				if (TT_BASE::at(state)[s].next < initial_state) continue;

				if (state == initial_state) out << "|-";
				else out << "\t|-";

				if (s <= Symbol(Token::US)) out << state << "--control char-->" << TT_BASE::at(state)[s].next << " ";
				else out << state << "--'" << s << "'-->" << TT_BASE::at(state)[s].next << " ";
				out << to_string(TT_BASE::at(state)[s].indicator) << " ";
				if (TT_BASE::at(state)[s].token > Token::none) out << std::to_string((int)TT_BASE::at(state)[s].token) << " ";
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

        /*
        *\brief Agreaga la palabra indicada al anlizador
        *\param str cadeda de texto que deve acetar el analizador
        *\param prefixs lista de simbolos que determinan que la palabra ha terminado
        *\param token token retornado por el analizador si detecta la palabra
        */
		constexpr State word(const Symbol* str, Token token, const std::vector<Symbol>& prefixs,Flag flag)
		{
			size_t sz_str = strlen(str);
			if (sz_str == 0) throw exception("El input esta vacio");
			State state_current = initial_state, state_next = initial_state, state_last = initial_state;
			Symbol input;
			for (size_t i = 0; i < sz_str; i++)
			{
			    state_last = state_next;
				input = str[i];
				if(Flag::error == flag)
				{
					if(not is_symbol(input))
					{
						std::string msg_not_symbols;
						msg_not_symbols = "' ' ";
						msg_not_symbols[1] = input;
						msg_not_symbols += "no es un simbolo del lenguaje";
						throw exception(msg_not_symbols);
					}
				}
				if(is_used(input,state_current))
				{
					state_next = TT_BASE::at(state_current)[input].next;
				}
				else
				{
					state_next = create();
					TT_BASE::at(state_current)[input].next = state_next;
				}
				state_current = state_next;
			}
			TT_BASE::at(state_current)[input].indicator = Indicator::acceptable;


			//la ultima transicion deve estar vacio para ser usada con este token
			Symbol last_symbol = str[sz_str];
			if(is_used(last_symbol,state_last))
            {
                std::string msg;
                char sim[] = {' ','\0'};
                sim[0] = last_symbol;
                msg = "En el estado " + std::to_string(state_last) + ", para el simbolo ";
                msg += (const char*)sim;
                msg += ", La transicion ya esta ocupada, no se puede usar para el token ";
                msg += str;
                throw exception(msg);
            }
			prefixing(state_next, prefixs, token);

			return state_next;
		}

		/*
        *\brief equvalente a eloperador de expresion regular +
        *\param prefixs lista de simbolos que determinan que la palabra ha terminado
        *\param token token retornado por el analizador si detecta la palabra
        */
		constexpr State almost_one(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs,Flag flag)
		{
			State state_next = one(simbols,token,prefixs,flag);

			for (size_t i = 0; i < simbols.size(); i++)
			{
				TT_BASE::at(state_next)[simbols[i]].next = state_next;
			}

			return state_next;
		}

		/*
        *\brief equvalente a eloperador de expresion regular ?
        *\param prefixs lista de simbolos que determinan que la palabra ha terminado
        *\param token token retornado por el analizador si detecta la palabra
        */
		constexpr State one(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs,Flag flag)
		{
			State state_current = initial_state, state_next = initial_state;
			if (simbols.empty()) throw exception("El input esta vacio");

			for (size_t i = 0; i < simbols.size(); i++)
			{
				if (not is_symbol(simbols[i]))
				{
				    char minimsg[] = {'\'','?','\'', '\0'};
					minimsg[1] = simbols[i];
					std::string msg_not_symbols;
					msg_not_symbols = (const char*)minimsg;
					msg_not_symbols += ", no es un simbolo del lenguaje";
					throw exception(msg_not_symbols);
				}
			}
			if(flag == Flag::only_free)
			{
				state_next = create();
				prefixing(state_next,prefixs,token);
				for (size_t i = 0; i < simbols.size(); i++)
				{
					if (not is_used(simbols[i],state_current)) TT_BASE::at(state_current)[simbols[i]].next = state_next;
				}
			}
			else if(Flag::error == flag)
			{
				//state_next = one(simbols, state_current, prefixs, token);//Usar una funcion homegena
				state_next = create();
				prefixing(state_next,prefixs,token);
				for (size_t i = 0; i < simbols.size(); i++)
				{
					if (is_used(simbols[i], state_current))
					{
						std::string msg;
						char sim[] = { ' ','\0' };
						sim[0] = simbols[i];
						msg = "En el estado " + std::to_string(state_current) + ", para el simbolo ";
						msg += (const char*)sim;
						msg += ", La transicion ya esta ocupada, no se puede usar para el token ";
						msg += std::to_string((int)token);
						throw exception(msg);
					}
					TT_BASE::at(state_current)[simbols[i]].next = state_next;
				}
			}

			return state_next;
		}

		constexpr State one(Symbol symbol, Token token, const std::vector<Symbol>& prefixs, Flag flag = Flag::none)
		{
			State state_next = initial_state;

			if (not is_symbol(symbol))
			{
				char minimsg[] = {'\'','?','\'', '\0'};
				minimsg[1] = symbol;
				std::string msg_not_symbols;
				msg_not_symbols = (const char*)minimsg;
				msg_not_symbols += ", no es un simbolo del lenguaje";
				throw exception(msg_not_symbols);
			}
			if (is_used(symbol, initial_state))
			{
				std::string msg;
				char minimsg[] = {'\'','?','\'', '\0'};
				minimsg[1] = symbol;
				msg = "En el estado " + std::to_string(initial_state) + ", para el simbolo ";
				msg += (const char*)minimsg;
				msg += ", La transicion ya esta ocupada, no se puede usar para el token ";
				msg += std::to_string((int)token);
				throw exception(msg);
			}

			state_next = create();
			prefixing(state_next,prefixs,token);

			return initial_state;
		}

		/*
        *\brief equvalente a eloperador de expresion regular *
        *\param prefixs lista de simbolos que determinan que la palabra ha terminado
        *\param token token retornado por el analizador si detecta la palabra
        */
		constexpr State some(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs,Flag flag,State extend)
		{
			//State next = create();
			//prefixing(next,prefixs,token);
			for (size_t i = 0; i < simbols.size(); i++)
			{
				TT_BASE::at(extend)[simbols[i]].next = extend;
				TT_BASE::at(extend)[simbols[i]].indicator = Indicator::acceptable;
				TT_BASE::at(extend)[simbols[i]].token = token;
			}
			some(simbols,token,prefixs,flag,initial_state,extend);
			return initial_state;
		}
    protected:
        constexpr void sort_symbols()
        {
			std::sort(_simbols.begin(), _simbols.end(), [](int a, int b)
				{
					return a < b;
				});
		}

		std::vector<Symbol> _simbols;
		static const State initial_state = 0;

	private:

		/*
		*\brief Recorre todos los symbols del estado indicado, caundo encuentra algunos de los prefijos asigna dicha trasision como de aceptacion
		*/
		constexpr State prefixing(State state_current, const std::vector<Symbol>& prefixs, Token token)
		{
            if(if_prefixed(state_current,prefixs))
            {
                std::string msg;
                msg = "En el estado " + std::to_string(state_current) + ", no se puede colocar los prefijo ya que al menos una transicion esta usada";
                throw exception(msg);
            }

			for (size_t k = 0; k < length_transition(); k++)
			{
				if (std::find(prefixs.begin(), prefixs.end(), Symbol(k)) == prefixs.end()) continue;

				TT_BASE::at(state_current)[k].next = 0;
				TT_BASE::at(state_current)[k].token = token;
				TT_BASE::at(state_current)[k].indicator = Indicator::accept;
			}

			return state_current;
		}
		/*
		*\brief Verifica si el estado indicado ha sido marcado con los prefijos indicados
		*/
		constexpr bool if_prefixed(State state_current, const std::vector<Symbol>& prefixs)
		{
			for (size_t i = 0; i < prefixs.size(); i++)
			{
				if (TT_BASE::at(state_current)[prefixs[i]].indicator == Indicator::accept and TT_BASE::at(state_current)[prefixs[i]].next == 0) return true;
				//if (TT_BASE::at(state_current)[prefixs[i]].token == Token::none) return false;
			}

			return false;
		}

		constexpr bool is_recursive(Symbol simbol, State state_current)const
		{
            if(TT_BASE::at(state_current)[simbol].next == state_current) return true;

            return false;
		}
		constexpr bool is_empty_transition(Symbol simbol, State state_current)const
		{
            if(TT_BASE::at(state_current)[simbol].next < initial_state) return true;

            return false;
		}
		constexpr bool is_symbol(Symbol s) const
		{
			if (std::find(_simbols.begin(), _simbols.end(), Symbol(s)) == _simbols.end()) return false;

			return true;
		}
		constexpr bool is_used(Symbol simbol, State state_current)const
		{
            if(TT_BASE::at(state_current)[simbol].next < initial_state) return false;

            return true;
		}
		constexpr void some(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs,Flag flag,State current,State target)
		{
			if(target == current) return;
			for (size_t i = 0; i < simbols.size(); i++)
			{
				if(TT_BASE::at(current)[simbols[i]].indicator == Indicator::accept and TT_BASE::at(current)[simbols[i]].next == 0)
				{//prefixed

				}
				else if(TT_BASE::at(current)[simbols[i]].indicator == Indicator::none and TT_BASE::at(current)[simbols[i]].next == -1 and TT_BASE::at(current)[simbols[i]].token == Token::none)
                {//initailized
                	//prefixing(current,prefixs,token,simbols[i]);
					TT_BASE::at(current)[simbols[i]].next = target;
                }
				else if(TT_BASE::at(current)[simbols[i]].indicator == Indicator::none and TT_BASE::at(current)[simbols[i]].next >= 0  and TT_BASE::at(current)[simbols[i]].token == Token::none)
                {//used but not prefixed
                	//if(TT_BASE::at(current)[simbols[i]].next < 0) continue;
                	if(TT_BASE::at(current)[simbols[i]].next == current) continue;
					some(simbols,token,prefixs,flag,TT_BASE::at(current)[simbols[i]].next,target);
					for (size_t j = 0; j < simbols.size(); j++)
					{
						if(simbols[i] == simbols[j]) continue;
						if(is_used(simbols[j],current)) continue;
						TT_BASE::at(current)[simbols[j]].next = target;
					}
                }
				else
				{

				}
			}
		}
	private:
	};

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

template<typename Symbol /*Input*/,typename Token,typename State/*State*/>
class A
{
public:

public:
	A(const TTA<Symbol,Token, State>& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),index(0),actual_status(0),initial_status(0)
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
				if (acceptable_transition and acceptable_ended)
				{
					//std::cout << "terminating ...by prefix\n";
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
		else if (not actual_transition and index == buffer->size())
		{
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
	const TTA<Symbol,Token, State>* table;
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


enum errors
	{
		none,
		fail_create_firts_estate,
		fail_on_word_not_symbol,
		fail_on_word_null_transition,
		fail_on_used_null_transition,
		fail_on_create_no_memory,
		fail_on_word_used_transition,
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
			case errors::fail_on_word_used_transition: return "";
		}

		return "Error desconocido";
	}

//Transition Table - Tipo B
template<typename Symbol /*Input*/,typename Token,typename State/*Status*/,size_t amount_states,size_t amount_transitions,size_t amount_symbols>
class TTB
{
public:

public:
	constexpr TTB() : index(-1),error(errors::none)
	{
		for(size_t i = 0; i < amount_states; i++)
		{
			for(size_t j = 0; j < amount_transitions; j++)
			{
				tt[i][j].next = -1;
			}
		}
	}

	void print(std::ostream & out, State state = initial_state, size_t indend = 0) const
	{
		if ((size_t)state > amount_states - 1) return;//caso base

		for (Symbol s = 0; (size_t)s < amount_states; s++)
		{
			if (get(state,s)->next < initial_state) continue;

			for(size_t i = 0; i < indend; i++)
			{
				out << " ";
			}
			out << "|-";

			if (s <= Symbol(Token::US))
            {
                out << state << "--control char(" << (int)s << ")";
            }
			else
            {
                out << state << "--'" << s << "'";
            }

            out << "-->" << get(state,s)->next << " ";

			out << to_string(get(state,s)->indicator) << " ";
			if (get(state,s)->token > Token::none) out << std::to_string((int)get(state,s)->token) << " ";
			out << "\n";

            if (get(state,s)->next > initial_state) print(out, get(state,s)->next,indend + 1);

		}
	}

	const Symbol* get_symbols()const
	{
		return symbols;
	}
	const Transition<Token, State>* get(size_t state,size_t simbol) const
	{
		if((size_t)state < amount_states) if((size_t)simbol < amount_transitions) return &tt[state][simbol];

		return NULL;
	}
	constexpr Transition<Token, State>* get(size_t state,size_t simbol)
	{
		if(state < amount_states) if(simbol < amount_transitions) return &tt[state][simbol];

		return NULL;
	}
	size_t get_amount_states()const
	{
		return amount_states;
	}
	size_t size()const
	{
		return amount_states;
	}
	size_t get_amount_symbols()const
	{
		return amount_symbols;
	}
	size_t get_amount_transitions()const
	{
		return amount_transitions;
	}
	errors get_last_error()const
	{
		return error;
	}

private:
	constexpr void sort()
	{
		std::sort(symbols.begin(), symbols.end(), [](int a, int b)
		{
			return a < b;
		});
	}

protected:
	constexpr State create()
	{
		if((size_t)index + 1 < amount_states) return ++index;

		error = errors::fail_on_create_no_memory;
		return -1;
	}

	constexpr bool is_used(Symbol simbol, State state_current)
	{
		if(not get(state_current,simbol))
		{
			error = errors::fail_on_used_null_transition;
			return false;
		}


		if(get(state_current,simbol)->next < initial_state) return false;
		return true;
	}
	constexpr bool is_symbol(Symbol s)
	{
		if (std::find(symbols, symbols + amount_symbols, Symbol(s)) == symbols + amount_symbols) return false;

		return true;
	}


	/*
	*\brief Recorre todos los symbols del estado indicado, caundo encuentra algunos de los prefijos asigna dicha trasision como de aceptacion
	*/
	constexpr State prefixing(State state_current, const Symbol* prefixs, size_t length, Token token)
	{
		for (size_t k = 0; k < amount_transitions; k++)
		{
			if (std::find(prefixs, prefixs + length, Symbol(k)) == prefixs + length) continue;

			get(state_current,k)->next = 0;
			get(state_current,k)->token = token;
			get(state_current,k)->indicator = Indicator::accept;
		}

		return state_current;
	}

    /*
    *\brief Agreaga la palabra indicada al anlizador
    *\param str cadeda de texto que deve acetar el analizador
    *\param prefixs lista de simbolos que determinan que la palabra ha terminado
    *\param token token retornado por el analizador si detecta la palabra
    */
    constexpr State word(const Symbol* str, Token token, const Symbol* prefixs, size_t length, Flag flag)
	{
        size_t sz_str = strlen(str);
        if (sz_str == 0) throw exception("El input esta vacio");
        State state_current = initial_state, state_next = initial_state, state_last = initial_state;
        Symbol input;
		for (size_t i = 0; i < sz_str; i++)
        {
            state_last = state_next;
			input = str[i];
			if(Flag::error == flag)
            {
                if(error > errors::none) return -1;
                if(not is_symbol(input))
				{
                    error = errors::fail_on_word_not_symbol;
                    return -1;
				}
            }
            if(is_used(input,state_current))
            {
                state_next = get(state_current,input)->next;
            }
            else
			{
                state_next = create();
                get(state_current,input)->next = state_next;
			}
            state_current = state_next;
		}

        //la ultima transicion deve estar vacio para ser usada con este token
		Symbol last_symbol = str[sz_str];
		if(is_used(last_symbol,state_last))
        {
            error = errors::fail_on_word_used_transition;
            return -1;
        }
        prefixing(state_next, prefixs, length, token);

        return state_next;
    }


protected:
	State index;
	errors error;

	Symbol symbols[amount_symbols];
	Transition<Token, State> tt[amount_states][amount_transitions];

	static const State initial_state = 0;
};


template<typename Symbol /*Input*/,typename Token,typename State/*State*/,size_t amount_states,size_t amount_transitions,size_t amount_symbols>
class B
{
public:

public:
	B(const TTB<Symbol,Token, State,amount_states,amount_transitions,amount_symbols>& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),index(0),actual_status(0),initial_status(0)
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
				if (acceptable_transition and acceptable_ended)
				{
					//std::cout << "terminating ...by prefix\n";
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
		else if (not actual_transition and index == buffer->size())
		{
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
	const TTB<Symbol,Token, State,amount_states,amount_transitions,amount_symbols>* table;
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


template<typename Symbol /*Input*/,typename Token,typename State/*State*/>
class Lexer
{
public:

public:
	Lexer(const TTA<Symbol,Token, State>& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),index(0),actual_status(0),initial_status(0)
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
				if (acceptable_transition and acceptable_ended)
				{
					//std::cout << "terminating ...by prefix\n";
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
		else if (not actual_transition and index == buffer->size())
		{
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
	const TTA<Symbol,Token, State>* table;
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
