
#include "data.hh"




int main()
{
	oct::core::Wall<int> array1(5);
	array1[0] = 0;
	array1[1] = 0;
	array1[2] = 0;
	array1[3] = 0;
	array1[4] = 0;
	for(unsigned int i = 0; i < 1000000; i++)
	{
		for(unsigned int j = 0; j < array1.get_size(); j++)
		{
			if(j >= array1.get_size()) throw oct::core::Exception("indice fuera de rango");
			array1[j]++;
		}
	}
}