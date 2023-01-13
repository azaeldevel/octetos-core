

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

/**
*\brief
*
*/
template<typename T>
class Buffer : public core::v3::Buffer<T>
{
public:
	
public:
	Buffer(const std::filesystem::path& file) : core::v3::Buffer<T>(file)
	{
	}
	Buffer(const T* string) : core::v3::Buffer<T>(string)
	{
	}
	~Buffer()
	{
	}
	
protected:
	T* base;
	
private:
	T* buffer;
	std::uintmax_t _size;
	std::filebuf* pbuf;
	std::ifstream sfile;
};

enum class Indicator : Status
{
	none,
	acceptable,
	accept,
	reject,
	prefix,
	//terminate,
	//Left_Eat,
	//Accept_Inmediatly
};
const char* to_string(Indicator i)
{
	switch(i)
	{
	case Indicator::none: return "none";
	case Indicator::acceptable: return "acceptable";
	case Indicator::accept: return "accept";
	case Indicator::reject: return "reject";
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

	class TT : public std::vector<std::array<Transition,MAX_SIMBOLS>>
	{
	public:
		TT() = default;
		
		bool initial(Status status)
		{
			for(size_t i = 0; i < MAX_SIMBOLS; i++)
			{
				std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[i].indicator = Indicator::reject;
				std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[i].next = 0;
				std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[i].token = Token::none;
			}
			return true;
		}
		Status add_status()
		{
			std::vector<std::array<Transition,MAX_SIMBOLS>>::resize(std::vector<std::array<Transition,MAX_SIMBOLS>>::size() + 1);
			std::array<Transition,MAX_SIMBOLS>& t = std::vector<std::array<Transition,MAX_SIMBOLS>>::back();	
			Status status = std::vector<std::array<Transition,MAX_SIMBOLS>>::size() - 1;
			initial(status);
			return status;
		}
		bool acceptable(Status status, Symbol symbol,Token token,Status next)
		{
			std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[symbol].indicator = Indicator::acceptable;
			std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[symbol].token = token;
			std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[symbol].next = next;
			return true;
		}
		bool prefix(Status status, Symbol symbol)
		{
			std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[symbol].indicator = Indicator::prefix;
			std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[symbol].token = Token::none;
			std::vector<std::array<Transition,MAX_SIMBOLS>>::at(status)[symbol].next = 0;
			return true;
		}
	private:
		
	};

	/*A(const Transition (*t)[MAX_SIMBOLS],size_t l,Buffer<Symbol>& b) : table(t),table_length(l),index(0),buffer(&b)
	{
	}*/
	A(const TT& tt,Buffer<Symbol>& b) : table(&tt),index(0),buffer(&b)
	{
	}

	Token next()
	{
		Symbol input;
		Status next = 0,actual = next;
		actual_transition = NULL;
		acceptable_transition = NULL;
		
		while(next < table_length and index < buffer->size())
		{
			actual = next;
			input = buffer->operator[](index);
			if(Buffer<Symbol>::EOB == input )
			{
				//std::cout << "if(" << int(Buffer<Symbol>::EOB) << " == " << int(input) << ") ..\n";
				return get_token();
			}
			actual_transition = &(table->at(actual).at(input));
			if(actual_transition->indicator == Indicator::acceptable) acceptable_transition = actual_transition;
			else if(actual_transition->indicator == Indicator::prefix) ;//puede aceptar n prefijos pero deve ser continuos
			else acceptable_transition = NULL;
			next = actual_transition->next;	
			
			//std::cout << actual << " -- (" << input << " - " << to_string(actual_transition->indicator) << ") --> " << next << "\n";
			index++;
			
		}
		
		return get_token();
	}
private:
	Token get_token() const
	{
		if(not actual_transition) return Token::none;
		if(actual_transition->indicator == Indicator::reject)
		{
			if(acceptable_transition) return acceptable_transition->token;
		}
		if(actual_transition->indicator == Indicator::acceptable or actual_transition->indicator == Indicator::prefix)
		{
			if(acceptable_transition) return acceptable_transition->token;
		}
		return Token::none;
	}
	
private:
	const TT* table;
	size_t table_length,index;
	Buffer<Symbol>* buffer;
	const Transition* actual_transition;
	const Transition* acceptable_transition;
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