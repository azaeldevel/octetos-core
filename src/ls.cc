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
#include <dirent.h>
#include <sys/types.h>

#include "shell.hh"

namespace oct::core
{
	bool Shell::ls(std::list<std::string>& l)
	{
		DIR* dircwd = opendir(cwd().c_str());;
		struct dirent *entry;

  		while((entry = readdir(dircwd)))
		{
			l.push_back(entry->d_name);
		}
	
		return true;
	}
}