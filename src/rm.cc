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
#include <unistd.h>
#include <fcntl.h>
#ifdef WINDOWS_MINGW
    #include <windows.h>
    #include <winuser.h>
    #include <fileapi.h>
    #include <windef.h>
    #include <setupapi.h>
#endif
#include "shell.hh"

namespace oct::core
{
    void Shell::rm(const std::string& path)
	{
		struct stat buf;
		int fd = open(path.c_str(),O_RDONLY);
		if(fd == -1)
		{
			return;
		}
		if(fstat (fd, &buf) == -1)
		{
			return;
		}
		//close(fd);

#ifdef WINDOWS_MINGW
        DeleteFileA(path.c_str());
        return;
#else
		if (S_ISLNK(buf.st_mode) or S_ISREG(buf.st_mode))//es link?
		{//es un link
			int retRm = unlinkat(fdcwd,path.c_str(),0);
			if(retRm == 0)
			{
				return;
			}
			else if(retRm == -1)
			{
				std::string msg = "Fallo eliminar link '";
				msg += path + "'";
				msg += "\n\t";
				switch(errno)
				{
					case EACCES:
						msg += "Write access to the directory containing pathname is not allowed for the process's effective UID, or one of the directories in pathname did not allow search permission";
						break;
					case EBUSY:
						msg += "The file pathname cannot be unlinked because it is being used by the system or another process; for example, it is a mount point or the NFS client software created it to represent an active but otherwise nameless inode (\"NFS silly renamed\")";
						break;
					case EFAULT:
						msg += "pathname points outside your accessible address space";
						break;
					case EIO:
						msg += "An I/O error occurred";
						break;
					case EISDIR:
						msg += "pathname refers to a directory";
						break;
					case ELOOP:
						msg += "Too many symbolic links were encountered in translating pathname";
						break;
					case ENAMETOOLONG:
						msg += "pathname was too long";
						break;
					case ENOENT:
						msg += "A component in pathname does not exist or is a dangling symbolic link, or pathname is empty.";
						break;
					case ENOMEM:
						msg += "Insufficient kernel memory was available";
						break;
					case ENOTDIR:
						msg += "A component used as a directory in pathname is not, in fact, a directory";
						break;
					case EPERM:
						msg += "The system does not allow unlinking of directories, or unlinking of directories requires privileges that the calling process doesn't have";
						break;
					case EROFS:
						msg += "pathname refers to a file on a read-only file system";
						break;
				}
				throw Exception(msg,__FILE__,__LINE__);
			}
		}
		else if (S_ISDIR(buf.st_mode))//es un directorio?
		{
			int retRm = rmdir(path.c_str());
			if(retRm == 0)
			{
				return;
			}
			else if(retRm == -1)
			{
				std::string msg = "Fallo eliminar directorio '";
				msg += path + "'";
				msg += "\n\t";
				switch(errno)
				{
					case EACCES:
						msg += "Write access to the directory containing pathname was not allowed, or one of the directories in the path prefix of pathname did not allow search permission";
						break;
					case EBUSY:
						msg += "pathname is currently in use by the system or some process that prevents its removal. On Linux this means pathname is currently used as a mount point or is the root directory of the calling process.";
						break;
					case EFAULT:
						msg += "pathname points outside your accessible address space";
						break;
					case EINVAL:
						msg += "pathname has . as last component";
						break;
					case ELOOP:
						msg += "Too many symbolic links were encountered in resolving pathname";
						break;
					case ENAMETOOLONG:
						msg += "pathname was too long";
						break;
					case ENOENT:
						msg += "A directory component in pathname does not exist or is a dangling symbolic link";
						break;
					case ENOMEM:
						msg += "Insufficient kernel memory was available";
						break;
					case ENOTDIR:
						msg += "pathname, or a component used as a directory in pathname, is not, in fact, a directory";
						break;
					case ENOTEMPTY:
						msg += "pathname contains entries other than . and .. ; or, pathname has .. as its final component. POSIX.1-2001 also allows EEXIST for this condition";
						break;
					case EPERM:
						msg += "The directory containing pathname has the sticky bit (S_ISVTX) set and the process's effective user ID is neither the user ID of the file to be deleted nor that of the directory containing it, and the process is not privileged (Linux: does not have the CAP_FOWNER capability)";
						break;
					case EROFS:
						msg += "pathname refers to a directory on a read-only file system";
						break;
				}
				throw Exception(msg,__FILE__,__LINE__);
			}
		}
#endif
	}
}
