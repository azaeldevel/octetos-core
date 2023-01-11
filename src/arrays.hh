
#ifndef OCTETOS_CORE_ARRAYS
#define OCTETOS_CORE_ARRAYS

#include <vector>
#include <iostream>


namespace oct::core::v3::arrays
{


template<typename T>
concept SortableData = requires (T t1,T t2)
{
	t1 < t2;
	t1 > t2;
	//t1 == t2;
	t1.print(std::cout);
};
template<SortableData D,typename I> void copy(I begin, I end,D* in,D* out)
{
	for(I i = begin; i < end; i++)
	{
		out[i] = in[i];
	}
}
template<SortableData D,typename I> void merge(D* in,I begin, I middle, I end,D* out)
{
			I i = begin;
			I j = middle;
			I k = begin;

			while(i < middle && j <= end)
			{
				if (in[i] < in[j])
				{
						//std::cout << " : Cierto\n";
						out[k] = in[i];
						i++;
				}
				else
				{
						//std::cout << " : Falso\n";
						out[k] = in[j];
						j++;
				}
				k++;
			}
			while(i < middle )
			{
					//std::cout << "\tvaciando " << in[i]->index << "\n";
					out[k] = in[i];
					i++;
					k++;
			}
			while(j <= end )
			{
					//std::cout << "\tvaciando " << in[j]->index << "\n";
					out[k] = in[j];
					j++;
					k++;
			}
}
template<SortableData D,typename I> void split(D* out,I begin, I end,D* in)
{
	if (end - begin < 1) return;
				
	I middle = begin + (end - begin) / 2;

	split(in,begin,middle,out);
	split(in,middle + 1,end,out);

	merge(out,begin,middle+1,end,in);
}
template<SortableData D,typename I> void sort(D* data, I length)
{
	D work[length];	

	copy(I(0),length,data,work);
	split(work,I(0),length - 1,data);
}

template<typename D>
class array 
{
public:
	
protected:
	
};

template<typename D>
class Wrapper : public array<D>
{
public:
	Wrapper(D* d,size_t s) : head(d),size(s)
	{
		std::cout << "Wrapper(D* d,size_t s)\n";
	}
	


	D& operator [](size_t index)
	{
		if(index < size) return &head[index];

		throw std::out_of_range("El indice esta fuera de rango");
	}
	const D* operator [](size_t index) const
	{
		if(index < size) return &head[index];

		throw std::out_of_range("El indice esta fuera de rango");
	}
	size_t get_size()const
	{
		return size;
	}

	void print(std::ostream& out)const
	{
		for(size_t i = 0; i < size; i++)
		{
			head[i].print(out);
		}
	}

private:
	D* head;
	size_t size;
};



template<SortableData D,typename... K>
class Table : public Wrapper<D>
{
public:
	Table(D* d,size_t s) : head(d),size(s)
	{
		std::cout << "Wrapper(D* d,size_t s)\n";
	}
	

	virtual D* find(K... k)
	{
		return &head[0];
	}
	virtual const D* find(K... k) const
	{
		if(sizeof...(K) == 0) return NULL;
		
		
		
		return &head[0];
	}

	D& operator [](size_t index)
	{
		if(index < size) return &head[index];

		throw std::out_of_range("El indice esta fuera de rango");
	}
	const D* operator [](size_t index) const
	{
		if(index < size) return &head[index];

		throw std::out_of_range("El indice esta fuera de rango");
	}

	void sort()
	{
		oct::core::v3::arrays::sort(head,size);
	}
private:
	D* head;
	size_t size;
};




}


#endif