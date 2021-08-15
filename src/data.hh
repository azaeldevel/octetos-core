

#ifndef OCTETO_CORE_DATA_HH
#define OCTETO_CORE_DATA_HH


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