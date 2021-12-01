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
#ifdef _GNUC_
	bool Shell::exists(const std::string& filename)
	{
	   	struct stat info;
	   	int mode;
	   	int ret = stat( filename.c_str(), &info );
	   	if(ret == 0 and S_ISDIR(info.st_mode))
	   	{
	   		return true;
	   	}
	   	
	   	if( ret == 0 )
		{
		    #ifdef WINDOWS_MINGW
		    mode = (info.st_mode && S_IFREG)  || (info.st_mode && S_IFMT);
		    #else
		    mode = (info.st_mode && S_IFREG)  || (info.st_mode && S_IFMT) || (info.st_mode && S_IFLNK);
		    #endif
			if( mode )
			{
				return true;
			}
		}
		/*
		if(ret == -1)
		{
			std::string msg = "Fail on floor : '";
			msg += filename + "'\n";
			switch(errno)
			{
				case EACCES:
					msg += "Search permission is denied for one of the directories in the path prefix of pathname.";
					break;
				case EBADF:
					msg += "fd is not a valid open file descriptor.\nor\ndirfd is not a valid file descriptor.";
					break;
				case EFAULT:
					msg += "Bad address.";
					break;
				case ELOOP:
					msg += "Too many symbolic links encountered while traversing the path.";
					break;
				case ENAMETOOLONG:
					msg += "pathname is too long.";
					break;
				case ENOENT:
					//msg += "A component of pathname does not exist or is a dangling symbolic link.\nor\npathname is an empty string and AT_EMPTY_PATH was not specified in flags.\nor\nOut of memory (i.e., kernel memory).";
					return false;
				case ENOTDIR:
					msg += "A component of the path prefix of pathname is not a directory.\nor\npathname is relative and dirfd is a file descriptor referring to a file other than a directory.";
					break;
				case EOVERFLOW:
					msg += "pathname or fd refers to a file whose size, inode number, or number of blocks cannot be represented in, respectively, the types off_t, ino_t, or blkcnt_t.";
					break;
				case EINVAL:
					msg += "Invalid flag specified in flags.";
					break;
			}
			throw octetos::core::Exception(msg,__FILE__,__LINE__);
		}*/

		return false;
	}
#elif _WIN32 || _WIND64
	bool Shell::exists(const std::string& filename)
	{
		throw Exception("Aun no implemetada", __FILE__, __LINE__);
	}
#else
	#error "Pltaforma desconocida"
#endif
}
