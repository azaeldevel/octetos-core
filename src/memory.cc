
#include <stdlib.h>


#include "memory.hh"

namespace octetos::core
{

	Memory::Memory()
	{
		flags.OwnMemory = false;
		size = 0;
		head = NULL;
	}
	Memory::Memory(unsigned short size)
	{
		head = malloc(size);
		if(!head) throw core::Exception("Fallo la adquisicion de memoria.",__FILE__,__LINE__);
		this->size = size;
		flags.OwnMemory = true;
	}
	Memory::Memory(void* h,unsigned short sz ) : head(h),size(sz)
	{
		flags.OwnMemory = false;
	}
	Memory::~Memory()
	{
		if(head) 
		{
			free(head);
			head = NULL;
		}
	}

	void Memory::resize(unsigned short size)
	{
		if(not flags.OwnMemory) throw core::Exception("No es posible redimensionar un arreglo cuya memoria no es propia",__FILE__,__LINE__);
		if(head) free(head);
		head = malloc(size);
		if(!head) throw core::Exception("Fallo la adquisizion de meoria.",__FILE__,__LINE__);
		this->size = size;
	}
	unsigned short Memory::getSize()const
	{
		return size;
	}


}