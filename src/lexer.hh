

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
	none = -1,
	NUL		= 0,
	SOH,
	STX,
	EOT,


	US 		= 31,
	space,


	plus 	= '+',//
	minus 	= '-',
	dot 	= '.',
	
	
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


/**
*\brief DFA type A
*
*/
template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/>
class A 
{
public:
	//template<typename T = Token>
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
	/*bool check(const Transition (*t)[MAX_SIMBOLS],size_t length, bool echo)
	{
		for(unsigned int i = 0; i < length; i++)
		{
			for(unsigned short j = 0; j < 128; j++)
			{
				//std::cout << "cheking (" << i << "," << j << ")\n";
				if(t[i][j].indicator ==  Indicator::reject and t[i][j].next == 0 and t[i][j].token == Token::none) continue;
				if(t[i][j].indicator ==  Indicator::none and t[i][j].next > 0 and t[i][j].token == Token::none) continue;
				if(t[i][j].indicator ==  Indicator::prefix and t[i][j].next == 0 and t[i][j].token == Token::none) continue;
				if(t[i][j].indicator ==  Indicator::accept and t[i][j].token != Token::none) continue;
				if(t[i][j].indicator ==  Indicator::acceptable and t[i][j].token != Token::none) continue;
				//if(t[i][j].indicator ==  Indicator::Left_Eat and t[i][j].token == Tokens::none) continue;
				//if(t[i][j].indicator ==  Indicator::Left_Eat and t[i][j].token < Tokens::none) continue;				
				if(echo) std::cout << "Fail on cheking table transiotion : " << i << " - " << j << "\n";
			}
		}

		return true;
	}*/

	typedef std::vector<std::array<Transition,MAX_SIMBOLS>> TT_BASE;
	class TT : public TT_BASE
	{
	public:
		TT() = default;
		
		bool initial(Status status)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = Indicator::reject;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = Token::none;
			}
			return true;
		}
		bool initial(Status status,Token token)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = Indicator::reject;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = token;
			}
			return true;
		}
		bool initial(Status status,Indicator indicator,Token token)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = indicator;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = token;
			}
			return true;
		}
		bool initial(Status status,Indicator indicator)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				TT_BASE::at(status)[i].indicator = indicator;
				TT_BASE::at(status)[i].next = 0;
				TT_BASE::at(status)[i].token = Token::none;
			}
			return true;
		}
		Status add_status()
		{
			TT_BASE::resize(std::vector<std::array<Transition,MAX_SIMBOLS>>::size() + 1);
			std::array<Transition,MAX_SIMBOLS>& t = TT_BASE::back();	
			Status status = TT_BASE::size() - 1;
			initial(status);
			return status;
		}
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

	/*A(const Transition (*t)[MAX_SIMBOLS],size_t l,Buffer<Symbol>& b) : table(t),table_length(l),index(0),buffer(&b)
	{
	}*/
	A(const TT& tt,Buffer<Symbol>& b) : table(&tt),index(0),buffer(&b),actual(0),post(0)
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
		//index = 0;
		index_prefix = 0;
		actual_transition = NULL;
		acceptable_transition = NULL;
		prefix_transition = NULL;
		//std::cout << "actual : " << actual << "\n";
		//std::cout << "index : " << index << "\n";
		//std::cout << "post : " << post << "\n";

		while(post < table_length and index < buffer->size())
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
			default:
				acceptable_transition = NULL;
				prefix_transition = NULL;
				break;
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
	const TT* table;
	size_t table_length,index,index_prefix;
	Buffer<Symbol>* buffer;
	const Transition* actual_transition;
	const Transition* acceptable_transition;
	const Transition* prefix_transition;
	Status post,actual,prefix_last,acceptable_last;
	Symbol input;
#ifdef OCTETOS_CORE_ENABLE_DEV
	bool _echo;
#endif
};







template<typename Token>
struct Transition //transition B
{
	Status current;//key
	Token input;//key
	
	Indicator indicator;
	Status next;
	Token token;
};



template<typename Symbol /*Input*/,typename Token,typename Status/*Status*/> 
class B
{
public:
	B(const arrays::Wrapper<Transition<Token>>& tt)
	{
		
	}

private:
	Status actual;
};

}


#endif