

#ifndef OCTETOS_CORE_LEXER_TTC_V3_HH
#define OCTETOS_CORE_LEXER_TTC_V3_HH



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

 #include <vector>

#include "lexer-v3.hh"
#include "Buffer-v3.hh"

namespace oct::core::v3::lex
{
    /*
    *\brief Tabla de Transiciones tipo C
    *\param prefan_length longitud del prefijo de analisis
    */
	template<typename Symbol,typename Token,typename State,size_t prefan_length, size_t amount_transitions>
	class TTC
	{
	public:

		constexpr State create()
		{
			states.resize(states.size() + 1);
			states.at(states.size() - 1).resize(amount_transitions);
			return State(states.size() - 1);
		}

	public:
	    constexpr TTC() = default;
		constexpr TTC(const std::vector<Symbol>& ss) : _simbols(ss)
		{
			sort_symbols();
			//std::cout << "Size : " << _simbols.size();
			State state_initial = create();
			make_prefix_deep(state_initial,0);
		}

		void make_prefix_deep(State actual,size_t deep)
		{
            if(deep >= prefan_length) return;

            State state;
            for(Symbol s : _simbols)
            {
                state = create();
                get(actual,s)->next = state;
                //std::cout << actual << "-" << s << "->" << state << "\n";
                make_prefix_deep(state,deep + 1);
            }
		}

		constexpr const std::vector<Symbol>& simbols() const
		{
			return _simbols;
		}

		const Transition<Token, State>* get(State state, Symbol simbol) const
		{
			if((size_t)state < states.size()) return &states.at(state)[simbol];

			return NULL;
		}
		Transition<Token, State>* get(State state, Symbol simbol)
		{
			if((size_t)state < states.size()) return &states.at(state)[simbol];

			return NULL;
		}
		Transition<Token, State>* get(Symbol simbol)
		{
			if((size_t)simbol < states[initial_state].size()) return &states[initial_state][simbol];

			return NULL;
		}
		inline size_t size() const
		{
			return states.size();
		}

	void print(std::ostream & out, State state = initial_state, size_t indend = 0) const
	{
	    //std::cout << "printing..." << state << "\n";
		if((size_t)state >= size()) return;//caso base

		for (Symbol s = 0; (size_t)s < amount_transitions; s++)
		{
		    //std::cout << "printing..." << state << " - '" << s << "'\n";
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

        /*
        *\brief Uno de los siguientes simbolos
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
					state_current = get(simbols[i]);
					if (not is_used(simbols[i],state_current)) get(state_current,simbols[i])->next = state_next;
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
					state_current = get(simbols[i]);
					get(state_current,simbols[i])->next = state_next;
				}
			}

			return state_next;
		}

		/*
        *\brief equivalente a eloperador de expresion regular ?
        *\param prefixs lista de simbolos que determinan que la palabra ha terminado
        *\param token token retornado por el analizador si detecta la palabra
        */
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
			if (is_used(symbol, get(symbol)->next))
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
			State state_current = get(symbol);
			get(state_current,symbol)->next = state_next;
			prefixing(state_next,prefixs,token);

			return initial_state;
		}

        /*
        *\brief Agreaga la palabra indicada al anlizador
        *\param str cadeda de texto que deve acetar el analizador
        *\param prefixs lista de simbolos que determinan que la palabra ha terminado
        *\param token token retornado por el analizador si detecta la palabra
        */
		State word(const Symbol* str, Token token, const std::vector<Symbol>& prefixs,Flag flag)
		{
			size_t sz_str = strlen(str);
			if (sz_str == 0) throw exception("El input esta vacio");
			State state_current = get(str[0])->next, state_next = initial_state, state_last = initial_state;
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
					state_next = get(state_current,input)->next;
				}
				else
				{
					state_next = create();
					get(state_current,input)->next = state_next;
				}
				state_current = state_next;
			}
			get(state_last,input)->token = token;
			get(state_last,input)->indicator = Indicator::acceptable;


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
		/*constexpr State almost_one(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs,Flag flag)
		{
			State state_next = one(simbols,token,prefixs,flag);

			for (size_t i = 0; i < simbols.size(); i++)
			{
				TT_BASE::at(state_next)[simbols[i]].next = state_next;
			}

			return state_next;
		}*/

		/*
        *\brief equvalente a eloperador de expresion regular *
        *\param prefixs lista de simbolos que determinan que la palabra ha terminado
        *\param token token retornado por el analizador si detecta la palabra
        */
		/*constexpr State some(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs,Flag flag,State extend)
		{
			for (size_t i = 0; i < simbols.size(); i++)
			{
				TT_BASE::at(extend)[simbols[i]].next = extend;
				TT_BASE::at(extend)[simbols[i]].indicator = Indicator::acceptable;
				TT_BASE::at(extend)[simbols[i]].token = token;
			}
			some(simbols,token,prefixs,flag,initial_state,extend);
			return initial_state;
		}*/
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

			for (size_t k = 0; k < amount_transitions; k++)
			{
				if (std::find(prefixs.begin(), prefixs.end(), Symbol(k)) == prefixs.end()) continue;

				get(state_current,k)->next = 0;
				get(state_current,k)->token = token;
				get(state_current,k)->indicator = Indicator::accept;
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
				if (get(state_current,prefixs[i])->indicator == Indicator::accept and get(state_current,prefixs[i])->next == 0) return true;
				//if (TT_BASE::at(state_current)[prefixs[i]].token == Token::none) return false;
			}

			return false;
		}

		constexpr bool is_recursive(Symbol simbol, State state_current)const
		{
            if(get(state_current,simbol)->next == state_current) return true;

            return false;
		}
		constexpr bool is_empty_transition(Symbol simbol, State state_current)const
		{
            if(get(state_current,simbol)->next < initial_state) return true;

            return false;
		}
		constexpr bool is_symbol(Symbol s) const
		{
			if (std::find(_simbols.begin(), _simbols.end(), Symbol(s)) == _simbols.end()) return false;

			return true;
		}
		constexpr bool is_used(Symbol simbol, State state_current)const
		{
            if(get(state_current,simbol)->next < initial_state) return false;

            return true;
		}
		constexpr void some(const std::vector<Symbol> simbols, Token token, const std::vector<Symbol>& prefixs,Flag flag,State current,State target)
		{
			if(target == current) return;
            if((size_t)current >= states.size()) return;

			for (size_t i = 0; i < simbols.size(); i++)
			{
				if(get(current,simbols[i])->indicator == Indicator::accept and get(current,simbols[i])->next == 0)
				{//prefixed

				}
				else if(get(current,simbols[i])->indicator == Indicator::none and get(current,simbols[i])->next == -1 and get(current,simbols[i])->token == Token::none)
                {//initailized
                	//prefixing(current,prefixs,token,simbols[i]);
					get(current,simbols[i])->next = target;
                }
				else if(get(current,simbols[i])->indicator == Indicator::none and get(current,simbols[i])->next >= 0  and get(current,simbols[i])->token == Token::none)
                {//used but not prefixed
                	//if(TT_BASE::at(current)[simbols[i]].next < 0) continue;
                	if(get(current,simbols[i])->next == current) continue;
					some(simbols,token,prefixs,flag,get(current,simbols[i])->next,target);
					for (size_t j = 0; j < simbols.size(); j++)
					{
						if(simbols[i] == simbols[j]) continue;
						if(is_used(simbols[j],current)) continue;
						get(current,simbols[j])->next = target;
					}
                }
				else
				{

				}
			}
		}

	private:
	    std::vector<std::vector<Transition<Token, State>>> states;
	};


}


#endif
