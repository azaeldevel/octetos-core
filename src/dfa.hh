

#ifndef OCTETOS_CORE_DFA
#define OCTETOS_CORE_DFA

#define TT_PARAMS(T) T,sizeof (T) / sizeof (T[0])

#include <cstddef>
#include <arrays.hh>
#include <Buffer-v3.hh>

namespace oct::core::v3::lc
{
typedef int Status;
typedef int Token;
typedef size_t Index;
static const unsigned char MAX_SIMBOLS = 128;


template<typename C>
bool is_whitespace(C c)
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

template<typename C> 
size_t length(const C* str)
{
	if(not str) return 0;
	size_t i = 0;
	while(str[i] != (C)0)
	{
		i++;
	}
	return i;
}

template<typename C> 
bool equal(const C* initial, const C* target)
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


template<typename C> size_t copy(const C* origin, size_t leng,C** dest)
{
	if(origin[leng] != (C)0) return 0;
	if(not origin) return 0;
	if(not dest) return 0;
	
	size_t i = 0;
	for(;i < leng; i++)
	{
		(*dest)[i] = origin[i];
		//std::cout << "C : " << (*dest)[i] << "\n";
	}
	(*dest)[leng] = (C)0;

	return leng;
}

/**
*\brief
*
*/
template<typename T>
class Buffer
{
public:
	static const T EOB = T(0);
	
public:
	Buffer(const std::filesystem::path& file)
	{
		if(not std::filesystem::exists(file)) throw Exception(Exception::FILE_TERGET_NOT_FOUND,__FILE__,__LINE__);

		_size = std::filesystem::file_size(file);
		if(_size == 0) return;

		buffer = new T[_size + 1];

		std::ifstream ifs(file, std::ifstream::binary);
		pbuf = ifs.rdbuf();
		pbuf->sgetn (buffer,_size);
	}
	Buffer(const T* string)
	{
		_size = length(string);
		if(_size > 0)
		{
			buffer = new T[_size + 1];
			copy(string,_size,&buffer);
		}
		else
		{
			buffer = NULL;
		}
	}
	~Buffer()
	{
		if(sfile.is_open()) sfile.close();
		if(buffer) delete[] buffer;
	}
	explicit operator const T*()const
	{
		return buffer;
	}
	T operator[](uintmax_t i)const
	{	
		//std::cout << "if(" << i << " < " << _size << ") return " << int(buffer[i]) << "\n";
		if(i < _size) return buffer[i];		
		
		return T(0);
	}
	std::uintmax_t size() const
	{
		return _size;
	}

private:
	
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
	bool check(const Transition (*t)[MAX_SIMBOLS],size_t length, bool echo)
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
	}

	A(const Transition (*t)[MAX_SIMBOLS],size_t l,Buffer<Symbol>& b) : table(t),table_length(l),index(0),buffer(&b)
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
			actual_transition = &table[actual][input];
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
	const Transition (*table)[MAX_SIMBOLS];
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