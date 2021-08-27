
#ifndef OCTETO_CORE_MEMORY_HH
#define OCTETO_CORE_MEMORY_HH

/**
 *
 *  This file is part of octetos-core.
 *  octetos-core is a core C/C++ Octeto's library.
 *  Copyright (C) 2018  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */

#include <vector>
#include <iostream>

#include "Exception.hh"

namespace oct::core
{


/**
*\brief Su funcion es la de un recolector de basura, sin embargo, se deve de eliminar explicitamente cada objeto.
*/
template<typename T, typename I = unsigned int> class Allocator
{
public:
	class List;
	class Node
	{
	friend class List;

	public:
		T object;

	public:
		Node(List* listOwner)
		{
			previous = NULL;
			posteriory = NULL;
			owner = listOwner;
		}
		
		List& get_owner()
		{
			return *owner;
		}
		Node* get_previous()
		{
			return previous;
		}
		Node* get_posteriory()
		{
			return posteriory;
		}

	public:
		Node* previous;
		Node* posteriory;
		List* owner;
	};
	class List
	{
	public:
		List()
		{
			node_first = NULL;
			node_last = NULL;
			size = 0;
		}
		~List()
		{
			Node* toDelete = node_last;
			Node* nodePrev = NULL;
			while(toDelete != NULL)
			{
				nodePrev = toDelete->get_previous();
				delete toDelete;
				toDelete = nodePrev;
			}			
		}

		Node& push_back(T& object)
		{
			Node* newNode = new Node(this);
			newNode->object = object;

			if(not node_first and not node_last)//es el primero
			{
				node_first = newNode;
				node_last  = newNode;
			}
			else
			{
				newNode->previous = node_last; 
				newNode->posteriory = NULL;
				node_last->posteriory = newNode;
				node_last = newNode;
			}
			size++;
			return *newNode;
		}
		Node& push_back(T object)
		{
			Node* newNode = new Node(this);
			newNode->object = object;

			if(not node_first and not node_last)//es el primero
			{
				node_first = newNode;
				node_last  = newNode;
			}
			else
			{
				newNode->previous = node_last; 
				newNode->posteriory = NULL;
				node_last->posteriory = newNode;
				node_last = newNode;
			}
			size++;
			return *newNode;
		}
		Node& push_back(Node& newNode)
		{
			newNode.owner = this;

			if(size == 0)//es el primero
			{
				node_first = &newNode;
				node_last  = &newNode;
				newNode.previous = NULL; 
				newNode.posteriory = NULL;
			}
			else
			{
				newNode.previous = node_last; 
				newNode.posteriory = NULL;
				node_last->posteriory = &newNode;
				node_last = &newNode;
			}
			size++;
			return newNode;
		}
		Node& push_back()
		{
			Node* newNode = new Node(this);

			if(not node_first and not node_last)//es el primero
			{
				node_first = newNode;
				node_last  = newNode;
			}
			else
			{
				newNode->previous = node_last; 
				//newNode->posteriory = NULL;hecho en el contructor de Node
				node_last->posteriory = newNode;
				node_last = newNode;
			}
			size++;
			return *newNode;
		}
		Node& first()
		{
			if(not node_first)throw Exception("Lista vacia",__FILE__,__LINE__);

			return *node_first;
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
		Node& pull(Node& node)
		{
			node.get_owner().remove(node);
			return push_back(node);
		}
		void remove(Node& node)
		{
			//std::cout << " void List::remove(..) step 1\n";
			if(not isOwner(node)) throw Exception("El nodo indicado no pertenece a esta lista",__FILE__,__LINE__);
			
			//std::cout << " void List::remove(..) step 2\n";
			if(size == 1)
			{
				node_last = NULL;
				node_first = NULL;
			}
			else if(size > 1)
			{
				//std::cout << " void List::remove(..) step 2.1\n";
				if(node.previous) node.previous->posteriory = node.posteriory;
				else //es el primer nodo
				{
					//std::cout << " void List::remove(..) step 2.2.1\n";
					node.posteriory->previous = NULL;
					node_first = node.posteriory;
				}
				if(node.posteriory) node.posteriory->previous = node.previous;
				else //es el ultimo nodo
				{
					//std::cout << " void List::remove(..) step 2.2.1\n";
					node.previous->posteriory = NULL;
					node_last = node.previous;
				}
			}
			
			node.owner = NULL;
			node.previous = NULL;
			node.posteriory = NULL;			
			size--;
		}
		bool isOwner(Node& node)
		{
			return node.owner != this ? false : true;			
		}
	private:
		Node *node_last, *node_first;
		I size;
	};
public:
	Allocator()
	{
	}
	~Allocator()
	{
	}
	
	T* create()
	{
		if(gc.get_size() > 0)
		{
			Node& node = gc.last();
			used.pull(node);
			return &node.object;
		}
		else
		{
			return &used.push_back().object;
		}
	}
	void destroy(T* obj)
	{
		Node* node = (Node*)(void*)obj;
		if(used.isOwner(*node)) gc.pull(*node);
		else throw Exception("El objeto no existe",__FILE__,__LINE__);
	}
	void destroy(Node* node)
	{
		if(used.isOwner(*node)) gc.pull(*node);
		else throw Exception("El objeto no existe",__FILE__,__LINE__);
	}	
	List& get_used()
	{
		return used;
	}
private:
	List gc,used;
};


//>>>>>>>>>>>>>>	DEPRECATED 	DEPRECATED DEPRECATED
//>>>>>>>>>>>>>>	DEPRECATED 	DEPRECATED DEPRECATED
//>>>>>>>>>>>>>>	DEPRECATED 	DEPRECATED DEPRECATED


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


}

#endif