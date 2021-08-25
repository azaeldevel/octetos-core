
#include "core.hh"

#include <ctime>
#include <random>

namespace oct::core
{

	unsigned int getDayID()
	{
		std::time_t t = std::time(0);   // get time now
		std::tm* now = std::localtime(&t);

		unsigned int v = (now->tm_year + 1900) * 10000;
		v += (now->tm_mon + 1 ) * 100;
		v += now->tm_mday;
		
		return v;
	}
	unsigned int getTimeID()
	{
		std::time_t t = std::time(0);   // get time now
		std::tm* now = std::localtime(&t);

		unsigned int v = 0;
		v += now->tm_hour * 100000;
		v += now->tm_min * 1000;
		v += now->tm_sec;
		
		return v;
	}
	double randNumber()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> distr(0.0, 1.0);
		
		return distr(gen);
	}
	double randNumber(double max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> distr(0.0, max);
		
		return distr(gen);
	}
	double randNumber(double min,double max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> distr(min, max);
		
		return distr(gen);
	}
	
	
}