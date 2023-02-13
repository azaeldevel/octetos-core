
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
 
#include "core.hh"

#include <ctime>
#include <random>

namespace oct
{
#if defined(__linux__)
    void print_backtrace(const char* msg,int code)
	{
		void* array[20];
		size_t size;

		size = backtrace(array,20);
		fprintf(stderr,msg,code);
		backtrace_symbols_fd(array,size,STDERR_FILENO);
	}
	void signal_exception(int s)
	{
		print_backtrace("Error signal detected %d:\n",s);
	}
	void signal_abort(int s)
	{
		print_backtrace("Error signal detected %d:\n",s);
	}
	void signal_segmentv(int s)
	{
		print_backtrace("Error signal detected %d:\n",s);
	}
#elif (defined(_WIN32) || defined(_WIN64))

#else
    #error "Pltaforma desconocida"
#endif
}

namespace oct::core::v2
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
		v += now->tm_hour * 10000;
		v += now->tm_min * 100;
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

namespace oct::core::v3
{


}


namespace oct::core
{


}