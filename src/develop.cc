
#include <iostream>
#include <chrono>
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
	auto start1 = std::chrono::high_resolution_clock::now();
	for(unsigned short test = 0; test < TESTS; test++)
	{
		segment1 = new int[LENGTH];
		for(int i = 0; i < LENGTH; i++)
		{
			segment1[i] = i;
		}
		delete [] segment1;
	}
	auto stop1 = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);

	
	int* segment2[LENGTH];	
	auto start2 = std::chrono::high_resolution_clock::now();
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
	auto stop2 = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
	float speed2 = duration2.count()/duration1.count();
	std::cout  << "Lentiud 2 : " << duration2.count() << "/" << duration1.count() << "=" << speed2 << "\n";


	int* segment3[LENGTH];
	auto start3 = std::chrono::high_resolution_clock::now();
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
	auto stop3 = std::chrono::high_resolution_clock::now();	
	auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(stop3 - start3);
	float speed3 = duration3.count()/duration1.count();
	std::cout << "Lentiud 3 : " << duration3.count() << "/" << duration1.count() << "=" << speed3 << "\n";

	float speed = speed3/speed2;
	float ventaja = fabs(100 * speed);
	if(speed < 1) std::cout << "Hay una ventaj del " << ventaja << "%\n";
	else if(fabs(speed - 1.0) <= 0.001) std::cout << "No hay efecto\n";
	else std::cout << "Hay una desventaja del " << ventaja << "%\n";

	std::ofstream fn("statics.csv");
	fn << speed2 << "," << speed3 << "," << ventaja << "\n";
}
