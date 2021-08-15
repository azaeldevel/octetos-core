

#include "data.hh"



struct Array
{
	unsigned int number[5];
	unsigned int size=5;
};
int main()
{
	Array array1;
	array1.number[0] = 0;
	array1.number[1] = 0;
	array1.number[2] = 0;
	array1.number[3] = 0;
	array1.number[4] = 0;
	for(unsigned int i = 0; i < 1000000; i++)
	{
		for(unsigned int j = 0; j < array1.size; j++)
		{
			if(j >= array1.size) throw oct::core::Exception("indice fuera de rango");
			array1.number[j]++;
		}
	}
}
