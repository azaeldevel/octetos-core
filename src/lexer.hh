

#ifndef OCTETOS_CORE_LC_V3_HH
#define OCTETOS_CORE_LC_V3_HH

//#define TT_PARAMS(T) T,sizeof (T) / sizeof (T[0])

#include <cstddef>
#include <array>
//#include "arrays.hh"
#include "Buffer-v3.hh"
#include <string>
#include <list>

namespace oct::core::v3::lc
{
typedef int Status;
typedef int Token;
typedef size_t Index;
static const unsigned char MAX_SIMBOLS = 128;

enum class Tokens : int
{//https://www.asciitable.com/,https://www.rapidtables.com/code/text/ascii-table.html
	none = -1,//ASCII>>>
	NUL		= 0,
	SOH,
	STX,
	EOT,


	US 		= 31,
	space,


	plus 	= '+',
	minus 	= '-',
	dot 	= '.',

	DEL		= 127,
	//UTF >>>
	tokens	= 0x11000000,
	number,
	integer,
	decimal,//incluye punto flotante
	letter,//caracter
	digit,//cararte digito
	string,
	identifier,
	keyword,
	softword,
	expresion,
	semver_operator,
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
	case Tokens::semver_operator:
		return "semver operator";
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

#define Buffer_Base core::v3::Buffer<T>
/**
*\brief
*
*/
/*template<typename T>
class Buffer : public Buffer_Base
{
public:

public:
	Buffer(const std::filesystem::path& file) : core::v3::Buffer<T>(file)//,base(0)
	{
	}
	Buffer(const T* string) : core::v3::Buffer<T>(string)//,base(0)
	{
	}
	~Buffer()
	{
	}

	T operator[](uintmax_t i)const
	{
		//std::cout << "if(" << i << " < " << _size << ") return " << int(buffer[i]) << "\n";
		uintmax_t _index = i + base;
		if(_index < Buffer_Base::_size) return Buffer_Base::buffer[_index];

		return T(0);
	}
	void jump(uintmax_t b)
	{
		base = b;
	}
protected:
	//uintmax_t base;

private:
};*/

enum class Indicator : Status
{
	none,//no es us estado determinado, sin mebago, no cambia el estado previo por lo que se podria decir no no tiene efecto en el estado
	accept,//estado de aceptacion, sin embargo deve terminar de inmediato
	acceptable,//estado de aceptacion, sin embario que termine de inmediato
	//reject,//rechazar y terminar de imendiato
	//rejectable,//estado de rechazo, sin embargo no es necesario que termina de inmediato
	//prefix,//prefijo de analisis
	//error,//
	//finalized,
	//terminate,//terminar de enmediato
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

	//TODO: todos los elementos deven matener el automata en el estado aceptable, termina cuando no es aceptable la cadena
	template<typename Token,typename Status/*Status*/>
	struct Transition
	{
		Indicator indicator;
		Status next;
		Token token;

		void print(std::ostream& out) const
		{
			out << next << " - ";
			const char* strtoken = to_string(token);
			if (strtoken) out << strtoken << ", ";
			out << to_string(indicator);
		}
	};

	struct Selector
	{
		unsigned int i;
		unsigned short j;
	};

	template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/,typename TT_BASE>
	class TT : public TT_BASE
	{
	public:
		TT() = default;

		constexpr bool initial(Status status)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				//std::cout << "initial : " << status << " - " << i << "\n";
				TT_BASE::at(status)[i].indicator = Indicator::none;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = Token::none;
			}
			return true;
		}
		constexpr bool initial(Status status,Token token)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = Indicator::none;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = token;
			}
			return true;
		}
		constexpr bool digits(Status status, Indicator indicator,Status next, Token token)
		{
			for (size_t i = 48; i < 58; i++)
			{
				TT_BASE::at(status)[i].indicator = indicator;
				TT_BASE::at(status)[i].next = next;
				TT_BASE::at(status)[i].token = token;
			}

			return true;
		}
		constexpr bool letters(Status status, Indicator indicator, Status next, Token token)
		{
			for (size_t i = 65; i < 91; i++)
			{
				TT_BASE::at(status)[i].indicator = indicator;
				TT_BASE::at(status)[i].next = next;
				TT_BASE::at(status)[i].token = token;
			}
			for (size_t i = 97; i < 123; i++)
			{
				TT_BASE::at(status)[i].indicator = indicator;
				TT_BASE::at(status)[i].next = next;
				TT_BASE::at(status)[i].token = token;
			}

			return true;
		}
		constexpr bool initial(Status status,Indicator indicator,Token token)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = indicator;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = token;
			}
			return true;
		}
		constexpr bool initial(Status status,Indicator indicator)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = indicator;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = Token::none;
			}
			return true;
		}
		bool acceptable(Status status, Symbol symbol,Token token,Status next)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::acceptable;
			TT_BASE::at(status)[symbol].token = token;
			TT_BASE::at(status)[symbol].next = next;
			return true;
		}
		/*
		bool accept(Status status, Symbol symbol, Token token)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::accept;
			TT_BASE::at(status)[symbol].token = token;
			TT_BASE::at(status)[symbol].next = 0;
			return true;
		}
		bool prefix(Status status, Symbol symbol, Status next)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::prefix;
			TT_BASE::at(status)[symbol].token = Token::none;
			TT_BASE::at(status)[symbol].next = next;
			return true;
		}
		bool prefix(Status status, Symbol symbol)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::prefix;
			TT_BASE::at(status)[symbol].token = Token::none;
			TT_BASE::at(status)[symbol].next = -1;
			return true;
		}
		*/
	private:

	};

/**
*\brief DFA type A
*
*/
template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/,typename TT_BASE>
class A
{
public:
	A(const TT<Symbol,Token,Status,TT_BASE>& tt,Buffer<Symbol>& b) :
	    table(&tt),buffer(&b),actual_state(Indicator::none),
	    index(0),actual_status(0),initial_status(0)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
		_echo = false;
#endif
	}

    Token next()
	{
	    //std::cout << "A<>::next : Step 0\n";
        actual_status = initial_status;
        actual_state = Indicator::none;
        /*
		prefix_start = false;
        prefix_end = false;
        prefix_index = 0;
		*/
		actual_transition = NULL;
		prev_transition = NULL;
		token_begin = index;
		token_end = 0;

	    const Symbol* buff = (const Symbol*)*buffer;
        while(index < buffer->size() and actual_status < table->size())
        {
            //std::cout << "whiel : Step 0\n";
            //if(actual_state == Indicator::finalized) break;

            //std::cout << "whiel : Step 1\n";
            //>>>reading data
            {
                input = buff[index];
                actual_transition = &(table->at(actual_status).at(input));
				actual_state = actual_transition->indicator;
                next_status = actual_transition->next;

				//
				

			}

            //std::cout << "whiel : Step 2\n";
            //>>>working
            {
				std::cout << actual_status << "--'" << input << "'->";
				actual_transition->print(std::cout);
				std::cout << "\n";
				

            }

            //std::cout << "whiel : Step 3\n";
            //>>>finalizing
            {
				if (actual_state == Indicator::none) break;
            }

			//repetir loop
			{
				index++;
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
		/*std::cout << "Finalizando ..\n";
		std::cout << actual_status << "--'" << input << "'->";
		if (prev_transition) prev_transition->print(std::cout);
		std::cout << "\n";*/
		if (prev_transition) 
		{
			if (prev_transition->indicator == Indicator::accept or prev_transition->indicator == Indicator::acceptable)
			{
				actual_state = Indicator::accept;
			}
			return prev_transition->token;
		}
		return Tokens::none;
	}
	bool next(const Symbol* str)
	{
		size_t leng = strlen(str);
		const Symbol* buf = (const Symbol*)*buffer;
		buf += index;
		if (strncmp(buf, str, leng) == 0)
		{
			actual_state = Indicator::accept;
			index += leng;
			return true;
		}
		else
		{
			actual_state = Indicator::none;
			return false;
		}
	}
	bool next(Symbol s)
	{
		const Symbol* buf = (const Symbol*)*buffer;
		buf += index;
		if (buf[0] == s)
		{
			actual_state = Indicator::accept;
			index++;
			return true;
		}
		else
		{
			actual_state = Indicator::none;
			return false;
		}
	}
	Token next(std::list<std::string>& tk)
	{
		Token next_token = next();
		tk.push_back("");
		std::string& str = tk.back();
		const Symbol* buf = (const Symbol*) *buffer;
		buf += token_begin;
		size_t token_len = token_end - token_begin;
		std::cout << "Buffer : " << buf[0] << " - " << token_len << "\n";
		str.append(buf + token_len,token_len);

		return next_token;
	}

#ifdef OCTETOS_CORE_ENABLE_DEV
	void echo(bool e)
	{
		_echo = e;
	}
#endif
	bool is_accepted()const
	{
		if (actual_state == Indicator::accept or actual_state == Indicator::acceptable) return true;

		return false;
	}
private:


private:
	const TT<Symbol,Token,Status,TT_BASE>* table;
	Buffer<Symbol>* buffer;
	Symbol input;
	Indicator actual_state;//estado del automata actual
	size_t index,token_begin,token_end;//prefix_index
    const Transition<Token,Status> *actual_transition, *accepted_transition, *prev_transition;
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
