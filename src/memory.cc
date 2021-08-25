
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
 
 
#include <stdlib.h>


#include "memory.hh"

namespace oct::core
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