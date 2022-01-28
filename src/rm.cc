/**
 *
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
 *
 * */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#ifdef __GNUC__
#include <unistd.h>
#endif
#include "shell.hh"

#include "rm-exceptions.cc"


namespace oct::core
{

#if defined(__GNUC__) && defined(__linux__)
    bool Shell::rm(const std::string& path, bool recursive)
	{
		struct stat st;		
		stat(path.c_str(), &st);


		if(S_ISREG(st.st_mode))
		{
			remove(path.c_str());
		}
		else if (S_ISDIR(st.st_mode))//es un directorio?
		{
			DIR* dircwd = opendir(path.c_str());
			struct dirent *entry;

	  		while((entry = readdir(dircwd)))
			{
				if(strcmp(entry->d_name,".") == 0) continue;
				if(strcmp(entry->d_name,"..") == 0) continue;
				
				if(not recursive) throw RemoveDirException(EINVAL,__FILE__,__LINE__);
				rm(entry->d_name);
			}
			int retRm = rmdir(path.c_str());
			if(retRm == 0)
			{
				return true;
			}
			else if(retRm == -1)
			{
				//std::cout << "Fail with : " << path << "\n";
				throw RemoveDirException(errno,__FILE__,__LINE__);
			}
		}
		else if (S_ISLNK(st.st_mode))//es link?
		{//es un link
			int retRm = unlinkat(fdcwd,path.c_str(),0);
			if(retRm == 0)
			{
				return true;
			}
			else if(retRm == -1)
			{				
				throw UnlinkException(errno,__FILE__,__LINE__);
			}
		}
		else
		{
			throw UnmanageObjectException(__FILE__,__LINE__);
		}

		return true;
	}
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))
    bool Shell::rm(const std::string& path)
	{
		struct stat st;		
		stat(path.c_str(), &st);

		if(S_ISREG(st.st_mode))
		{
			remove(path.c_str());
		}
		else if (S_ISDIR(st.st_mode))//es un directorio?
		{
			int retRm = rmdir(path.c_str());
			if(retRm == 0)
			{
				return true;
			}
			else if(retRm == -1)
			{
				
				throw RemoveDirException(errno,__FILE__,__LINE__);
			}
		}
		else
		{
			throw UnmanageObjectException(__FILE__,__LINE__);
		}

		return true;
	}
#else
	#error "Plataforma desconocida"
#endif
}
