
#ifndef OCTETO_CORE_MEMORY_HH
#define OCTETO_CORE_MEMORY_HH

#include <vector>

#include "Exception.hh"

namespace oct::core
{


typedef unsigned short MemorySize;

struct FlagsMemory
{
	unsigned short OwnMemory : 1;
};
class Memory
{
protected:
	Memory(MemorySize size);
	Memory(void* h,MemorySize sz );
	virtual ~Memory();

	void resize(MemorySize size);
	MemorySize getSize()const;
	
	Memory();
	//
	void* head;
	unsigned short size;
	FlagsMemory flags;
}DEPRECATED;


template<typename T> class Block : public Memory
{
public:
	Block(MemorySize size) : Memory(size * sizeof(T))
	{		
	}
	virtual ~Block()
	{
	}

	//getters
	MemorySize getSize()const
	{
		return Memory::getSize()/sizeof(T);
	};

	T& operator [](MemorySize index)
	{
		if(not head) throw core::Exception("El valor del indice apunta fuera del arreglo.",__FILE__,__LINE__);
		
		return ((T*)head)[index];
	};

	
protected:
	
}DEPRECATED;

template<typename T> class MiniGC
{
private:
	struct Element
	{
		T obj;//deve ser el primer miembro para que fucione correctamtne create
		bool use;
	};
	
public:
	MiniGC(MemorySize size) : block(size)
	{
		lastCreated = 0;
		full = false;
		for(MemorySize i = 0; i < size; i++)
		{
			block[i].use = false;
		}
	}
	virtual ~MiniGC()
	{
	}

	T* create()
	{
		if(full) return NULL;
		bool second = false;
	repeat:
		MemorySize max = block.getSize();
		for(MemorySize i = lastCreated; i < max; i++)
		{
			if(not block[i].use) 
			{
				block[i].use = true;
				lastCreated = i;
#ifdef DEBUG
				if(((void*)&(block[i].obj)) != ((void*)&block[i])) throw core::Exception("Element.obj no esta alineado con el inicion de Element.",__FILE__,__LINE__);
#endif
				return &block[i].obj;
			}
		}

		if(not second)
		{
			lastCreated = 0;
			second = true;
			goto repeat;
		}

		full = true;
		return NULL;
	};
	void destroy(T* t)
	{
		Element* e = reinterpret_cast<Element*>(t);
		e->use = false;
		full = false;
	};
	
private:
	Block<Element> block;
	MemorySize lastCreated;
	bool full;
}DEPRECATED;

template<typename T, typename I = unsigned int> class Allocation
{
public:
	struct Node
	{
		Node* prev;
		T object;
		Node* post;
		
		Node()
		{
			prev = NULL;
			post = NULL;
		}
	};
	class List
	{
	public:
		List()
		{
			node_begin = NULL;
			node_last = NULL;
			size = 0;
		}
		Node* push_back(T& object)
		{
			Node* newNode = new Node;
			newNode->object = object;

			if(not node_begin and not node_last)//es el primero
			{
				node_begin = newNode;
				node_last  = newNode;
			}
			else
			{
				Node* oldend = node_last;
				oldend->post = newNode;
				newNode->prev = oldend;
				newNode->post = NULL;
				node_last  = newNode;
			}
			size++;
			return newNode;
		}
		Node* push_back(T object)
		{
			Node* newNode = new Node;
			newNode->object = object;

			if(not node_begin and not node_last)//es el primero
			{
				node_begin = newNode;
				node_last  = newNode;
			}
			else
			{
				Node* oldend = node_last;
				oldend->post = newNode;
				newNode->prev = oldend;
				newNode->post = NULL;
				node_last  = newNode;
			}
			size++;
			return newNode;
		}
		Node& begin()
		{
			if(not node_begin)throw Exception("Lista vacia",__FILE__,__LINE__);

			return *node_begin;
		}
		Node& last()
		{
			if(not node_last)throw Exception("Lista vacia",__FILE__,__LINE__);

			return *node_last;
		}
		I get_size()
		{
			return size;
		}
	private:
		Node *node_last,*node_begin;
		I size;
	};
public:
	Allocation(I size)
	{
	}
	~Allocation()
	{
		free();
	}
	
	T* get()
	{
	}
	void free(T* obj)
	{
	}
	void free()
	{
	}
	void resize(I newsize)
	{
	}
private:
	
};


}

#endif