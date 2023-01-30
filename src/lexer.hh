

#ifndef OCTETOS_CORE_LC_V3_HH
#define OCTETOS_CORE_LC_V3_HH

//#define TT_PARAMS(T) T,sizeof (T) / sizeof (T[0])

#include <cstddef>
#include <array>
//#include "arrays.hh"
#include "Buffer-v3.hh"
#include <string>
#include <list>

namespace oct::core::v3::lex
{
typedef int Status;
typedef int Token;
typedef size_t Index;
static const unsigned char ASCII_LENGTH = 128;

enum class Tokens : int
{//https://www.charset.org/utf-8,https://www.asciitable.com/,https://www.rapidtables.com/code/text/ascii-table.html
	none = -1,
	//ASCII>>>
	NUL = 0,
	SOH,
	STX,
	EOT,


	US = 31,
	space,


	plus	= '+',
	minus	= '-',
	dot		= '.',

	EuroSign	= 218,
	//>>>Extended ASCII






	y_Diaeresis = 255,//�
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

enum class Indicator : Status
{
	none,//no es us estado determinado, sin mebago, no cambia el estado previo por lo que se podria decir no no tiene efecto en el estado
	accept,//estado de aceptacion, sin embargo deve terminar de inmediato
	acceptable,//estado de aceptacion, sin embario que termine de inmediato
	reject,//rechazar y terminar de imendiato
	rejectable,//estado de rechazo, sin embargo no es necesario que termina de inmediato
	//prefix,//prefijo de analisis
	//finalized,
	error,//el simbolo no se esperaba
	unknow,//simbolo que no pertenece al lenguaje
	terminate,//terminar de enmediato, sin embargo no tienne efecto en el estado actual del automamta(podria decirse qu es lo mismo que el buffer se termine)
};
const char* to_string(Indicator i)
{
	switch(i)
	{
	case Indicator::none: return "none";
	case Indicator::acceptable: return "acceptable";
	case Indicator::accept: return "accept";
	//case Indicator::reject: return "reject";
	//case Indicator::prefix: return "prefix";
	//case Indicator::terminate: return "terminate";
	}
	return "Unknow";
}

	template<typename Token,typename Status/*Status*/>
	struct Transition
	{
		Indicator indicator;
		Status next;
		Token token;

		/*void print(std::ostream& out) const
		{
			out << next << " - ";
			const char* strtoken = to_string(token);
			if (strtoken) out << strtoken;
			//out << to_string(indicator);
		}*/
	};
		
	template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/>
	class TT : public std::vector<std::vector<Transition<Token, Status>>>
	{
	public:
		typedef std::vector<std::vector<Transition<Token, Status>>> TT_BASE;

	public:
		constexpr TT(size_t size)
		{
			TT_BASE::resize(size);
			for (size_t i = 0; i < size; i++)
			{
				TT_BASE::at(i).resize(ASCII_LENGTH);
				initial(i);
			}
		}

		constexpr TT(const TT& tt)
		{
			TT_BASE::resize(tt.size());
			for (size_t s = 0; s < tt.size(); s++)
			{
				TT_BASE::at(s).resize(tt.at(s).size());
				for (size_t t = 0; t < TT_BASE::at(s).size(); t++)
				{
					TT_BASE::at(s).at(t) = tt[s][t];
				}
			}
		}

		constexpr bool initial(Status status)
		{
			for(size_t i = 0; i < ASCII_LENGTH; i++)
			{
				//std::cout << "initial : " << status << " - " << i << "\n";
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = Token::none;
				TT_BASE::at(status)[i].indicator = Indicator::unknow;
			}
			return true;
		}
		/*constexpr bool initial(Status status, Token token)
		{
			for(size_t i = 0; i < ASCII_LENGTH; i++)
			{
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = token;
			}
			return true;
		}*/
		constexpr bool numbers(Status status, Token token,Status next)
		{
			for (size_t i = 48; i < 58; i++)
			{
				TT_BASE::at(status)[i].next = next;
				TT_BASE::at(status)[i].token = token;
				TT_BASE::at(status)[i].indicator = Indicator::acceptable;
			}

			return true;
		}
		constexpr bool alphabet(Status status, Token token, Status next)
		{
			for (size_t i = 65; i < 91; i++)
			{
				TT_BASE::at(status)[i].next = next;
				TT_BASE::at(status)[i].token = token;
				TT_BASE::at(status)[i].indicator = Indicator::acceptable;
			}
			for (size_t i = 97; i < 123; i++)
			{
				TT_BASE::at(status)[i].next = next;
				TT_BASE::at(status)[i].token = token;
				TT_BASE::at(status)[i].indicator = Indicator::acceptable;
			}

			return true;
		}
		constexpr bool symbol(Status status, Token token, Status next, Symbol i)
		{
			TT_BASE::at(status)[i].next = next;
			TT_BASE::at(status)[i].token = token;
			TT_BASE::at(status)[i].indicator = Indicator::acceptable;

			return true;
		}

	private:

	};

	template<typename Symbol /*Input*/>
	struct Content
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
template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/>
class A
{
public:

public:
	A(const TT<Symbol,Token,Status>& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),actual_state(false),index(0),actual_status(0),initial_status(0)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
		_echo = false;
#endif
	}

    Token next()
	{
	    //std::cout << "A<>::next : Step 0\n";
        actual_status = initial_status;
        actual_state = false;
		actual_transition = NULL;
		prev_transition = NULL;
		token_start = index;
		token_end = 0;
		bool terminate = false;

	    const Symbol* buff = (const Symbol*)*buffer;
        while(index < buffer->size() and actual_status < table->size())
        {
            //std::cout << "whiel : Step 0\n";

            //std::cout << "whiel : Step 1\n";
            //>>>reading data
            {
                input = buff[index];
                actual_transition = (const Transition<Token, Status>*) & (table->at(actual_status).at(input));
				actual_state = actual_transition->token > Tokens::none;
                next_status = actual_transition->next;

				//verificando terminacion
				/*
				if (actual_transition->indicator == Indicator::unknow) terminate = true;
				else if (actual_transition->indicator == Indicator::reject) terminate = true;
				else if (actual_transition->indicator == Indicator::terminate) terminate = true;
				else if (actual_transition->indicator == Indicator::error) terminate = true;
				*/
			}

            //std::cout << "whiel : Step 2\n";
            //>>>working
            {
				/*
				std::cout << actual_status << "--'" << input << "'->";
				actual_transition->print(std::cout);
				std::cout << "\n";
				*/
            }

            //std::cout << "whiel : Step 3\n";
            //>>>finalizing
            {
				if (not actual_state) break;
				if (terminate) break;
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
		/*
		std::cout << "Finalizando ..\n";
		std::cout << actual_status << "--'" << input << "'->";
		if (prev_transition) prev_transition->print(std::cout);
		std::cout << "\n";
		*/
		if (prev_transition)
		{
			actual_state = true;
			return prev_transition->token;
		}
		else if (actual_transition->indicator == Indicator::unknow) return (Tokens)input;
		else if (actual_transition->indicator == Indicator::reject) return (Tokens)input;
		else if (actual_transition->indicator == Indicator::terminate) return (Tokens)input;
		else if (actual_transition->indicator == Indicator::error) return (Tokens)input;

		return Tokens::none;
	}
	Tokens next(Content<Symbol>& content)
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
	bool is_accepted()const
	{
		return actual_state;
	}
private:


private:
	const TT<Symbol,Token,Status>* table;
	Buffer<Symbol>* buffer;
	Symbol input;
	bool actual_state;//estado del automata actual
	size_t index,token_start,token_end;//prefix_index
    const Transition<Token,Status> *actual_transition, *prev_transition;
    Status actual_status,next_status;//numero del estado actual del automata
    const Status initial_status;
    //bool prefix_start,prefix_end;
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
