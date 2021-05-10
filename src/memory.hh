
#ifndef OCTETO_CORE_MEMORY_HH
#define OCTETO_CORE_MEMORY_HH


#include "Exception.hh"

namespace octetos::core
{

class Allocable
{

public:
	
};


struct FlagsMemory
{
	unsigned short OwnMemory : 1;
};
class Memory
{
public:
	Memory(unsigned short size);
	Memory(void* h,unsigned short sz );
	Memory(unsigned short objsize,unsigned short objcount);
	virtual ~Memory();

	void resize(unsigned short size);
	unsigned short getSize()const;

protected:
	Memory();

	//
	void* head;
	unsigned short size;
	FlagsMemory flags;
};


template<typename T> class Array : public Memory
{
public:
	Array(unsigned short size) : Memory(size)
	{		
	}
	Array(T* h,unsigned short sz ) : Memory(h,sz)
	{
	}
	Array(unsigned short objsize,unsigned short objcount) : Memory(objsize,objcount)
	{
	}
	virtual ~Array()
	{
	}

	T& operator [](unsigned short index)
	{
		if(not head) throw core::Exception("El valor del indice apunta fuera del arreglo.",__FILE__,__LINE__);
		
		return ((T*)head)[index];
	};
	
protected:
	
};

template<typename T> class DoubleBlock
{
private:
	template<typename U> struct Element
	{
		U e;
		bool use;
	};
public:
	DoubleBlock(unsigned short size) : main(size),second(size)
	{
	}
	virtual ~DoubleBlock()
	{
	}
	
private:
	Array<Element<T>> main, second;
};

}

#endif