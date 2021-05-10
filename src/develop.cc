
#include <iostream>
#include <chrono>


#include "Mail.hh"
#include "data.hh"
#include "memory.hh"

#define LENGTH 1000



int main()
{
	int* segment1[LENGTH];	
	auto start1 = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < 1000; i++)
	{
		segment1[i] = new int;
	}
	for(int i = 0; i < 1000; i++)
	{
		delete segment1[i];
	}
	auto stop1 = std::chrono::high_resolution_clock::now();
	auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1);
	
	int* segment2 = NULL;
	auto start2 = std::chrono::high_resolution_clock::now();
	segment2 = new int[LENGTH];
	delete [] segment2;
	auto stop2 = std::chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
	std::cout << duration1.count() << "/" << duration2.count() << "=" << duration1.count()/duration2.count() << "\n";
	
	octetos::core::DoubleBlock<int> minigc(1000);
	
}
