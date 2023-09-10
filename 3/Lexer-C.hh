

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

#include <cstddef>
#include <string>
#include <list>
#include <algorithm>
#include <initializer_list>
#include <iterator>


#include "Buffer.hh"
#include "Lexer.hh"
#include "array.hh"

namespace oct::core::v3::lex
{
template<typename Symbol /*Input*/,typename Token,typename State/*Status*/,size_t amount_states,size_t amount_transitions=128,size_t amount_symbols=amount_transitions>
class TTC
{
public:

public:
	/*constexpr TTC() : index(-1),error(errors::none)
	{
		for(size_t i = 0; i < amount_states; i++)
		{
			for(size_t j = 0; j < amount_transitions; j++)
			{
				tt[i][j].next = -1;
			}
		}
	}*/
	/**
	*\brief
	*
	*/
	constexpr TTC() : index(-1),error(errors::none)
	{
		for(size_t i = 0; i < amount_states; i++)
		{
			for(size_t j = 0; j < amount_transitions; j++)
			{
				tt[i][j].next = -1;
				tt[i][j].indicator = Indicator::none;
				tt[i][j].token = Token::none;
			}
		}
		for(size_t i = 0; i < amount_symbols;i++)
		{
            symbols[i] = i;
		}
		create();
	}

	void print(std::ostream & out, State state = initial_state, size_t indend = 0) const
	{
		if((size_t)state >= size()) return;//caso base

		for (Symbol s = 0; (size_t)s < amount_transitions; s++)
		{
		    //std::cout << "printing..." << state << " - '" << s << "'\n";
			if (get(state,s)->next < initial_state) continue;

			for(size_t i = 0; i < indend; i++)
			{
				out << " ";
			}

			print(out,state,s);

            if(get(state,s)->next != state) if (get(state,s)->next > initial_state) print(out, get(state,s)->next,indend + 1);

		}
	}
	void print(std::ostream & out, State state, Symbol symbol) const
	{
			out << "|-";

			if (symbol <= Symbol(Token::US))
            {
                out << state << "--control char(" << (int)symbol << ")";
            }
			else
            {
                out << state << "--'" << symbol << "'";
            }

            out << "-->" << get(state,symbol)->next << " ";

			out << to_string(get(state,symbol)->indicator);
			out << " - ";
			out << (int)get(state,symbol)->token;
			out << "\n";
	}

	const Symbol* get_symbols()const
	{
		return symbols;
	}
	/**
	*\brief Optiene la trancion de l estado indicado con el simbolo inidcado
	*
	*/
	const Transition<Token, State>* get(size_t state,size_t simbol) const
	{
		if((size_t)state < amount_states) if((size_t)simbol < amount_transitions) return &tt[state][simbol];

		return NULL;
	}
	/**
	*\brief Optiene la trancion de l estado indicado con el simbolo inidcado
	*
	*/
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
	constexpr void init(State state)
	{
		for(size_t i = 0; i < amount_states; i++)
		{
			for(size_t j = 0; j < amount_transitions; j++)
			{
				tt[state][j].next = -1;
				tt[state][j].indicator = Indicator::none;
				tt[state][j].token = Token::none;
			}
		}
	}

public:
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
    constexpr bool if_prefixed(State state_current,const array<Symbol>& prefixs_array)
    {
        for (size_t i = 0; i < prefixs_array.size(); i++)
        {
            if (get(state_current,prefixs_array[i])->indicator == Indicator::accept and get(state_current,prefixs_array[i])->next == 0) return true;
        }

        return false;
    }

	/*
	*\brief Recorre todos los symbols del estado indicado, caundo encuentra algunos de los prefijos asigna dicha trasision como de aceptacion
	*/
	constexpr State prefixing(State state_current,const array<Symbol>& prefixs, Token token)
	{
	    if(if_prefixed(state_current,prefixs))
        {
            error = errors::fail_on_prefixing_conflict;
            return -1;
        }

        const Symbol* end = &prefixs[prefixs.size() - 1];
		for (size_t k = 0; k < prefixs.size(); k++)
		{
			if (std::find(&prefixs[0], end, Symbol(prefixs[k])) == end) continue;

			get(state_current,prefixs[k])->next = 0;
			get(state_current,prefixs[k])->token = token;
			get(state_current,prefixs[k])->indicator = Indicator::accept;
		}

		return state_current;
	}

	/*
	*\brief Recorre todos los symbols del estado indicado, caundo encuentra algunos de los prefijos asigna dicha trasision como de aceptacion
	*/
	constexpr State prefixing(State state_current,const array<Symbol>& prefixs)
	{
	    if(if_prefixed(state_current,prefixs))
        {
            error = errors::fail_on_prefixing_conflict;
            return -1;
        }

        const Symbol* end = &prefixs[prefixs.size() - 1];
		for (size_t k = 0; k < prefixs.size(); k++)
		{
			if (std::find(&prefixs[0], end, Symbol(prefixs[k])) > end) continue;

			get(state_current,prefixs[k])->next = 0;
			get(state_current,prefixs[k])->token = Token(prefixs[k]);
			get(state_current,prefixs[k])->indicator = Indicator::accept;
		}

		return state_current;
	}

    /*
    *\brief Agreaga la palabra indicada al anlizador
    *\param str cadeda de texto que deve acetar el analizador
    *\param prefixs lista de simbolos que determinan que la palabra ha terminado
    *\param token token retornado por el analizador si detecta la palabra
    */
    /*constexpr State word(const Symbol* str, Token token, const Symbol* prefixs, size_t length, Flag flag)
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
    }*/


	/*
	*\brief Crea una trasicion recursiva
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State circular(const array<Symbol>& symbols_array)
	{
        State state_next = one(symbols_array);

		for (size_t i = 0; i < symbols_array.size(); i++)
		{
			get(state_next,symbols_array[i])->next = state_next;
		}

		return state_next;
	}

	/*
	*\brief Crea una trasicion recursiva
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State circular(const array<Symbol>& symbols_array, State state_next)
	{
		for (size_t i = 0; i < symbols_array.size(); i++)
		{
			get(state_next,symbols_array[i])->next = state_next;
		}

		return state_next;
	}

	/*
	*\brief Una transicion exactamente
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(const array<Symbol>& symbols_array,State state_current)
	{
		State state_next = initial_state;
		if (symbols_array.size() == 0)
		{
			error = errors::fail_on_one_empty;
			return -1;
		}

        state_next = create();
        //std::cout << "new state " << state_next << "\n";
        if(state_next < 0) return -1;
        if(error > errors::none) return -1;
        for (size_t i = 0; i < symbols_array.size(); i++)
        {
            if (not is_used(symbols_array[i],state_current)) if (not is_used(symbols_array[i],state_next))  get(state_current,symbols_array[i])->next = state_next;
        }

		return state_next;
	}


	/*
	*\brief Una transicion exactamente
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(const array<Symbol>& symbols_array)
	{
		State state_current = initial_state, state_next = initial_state;
		if (symbols_array.size() == 0)
		{
			error = errors::fail_on_one_empty;
			return -1;
		}

        state_next = create();
        //std::cout << "new state " << state_next << "\n";
        if(state_next < 0) return -1;
        if(error > errors::none) return -1;
        for (size_t i = 0; i < symbols_array.size(); i++)
        {
            if (not is_used(symbols_array[i],state_current)) if (not is_used(symbols_array[i],state_next))  get(state_current,symbols_array[i])->next = state_next;
        }

		return state_next;
	}

	/*
	*\brief Una transicion exactamente
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(const array<Symbol>& symbols_array, Token token, const array<Symbol>& prefixs,size_t min, size_t max)
	{
		State state_next;
		if(min >= max) return -1;
		//if(min == 0 ) return -1;
		//if(min == 1 ) return -1;

        state_next = one(symbols_array);
		for(size_t i = 0; i < min - 1; i++)
		{
            state_next = one(symbols_array,state_next);
		}
        prefixing(state_next,prefixs,token);
		for(size_t i = min; i < max - 1; i++)
		{
            state_next = one(symbols_array,state_next);
		}
        prefixing(state_next,prefixs,token);

		return state_next;
	}

	/*
	*\brief Una transicion exactamente
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(const array<Symbol>& symbols_array, Token token, const array<Symbol>& prefixs_array)
	{
		State state_current = initial_state, state_next = initial_state;
		if (symbols_array.size() == 0)
		{
			error = errors::fail_on_one_empty;
			return -1;
		}

        state_next = create();
        //std::cout << "new state " << state_next << "\n";
        if(state_next < 0) return -1;
        if(error > errors::none) return -1;
        prefixing(state_next,prefixs_array,token);
        for (size_t i = 0; i < symbols_array.size(); i++)
        {
            if (not is_used(symbols_array[i],state_current)) if (not is_used(symbols_array[i],state_next)) get(state_current,symbols_array[i])->next = state_next;
        }

		return state_next;
	}

	/*
	*\brief Una transicion exactamente
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State one(const array<Symbol>& symbols_array,State state_current,bool autotoken)
	{
		State state_next = initial_state;
		state_next = one(symbols_array,state_current);
		prefixing(state_current,symbols_array);

		return state_next;
	}


	/*
	*\brief Uno o mas de los simbolos
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State almost_one(const array<Symbol>& symbols_array)
	{
		State state_next = one(symbols_array);
		if(error > errors::none) return -1;

		state_next = one(symbols_array,state_next);
		if(error > errors::none) return -1;

		return state_next;
	}

	/*
	*\brief Uno o mas de los simbolos
	*\param prefixs lista de simbolos que determinan que la palabra ha terminado
	*\param token token retornado por el analizador si detecta la palabra
	*/
	constexpr State almost_one(const array<Symbol>& symbols_array, Token token, const array<Symbol>& prefixs_array)
	{
		State state_next = one(symbols_array);
		if(error > errors::none) return -1;

		state_next = one(symbols_array,state_next);
		if(error > errors::none) return -1;

		circular(symbols_array,state_next);

		prefixing(state_next,prefixs_array,token);

		return state_next;
	}



protected:
	State index;
	errors error;

	Symbol symbols[amount_symbols];
	Transition<Token, State> tt[amount_states][amount_transitions];

	static const State initial_state = 0;
};


template<typename Symbol /*Input*/,typename Token,typename State/*State*/,typename TT>
class LC
{
public:

public:
	LC(const TT& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),index(0),initial_status(0),actual_status(initial_status)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
		_echo = false;
#endif
	}

	bool is_accepted()
	{
        if(actual_transition->indicator == Indicator::accept and actual_transition->next == 0 and actual_transition->token > Token::none) return true;

        return false;
	}

    Token next()
	{
        actual_status = initial_status;
		actual_transition = NULL;
		string_start = index;
		string_leng = 0;
	    const Symbol* input = (const Symbol*)*buffer;
		//prefix_start = 0;

        while(index < buffer->size() and (size_t)actual_status < table->size())
        {
            //std::cout << "whiel : Step 0\n";

            //std::cout << "whiel : Step 1\n";
            //>>>reading data
            {
                //input = buff[index];
                actual_transition = table->get(actual_status,input[index]);
                next_status = actual_transition->next;
			}

            //std::cout << "whiel : Step 2\n";
            //>>>working
            {
				table->print(std::cout,actual_status,input[index]);
				//std::cout << "Input : '" << '\n' << "'\n";

				//>>>
            }

            //std::cout << "whiel : Step 3\n";
            //>>>finalizing
            {
                //string_leng++;
                if(is_accepted()) break;
            }

			//repetir loop
			{
				index++;
				actual_status = next_status;
				prev_transition = actual_transition;
			}
        }

        {
            if(index == string_start) string_leng = 1;
            else string_leng = index - string_start;
            //index--;
        }

        if(prev_transition) return prev_transition->token;
        else if(index >= buffer->size()) return Token::eoi;

		return Token::none;
	}

	void next(Tokenized<Symbol,Token>& content)
	{
		content.string.clear();
		content.token = next();

		//std::cout << "Start : " << string_start << ", leng :" << string_leng << "\n";
		//const Symbol* buff = (const Symbol*)buffer;
        content.string = std::string(get_string_base(),string_leng);

	}

	size_t get_string_length()const
	{
	    return string_leng;
	}
	const Symbol* get_string_base()const
	{
	    const Symbol* base = (const Symbol*)*buffer;
	    return base + string_start;
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
	//Symbol input;
	size_t index,string_start,string_leng;//prefix_index
    const Transition<Token, State> *actual_transition, *prev_transition;//, *prefix_transition, *acceptable_transition;
    const State initial_status;
	State actual_status,next_status;//numero del estado actual del automata
    //bool prefix_start;
#ifdef OCTETOS_CORE_ENABLE_DEV
	bool _echo;
#endif

};

}


#endif
