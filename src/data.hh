

#ifndef OCTETO_CORE_DATA_HH
#define OCTETO_CORE_DATA_HH

/**
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
 * */


#include "Exception.hh"


namespace oct::core
{
	
	template<typename T,typename I> class Mold
	{
	public:
		virtual T& operator [](I index) = 0;
	};

	template<typename T,typename I = unsigned int> class Wall : public Mold<T,I>
	{
	public:
		Wall()
		{
		}
		Wall(I size)
		{
			t = new T[size];
			this->size = size;
		}
		~Wall()
		{
			delete[] t;
		}
		
		virtual T& operator [](I i)
		{
			return t[i];
		}
		virtual const T& operator [](I i) const
		{
			return t[i];
		}
		operator T&()
		{
			return *t;
		}
		operator const T&() const
		{
			return *t;
		}


		I get_size() const
		{
			return size;
		}
 

	private:
		T* t;
		I size;
	};

	
}

#endif