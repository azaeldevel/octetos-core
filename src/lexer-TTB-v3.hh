

#ifndef OCTETOS_CORE_LEXER_TTB_V3_HH
#define OCTETOS_CORE_LEXER_TTB_V3_HH



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

		for (Symbol s = 0; (size_t)s < amount_transitions; s++)
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
    *\brief Verifica si el estado indicado ha sido marcado con los prefijos indicados
    */
    constexpr bool if_prefixed(State state_current, const Symbol* prefixs_array, size_t prefixs_length)
    {
        for (size_t i = 0; i < prefixs_length; i++)
        {
            if (get(state_current,prefixs_array[i])->indicator == Indicator::accept and get(state_current,prefixs_array[i])->next == 0) return true;
        }

        return false;
    }

	/*
	*\brief Recorre todos los symbols del estado indicado, caundo encuentra algunos de los prefijos asigna dicha trasision como de aceptacion
	*/
	constexpr State prefixing(State state_current, const Symbol* prefixs, size_t length, Token token)
	{
	    if(if_prefixed(state_current,prefixs,length))
        {
            error = errors::fail_on_prefixing_conflict;
            return -1;
        }

        const Symbol* end = prefixs + length;
		for (size_t k = 0; k < length; k++)
		{
			if (std::find(prefixs, end, Symbol(prefixs[k])) == end) continue;

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
		get(state_last,input)->token = token;
		get(state_last,input)->indicator = Indicator::acceptable;

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

	/*
	*\brief equivalente a eloperador de expresion regular ?
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(const Symbol* symbols_array, size_t symbols_length, Token token, const Symbol* prefixs_array, size_t prefixs_length,Flag flag)
	{
		State state_current = initial_state, state_next = initial_state;
		if (symbols_length == 0)
		{
			error = errors::fail_on_one_empty;
			return -1;
		}

		if(flag == Flag::only_free)
		{
			state_next = create();
			if(state_next < 0) return -1;
			if(error > errors::none) return -1;
			for (size_t i = 0; i < symbols_length; i++)
			{
				if (not is_used(symbols_array[i],state_current)) get(state_current,symbols_array[i])->next = state_next;
			}
			prefixing(state_next,prefixs_array,prefixs_length,token);
		}
		else if(Flag::error == flag)
		{
			state_next = create();
			if(state_next < 0) return -1;
			if(error > errors::none) return -1;
			for (size_t i = 0; i < symbols_length; i++)
			{
				if(is_used(symbols_array[i],state_current))
				{
					error = errors::fail_on_one_used_transition;
					return -1;
				}
				get(state_current,symbols_array[i])->next = state_next;
			}
			prefixing(state_next,prefixs_array,prefixs_length,token);
		}

		return state_next;
	}

/*
	*\brief equivalente a eloperador de expresion regular ?
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(const Symbol* symbols_array, size_t symbols_length, Token token,Flag flag)
	{
		State state_current = initial_state, state_next = initial_state;
		if (symbols_length == 0)
		{
			error = errors::fail_on_one_empty;
			return -1;
		}

		for (size_t i = 0; i < symbols_length; i++)
		{
			if(error > errors::none) return -1;
			if(not is_symbol(symbols_array[i]))
			{
				error = errors::fail_on_one_not_symbol;
				return -1;
			}
		}
		if(flag == Flag::only_free)
		{
			state_next = create();
			if(state_next < 0) return -1;
			if(error > errors::none) return -1;
			//prefixing(state_next,prefixs_array,prefixs_length,token);
			for (size_t i = 0; i < symbols_length; i++)
			{
				if (not is_used(symbols_array[i],state_current)) get(state_current,symbols_array[i])->next = state_next;
			}
		}
		else if(Flag::error == flag)
		{
			state_next = create();
			if(state_next < 0) return -1;
			if(error > errors::none) return -1;
			//sprefixing(state_next,prefixs_array,prefixs_length,token);
			for (size_t i = 0; i < symbols_length; i++)
			{
				if(is_used(symbols_array[i],state_current))
				{
					error = errors::fail_on_one_used_transition;
					return -1;
				}
				get(state_current,symbols_array[i])->next = state_next;
			}
		}

		return state_next;
	}
	/*
	*\brief Un simbolo
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(Symbol symbol, Token token, const Symbol* prefixs, size_t length , Flag flag = Flag::none)
	{
		State state_next = initial_state;

		if(error > errors::none) return -1;
		if(not is_symbol(symbol))
		{
			error = errors::fail_on_one_not_symbol;
			return -1;
		}

		if (is_used(symbol,initial_state))
		{
			error = errors::fail_on_one_used_transition;
			return -1;
		}

		state_next = create();
		if(error > errors::none) return -1;
		if(state_next < 0) return -1;
		State state_prefix  = prefixing(state_next,prefixs,length,token);
        if(state_prefix < 0 ) return state_prefix;

		return state_next;
	}

	/*
	*\brief equivalente a el operador de expresion regular +
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State almost_one(const Symbol* symbols_array, size_t symbols_length, Token token, const Symbol* prefixs_array, size_t prefixs_length,Flag flag)
	{
		State state_next = one(symbols_array,symbols_length,token,prefixs_array,prefixs_length,flag);
		if(error > errors::none) return -1;

		for (size_t i = 0; i < symbols_length; i++)
		{
			get(state_next,symbols_array[i])->next = state_next;
		}

		return state_next;
	}

	/*
	*\brief equivalente a el operador regular *
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr void some(const Symbol* symbols_array, size_t symbols_length, Token token, const Symbol* prefixs_array, size_t prefixs_length,Flag flag,State current,State target)
    {
        if(target == current) return;
        if((size_t)current >= amount_states) return;
        //if(target >= size()) return;

        for (size_t i = 0; i < symbols_length; i++)
        {
            if(get(current,symbols_array[i])->indicator == Indicator::accept and get(current,symbols_array[i])->next == 0)
            {//prefixed

            }
            else if(get(current,symbols_array[i])->indicator == Indicator::none and get(current,symbols_array[i])->next == -1 and get(current,symbols_array[i])->token == Token::none)
            {//initailized
                get(current,symbols_array[i])->next = target;
                get(current,symbols_array[i])->indicator = Indicator::acceptable;
				get(current,symbols_array[i])->token = token;
                //prefixing(current,prefixs_array,prefixs_length,token);
            }
            else if(get(current,symbols_array[i])->indicator == Indicator::none and get(current,symbols_array[i])->next >= 0  and get(current,symbols_array[i])->token == Token::none)
            {//used but not prefixed
                if(get(current,symbols_array[i])->next == current) continue;
                some(symbols_array,symbols_length,token,prefixs_array,prefixs_length,flag,get(current,symbols_array[i])->next,target);
                /*for (size_t j = 0; j < symbols_length; j++)
                {
                    if(symbols_array[i] == symbols_array[j]) continue;
                    if(is_used(symbols_array[j],current)) continue;
                    get(current,symbols_array[j])->next = target;
					//get(current,symbols_array[i])->indicator = Indicator::acceptable;
					//get(current,symbols_array[i])->token = token;
                }*/
                //prefixing(current,prefixs_array,prefixs_length,token);
            }
            else
            {
            }
        }
    }

    /*
    *\brief equvalente a eloperador de expresion regular *
    *\param prefixs lista de simbolos que determinan que la palabra ha terminado
    *\param token token retornado por el analizador si detecta la palabra
    */
    constexpr State some(const Symbol* symbols_array, size_t symbols_length, Token token, const Symbol* prefixs_array, size_t prefixs_length,Flag flag,State extend)
    {
        for (size_t i = 0; i < symbols_length; i++)
        {
            get(extend,symbols_array[i])->next = extend;
			get(extend,symbols_array[i])->indicator = Indicator::acceptable;
			get(extend,symbols_array[i])->token = token;
        }
        some(symbols_array,symbols_length,token,prefixs_array,prefixs_length,flag,initial_state,extend);
		return extend;
    }

protected:
	State index;
	errors error;

	Symbol symbols[amount_symbols];
	Transition<Token, State> tt[amount_states][amount_transitions];

	static const State initial_state = 0;
};

}


#endif
