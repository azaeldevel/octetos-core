

#ifndef OCTETOS_CORE_LC_V3_HH
#define OCTETOS_CORE_LC_V3_HH

#define TT_PARAMS(T) T,sizeof (T) / sizeof (T[0])

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
	acceptable,//estado de aceptacion, sin embario que termine de inmediato
	accept,//estado de aceptacion, sin embargo deve terminar de inmediato
	rejectable,//estado de rechazo, sin embargo no es necesario que termina de inmediato
	reject,//rechazar y terminar de imendiato
	prefix,//prefijo de analisis
	error,//
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
	A(const TT<Symbol,Token,Status,TT_BASE>& tt,Buffer<Symbol>& b) : table(&tt),buffer(&b),state(Indicator::none),index(0),actual_status(0),initial_status(0)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
	_echo = false;
#endif
	}

    Token next()
	{
	    const Symbol* buff = (const Symbol*)*buffer;
        while(index < buffer->size() and actual_status < table->size())
        {
            input = buff[index];
			if(Buffer<Symbol>::EOB == input )
			{
				//std::cout << "if(" << int(Buffer<Symbol>::EOB) << " == " << int(input) << ") ..\n";
				return Tokens::none;
			}
			actual_transition = &(table->at(actual_status).at(input));
			state = step(actual_transition);


        }

        return Tokens::none;
	}

#ifdef OCTETOS_CORE_ENABLE_DEV
	void echo(bool e)
	{
		_echo = e;
	}
#endif
private:
    Indicator step(const Transition<Token,Status>* t)
    {
        switch(state)
        {
        case Indicator::none:
            if(actual_status != initial_status) return Indicator::error;
            switch(state)
            {
            case Indicator::none:
                if(actual_status != initial_status) return Indicator::error;

                break;
            case Indicator::acceptable:

                break;
            case Indicator::accept:

                break;
            case Indicator::reject:

                break;
            case Indicator::prefix:

                break;
            case Indicator::error:

                break;
            }
            break;
        case Indicator::acceptable:

            break;
        case Indicator::accept:

            break;
        case Indicator::reject:

            break;
        case Indicator::prefix:

            break;
        case Indicator::error:

            break;
        }

        return Indicator::none;
    }
private:
	const TT<Symbol,Token,Status,TT_BASE>* table;
	Buffer<Symbol>* buffer;
	Symbol input;
	Indicator state;
	size_t index;
    const Transition<Token,Status> *actual_transition;
    Status actual_status;
    const Status initial_status;
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
