

#ifndef OCTETOS_CORE_LC_V3_HH
#define OCTETOS_CORE_LC_V3_HH

//#define TT_PARAMS(T) T,sizeof (T) / sizeof (T[0])

#include <cstddef>
#include <array>
//#include "arrays.hh"
#include "Buffer-v3.hh"

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
	string,
	identifier,
	keyword,
	softkeyword,
	expresion,

};

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
	none,
	accept,//estado de aceptacion, sin embargo deve terminar de inmediato
	acceptable,//estado de aceptacion, sin embario que termine de inmediato
	reject,//rechazar y terminar de imendiato
	rejectable,//estado de rechazo, sin embargo no es necesario que termina de inmediato
	prefix,//prefijo de analisis
	error,//
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
	case Indicator::reject: return "reject";
	case Indicator::prefix: return "prefix";
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
				TT_BASE::at(status)[(size_t)i].indicator = Indicator::reject;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = Token::none;
			}
			return true;
		}
		constexpr bool initial(Status status,Token token)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = Indicator::reject;
				TT_BASE::at(status)[i].next = 0;
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
		/*Status add_status()
		{
			TT_BASE::resize(TT_BASE::size() + 1);
			Status status = TT_BASE::size() - 1;
			return status;
		}*/
		bool acceptable(Status status, Symbol symbol,Token token,Status next)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::acceptable;
			TT_BASE::at(status)[symbol].token = token;
			TT_BASE::at(status)[symbol].next = next;
			return true;
		}
		bool accept(Status status, Symbol symbol,Token token)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::accept;
			TT_BASE::at(status)[symbol].token = token;
			TT_BASE::at(status)[symbol].next = 0;
			return true;
		}
		bool prefix(Status status, Symbol symbol,Status next)
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
		/*bool terminate(Status status, Symbol symbol)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::terminate;
			TT_BASE::at(status)[symbol].token = Token::none;
			TT_BASE::at(status)[symbol].next = 0;
			return true;
		}*/
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
	    index(0),actual_status(0),initial_status(0),prefix_start(false),prefix_end(false)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
		_echo = false;
#endif
	}

    Token next()
	{
	    //std::cout << "A<>::next : Step 0\n";
	    //if(actual_state == Indicator::finalized) return Tokens::none;
        actual_status = initial_status;
        actual_state = Indicator::none;
        prefix_start = false;
        prefix_end = false;
        prefix_index = 0;
		accepted_transition = NULL;

	    const Symbol* buff = (const Symbol*)*buffer;
        while(index < buffer->size() and actual_status < table->size())
        {
            //std::cout << "whiel : Step 0\n";
            //if(actual_state == Indicator::finalized) break;

            //std::cout << "whiel : Step 1\n";
            //>>>reading data
            {
                input = buff[index];
                if(not input)
                {
                    break;
                }
                actual_transition = &(table->at(actual_status).at(input));
                actual_state = step(actual_transition);
                next_status = actual_transition->next;
				if (actual_transition->indicator == Indicator::prefix and prefix_index == 0) accepted_transition = actual_transition;
                if(actual_transition->indicator == Indicator::prefix) prefix_index++;
                if(actual_transition->indicator == Indicator::prefix and prefix_index > 0) prefix_start = true;
                if(actual_transition->token == Tokens::none and next_status < 0) prefix_end = true;

			}

            //std::cout << "whiel : Step 2\n";
            //>>>working
            {
                /*if (prefix_start and prefix_end) std::cout << actual_status << "--'" << input << "'->end\n";
                else std::cout << actual_status << "--'" << input << "'->" << next_status << "\n";
				std::cout << "index : " << index << "\n";*/

            }

            //std::cout << "whiel : Step 3\n";
            //>>>finalizing
            {
                if(actual_state == Indicator::accept)
                {
                    index++;
                    actual_status = next_status;
					if (actual_transition->indicator == Indicator::accept) break;
                }
                else if(actual_state == Indicator::reject)
                {
                    break;
                }


            }
        }
#ifdef OCTETOS_CORE_ENABLE_DEV
		/*if (actual_state == Indicator::accept)
		{
			std::cout << "Acepted\n";
		}
		else if (actual_state == Indicator::reject)
		{
			std::cout << "Rejected\n";
		}
		else
		{

		}*/
#endif
		if(prefix_end) index -= prefix_index;
		if (actual_state == Indicator::accept)
		{
			if (prefix_end) return accepted_transition->token;
		}
		else if (actual_state == Indicator::reject)
		{
			return Tokens::none;
		}
		else
		{
			return Tokens::none;
		}

		return Tokens::none;
	}

#ifdef OCTETOS_CORE_ENABLE_DEV
	void echo(bool e)
	{
		_echo = e;
	}
#endif
	bool is_accepted()const
	{
		if (actual_state == Indicator::accept) return true;

		return false;
	}
private:

	/**
	*\brief Determina el estado actual del automata, solo puede estar en 1 de los sigueinetes estados: inicial,aceptacion, rechazo, error o finalizado.
	*\param t La trasicion actual que afecta al automata.
	*/
    Indicator step(const Transition<Token,Status>* t)
    {
        switch(actual_state)
        {
        case Indicator::none:
            if(actual_status != initial_status) return Indicator::error;
            switch(t->indicator)
            {
            case Indicator::none:
                return Indicator::error;
            case Indicator::accept:
                return Indicator::accept;
            case Indicator::acceptable:
                return Indicator::accept;
            case Indicator::reject:
                return Indicator::reject;
            case Indicator::rejectable:
                return Indicator::reject;
            case Indicator::prefix:
                return Indicator::accept;
            case Indicator::error:
                return Indicator::error;
            }
            break;
        case Indicator::accept:
            switch(t->indicator)
            {
            case Indicator::none:
                return Indicator::reject;
            case Indicator::accept:
                return Indicator::accept;
            case Indicator::acceptable:
                return Indicator::accept;
            case Indicator::reject:
                return Indicator::reject;
            case Indicator::rejectable:
                return Indicator::reject;
            case Indicator::prefix:
                return Indicator::accept;
            case Indicator::error:
                return Indicator::error;
            }
            break;
        case Indicator::reject:
            return Indicator::reject;
        case Indicator::error:
            return Indicator::error;
        case Indicator::acceptable:
        case Indicator::rejectable:
        case Indicator::prefix:
            return Indicator::error;
        }

        return Indicator::error;
    }


private:
	const TT<Symbol,Token,Status,TT_BASE>* table;
	Buffer<Symbol>* buffer;
	Symbol input;
	Indicator actual_state;//estado del automata actual
	size_t index,prefix_index;
    const Transition<Token,Status> *actual_transition, * accepted_transition;
    Status actual_status,next_status;//numero del estado actual del automata
    const Status initial_status;
    bool prefix_start,prefix_end;
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
