

#ifndef OCTETOS_CORE_DFA
#define OCTETOS_CORE_DFA

#define TT_PARAMS(T) T,sizeof (T) / sizeof (T[0])

#include <cstddef>
#include <array>
#include <arrays.hh>
#include <Buffer-v3.hh>

namespace oct::core::v3::lc
{
typedef int Status;
typedef int Token;
typedef size_t Index;
static const unsigned char MAX_SIMBOLS = 128;

enum class tokens : int
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
template<typename T>
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
	
	/*T operator[](uintmax_t i)const
	{	
		//std::cout << "if(" << i << " < " << _size << ") return " << int(buffer[i]) << "\n";
		uintmax_t _index = i + base;
		if(_index < Buffer_Base::_size) return Buffer_Base::buffer[_index];
		
		return T(0);
	}
	void jump(uintmax_t b)
	{
		base = b;
	}*/
protected:
	//uintmax_t base;
	
private:
};

enum class Indicator : Status
{
	none,
	acceptable,//estado de aceptacion
	accept,//estado de aceptacion, sin embargo deve terminar de inmediato
	reject,//rechazar y terminar de imendiato
	prefix,//prefijo de analisis
	terminate,//terminar de enmediato
	unknow,//no es simbolo del lenguaje
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
	case Indicator::terminate: return "terminate";
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
		bool terminate(Status status, Symbol symbol)
		{
			TT_BASE::at(status)[symbol].indicator = Indicator::terminate;
			TT_BASE::at(status)[symbol].token = Token::none;
			TT_BASE::at(status)[symbol].next = 0;
			return true;
		}
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
	A(const TT<Symbol,Token,Status,TT_BASE>& tt,Buffer<Symbol>& b) : table(&tt),index(0),buffer(&b),actual(0),post(0)
	{
#ifdef OCTETOS_CORE_ENABLE_DEV
	_echo = false;
#endif
	}

	bool is_accepted() const
	{
		if(not actual_transition) return false; 

		if(actual_transition->indicator == Indicator::accept) return true;
		if(actual_transition->indicator == Indicator::acceptable) return true;
		if(prefix_transition and acceptable_transition) if(acceptable_transition->indicator == Indicator::acceptable) return true;

		return false;
	}
	Token next()
	{
		//std::cout << "next : Step1\n";
		//index = 0;
		index_prefix = 0;
		actual_transition = NULL;
		acceptable_transition = NULL;
		prefix_transition = NULL;
		//std::cout << "actual : " << actual << "\n";
		//std::cout << "index : " << index << "\n";
		//std::cout << "post : " << post << "\n";

		//std::cout << "next : Step1\n";
		while(index < buffer->size())
		{
			//>>>seccion inicial
#ifdef OCTETOS_CORE_ENABLE_DEV
			//std::cout << "while : Step 1\n";
			//std::cout << "index : " << index << "\n";
			//std::cout << "actual : " << actual << "\n";
			//std::cout << "post : " << post << "\n";
#endif
			input = buffer->operator[](index);
			//std::cout << "while : Step 2\n";
			//std::cout << "input : " << input << "\n";
			if(Buffer<Symbol>::EOB == input )
			{
				//std::cout << "if(" << int(Buffer<Symbol>::EOB) << " == " << int(input) << ") ..\n";
				return get_token();
			}
						
			//>>>seccion lectura
			//std::cout << "while : Step 3\n";
			actual = post;//no importa que actual_transition sea la transicion previa
			//std::cout << "while : Step 4\n";
			actual_transition = &(table->at(actual).at(input));
			//std::cout << "while : Step 5\n";
			post = actual_transition->next;	
#ifdef OCTETOS_CORE_ENABLE_DEV
			//std::cout << "while : Step 6\n";
			//std::cout << "index : " << index << "\n";
			//std::cout << "index_prefix : " << index_prefix << "\n";
			//std::cout << "actual : " << actual << "\n";
			//std::cout << "post : " << post << "\n";
			//std::cout << "input : " << input << "\n";
			if(_echo)print();
#endif
			if(prefix_transition)
			{
				//std::cout << "if(prefix_transition)...\n";
				if(actual_transition->indicator != Indicator::prefix) 
				{
					//std::cout << "if(actual_transition->indicator != Indicator::prefix)...\n";
					index -= index_prefix;
					post = actual;
					//std::cout << "\n";		
					return get_token();
				}
			}
			
			//>>>seccion evaluacion
			//std::cout << "while : Step 7\n";
			switch(actual_transition->indicator)
			{
			case Indicator::acceptable:
				acceptable_transition = actual_transition;
				acceptable_last = actual;
				break;
			case Indicator::accept:
				acceptable_transition = actual_transition;
				acceptable_last = actual;
				actual = post;
				index++;
				return get_token();
			case Indicator::prefix:
				;//puede aceptar n prefijos pero deve ser continuos
				index_prefix++;
				prefix_transition = actual_transition;
				prefix_last = actual;
				break;
			case Indicator::unknow:
			case Indicator::reject:
				acceptable_transition = NULL;
				prefix_transition = NULL;
				actual = post;
				index++;
				return get_token();
			case Indicator::none:
				break;
			default:
				acceptable_transition = NULL;
				prefix_transition = NULL;
				return get_token();
			};
			
			
			index++;
			//std::cout << "\n";			
		}
		//std::cout << "\n";	
		
		return get_token();
	}
#ifdef OCTETOS_CORE_ENABLE_DEV
	void echo(bool e)
	{
		_echo = e;		
	}
#endif
private:
	Token get_token()
	{
		if(not actual_transition) return Token::none;
		
		if(actual_transition->indicator == Indicator::accept)
		{
			return actual_transition->token;
		}
		else if(prefix_transition and acceptable_transition)
		{
			return acceptable_transition->token;//se retorna el ultimo token de acpetacion
		}

		return actual_transition->token;
	}
	void print()
	{
		std::cout << actual << " -- (" << input << " - " << to_string(actual_transition->indicator) << ") --> " << post << "\n";
	}
	
private:
	const TT<Symbol,Token,Status,TT_BASE>* table;
	size_t index,index_prefix;
	Buffer<Symbol>* buffer;
	const Transition<Token,Status>* actual_transition;
	const Transition<Token,Status>* acceptable_transition;
	const Transition<Token,Status>* prefix_transition;
	Status post,actual,prefix_last,acceptable_last;
	Symbol input;
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