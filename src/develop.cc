
#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>

#include "Mail.hh"
#include "data.hh"
#include "memory.hh"

#define LENGTH 1000
#define TESTS 10000


int main()
{
	
	int* segment1;
	clock_t start1 = clock();
	for(unsigned short test = 0; test < TESTS; test++)
	{
		segment1 = new int[LENGTH];
		for(int i = 0; i < LENGTH; i++)
		{
			segment1[i] = i;
		}
		delete [] segment1;
	}
	clock_t stop1 = clock();
	clock_t duration1 = stop1 - start1;

	
	int* segment2[LENGTH];	
	clock_t start2 = clock();
	for(unsigned short test = 0; test < TESTS; test++)
	{
		for(int i = 0; i < LENGTH; i++)
		{
			segment2[i] = new int;
			(*segment2[i]) = i;
		}
		for(int i = 0; i < LENGTH; i++)
		{
			delete segment2[i];
		}
	}
	clock_t stop2 = clock();
	clock_t duration2 = stop2 - start2;
	float speed2 = duration2/duration1;
	std::cout  << "Lentiud 2 : " << duration2 << "/" << duration1 << "=" << speed2 << "\n";


	int* segment3[LENGTH];
	clock_t start3 = clock();
	octetos::core::MiniGC<int> minigc(LENGTH);	
	for(unsigned short test = 0; test < TESTS; test++)
	{
		for(unsigned short i = 0; i < LENGTH; i++)
		{
			segment3[i] = minigc.create();
			*segment3[i] = i;
		}
		for(unsigned short i = 0; i < LENGTH; i++)
		{
			minigc.destroy(segment3[i]);
		}		
	}
	clock_t stop3 = clock();
	clock_t duration3 = stop3 - start3;
	float speed3 = duration3/duration1;
	std::cout << "Lentiud 3 : " << duration3 << "/" << duration1 << "=" << speed3 << "\n";

	float speed = speed3/speed2;
	float ventaja = 1.0 - speed;
	if(speed < 1.0) std::cout << "Hay una ventaj del " << 100.0 * ventaja << "%\n";
	else if(fabs(speed - 1.0) <= 0.001) std::cout << "No hay efecto\n";
	else std::cout << "Hay una desventaja del " << fabs(100.0 * ventaja) << "%\n";

	std::ofstream fn("statics.csv",std::ios::app | std::ios::in | std::ios::ate);
	fn << speed2 << "," << speed3 << "," << ventaja << "\n";
}
