/**
 *
 *  This file is part of octetos-coreutils.
 *  octetos-coreutils is a library C++ for coreuitls funtions.
 *  Copyright (C) 2020  Azael Reyes
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
 *
 * */


#include <sys/stat.h>


#include "shell.hh"

namespace oct::core
{
#if defined(__GNUC__) && defined(__linux__)
	bool Shell::exists(const std::string& filename)
	{
	   	struct stat info;
	   	int ret = stat( filename.c_str(), &info );
	   	if(ret == 0) return true;
		else return false;
	}
#elif defined(__GNUC__) && defined(_WIN64)
    bool Shell::exists(const std::string& filename)
	{
	   	struct _stat64 info;
	   	int ret = _stat64( filename.c_str(), &info);
	   	if(ret == 0) return true;
		else return false;
	}
#elif defined(__GNUC__) && defined(_WIN32)
    bool Shell::exists(const std::string& filename)
	{
	   	throw octetos::core::Exception("Aun no implemetada.",__FILE__,__LINE__);
	}
#else
	#error "Pltaforma desconocida"
#endif
}
