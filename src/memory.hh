
#ifndef OCTETO_CORE_MEMORY_HH
#define OCTETO_CORE_MEMORY_HH


#include "Exception.hh"

namespace octetos::core
{

class Allocable
{

public:
	
};



template<typename T> class Memory
{
public:
	Memory(unsigned short size)
	{
		head = new T[size];
		if(!head) throw core::Exception("Fallo la adquisicion de meoria.",__FILE__,__LINE__);
		this->size = size;
	}
	virtual ~Memory()
	{
		if(head) 
		{
			delete[] head;
			head = NULL;
		}
	}
	T& operator [](unsigned short index)
	{
		if(not head) throw core::Exception("El valor del indice apunta fuera del arreglo.",__FILE__,__LINE__);
		
		return head[index];
	};

	unsigned short getSize()const
	{
		return size;
	}
	operator T* ()
	{
		return head;
	};
protected:
	Memory()
	{
	};

	//
	T* head;
	unsigned short size;
};

struct FlagsDS
{
	unsigned short OwnMemory : 1;
};


template<typename T> class Array : public Memory<T>
{
public:
	Array(unsigned short size) : Memory<T>(size)
	{
		flags.OwnMemory = true;
	}
	Array(T* h,unsigned short sz )
	{
		Memory<T>::head = h;
		Memory<T>::size = sz;
		flags.OwnMemory = false;
	}
	virtual ~Array()
	{
	}

	void resize(unsigned short size)
	{
		if(not flags.OwnMemory) throw core::Exception("No es posible redimensionar un arreglo cuya memoria no es propia",__FILE__,__LINE__);
		if(Memory<T>::head) delete [] Memory<T>::head;
		Memory<T>::head = new T[Memory<T>::size];
		if(!Memory<T>::head) throw core::Exception("Fallo la adquisizion de meoria.",__FILE__,__LINE__);
		this->size = size;
	}
protected:
	FlagsDS flags;
};

}

#endif