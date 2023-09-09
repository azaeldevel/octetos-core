

#ifndef OCTETOS_CORE_LEXER_TTA_V3_HH
#define OCTETOS_CORE_LEXER_TTA_V3_HH



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
#include <vector>

#include "Lexer.hh"
#include "Buffer.hh"
#include "array.hh"

namespace oct::core::v3::lex
{
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

		/*void print(std::ostream & out, State state = initial_state, int indend = 0)
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
		}*/

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
			TT_BASE::at(state_last)[input].token = token;
			TT_BASE::at(state_last)[input].indicator = Indicator::acceptable;


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
        *\brief equivalente al operador de +
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
        *\brief equivalente a eloperador de expresion regular ?
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


}


#endif
