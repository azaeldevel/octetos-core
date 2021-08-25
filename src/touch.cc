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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "shell.hh"

namespace oct::core
{

	void Shell::touch(const std::string& name, int options)
	{
		if(options == 0)
		{
			int fd = open(name.c_str(),O_CREAT | O_TRUNC | O_WRONLY ,0644);
			if(fd == -1)
			{
				std::string msg = "Fallo al tocar archivo '";
				msg += name + "'";
#if DEBUG
				msg += " \n\t";
				switch(errno)
				{
					case EACCES:
						msg += "The requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file did not exist yet and write access to the parent directory is not allowed.\n\tWhere O_CREAT is specified, the protected_fifos or protected_regular sysctl is enabled, the file already exists and is a FIFO or regular file, the owner of the file is neither the current user nor the owner of the containing directory, and the containing directory is both world- or group-writable and sticky.  For details, see the descriptions of /proc/sys/fs/protected_fifos and /proc/sys/fs/protected_regular in proc(5).";
						break;
					case EDQUOT:
						msg += "Where O_CREAT is specified, the file does not exist, and the user's quota of disk blocks or inodes on the filesystem has been exhausted";
						break;
					case EEXIST:
						msg += "pathname already exists and O_CREAT and O_EXCL were used";
						break;
					case EFAULT:
						msg += "pathname points outside your accessible address space";
						break;
					case EFBIG:
						msg += "See EOVERFLOW";
						break;
					case EINTR:
						msg += "While blocked waiting to complete an open of a slow device (e.g., a FIFO; see fifo(7)), the call was interrupted by a signal handler; see signal(7)";
						break;
					case EINVAL:
						msg += "The filesystem does not support the O_DIRECT flag.  See NOTES for more information.\n\tInvalid value in flags.\n\tThe final component (\"basename\") of pathname is invalid (e.g., it contains characters not permitted by the underlying filesystem)";
						break;
					case EISDIR:
						msg += "pathname refers to a directory and the access requested involved writing (that is, O_WRONLY or O_RDWR is set).\n\tpathname refers to an existing directory, O_TMPFILE and one o O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality.";
						break;
					case ELOOP:
						msg += "Too many symbolic links were encountered in resolving pathname.\n\tpathname was a symbolic link, and flags specified O_NOFOLLOW but not O_PATH.";
						break;
					case EMFILE:
						msg += "The per-process limit on the number of open file descriptors has been reached (see the description of RLIMIT_NOFILE in getrlimit(2)";
						break;
					case ENAMETOOLONG:
						msg += "pathname was too long.";
						break;
					case ENFILE:
						msg += "The system-wide limit on the total number of open files has been reached.";
						break;
					case ENODEV:
						msg += "pathname refers to a device special file and no corresponding device exists.";
						break;
					case ENOENT:
						msg += "O_CREAT is not set and the named file does not exist.\n\tA directory component in pathname does not exist or is a dangling symbolic link.\n\tpathname refers to a nonexistent directory, O_TMPFILE and one of O_WRONLY or O_RDWR were specified in flags, but this kernel version does not provide the O_TMPFILE functionality.";
						break;
					case ENOMEM:
						msg += "The named file is a FIFO, but memory for the FIFO buffer can't be allocated because the per-user hard limit on memory allocation for pipes has been reached and the caller is not privileged; see pipe(7).\n\tInsufficient kernel memory was available.";
						break;
					case ENOSPC:
						msg += "pathname was to be created but the device containing pathname has no room for the new file";
						break;
					case ENOTDIR:
						msg += "A component used as a directory in pathname is not, in fact, a directory, or O_DIRECTORY was specified and pathname was not a directory.";
						break;
					case ENXIO:
						msg += "O_NONBLOCK | O_WRONLY is set, the named file is a FIFO, and no process has the FIFO open for reading.\n\tThe file is a device special file and no corresponding device.\n\tThe file is a UNIX domain socket.";
						break;
					case EOPNOTSUPP:
						msg += "The filesystem containing pathname does not support O_TMPFILE.";
						break;
					case EOVERFLOW:
						msg += "pathname refers to a regular file that is too large to be opened.  The usual scenario here is that an application compiled on a 32-bit platform without -D_FILE_OFFSET_BITS=64 tried to open a file whose size exceeds (1<<31)-1 bytes; see also O_LARGEFILE above.  This is the error specified by POSIX.1; in kernels before 2.6.24, Linux gave the error EFBIG for this case.";
						break;
					case EPERM:
						msg += "The O_NOATIME flag was specified, but the effective user ID of the caller did not match the owner of the file and the caller was not privileged.\n\tThe operation was prevented by a file seal; see fcntl(2).\n\t";
						break;
					case EROFS:
						msg += "pathname refers to a file on a read-only filesystem and write access was requested.";
						break;
					case ETXTBSY:
						msg += "pathname refers to an executable image which is currently being executed and write access was requested.\n\tpathname refers to a file that is currently in use as a swap file, and the O_TRUNC flag was specified.\n\tpathname refers to a file that is currently being read by the kernel (e.g., for module/firmware loading), and write access was requested.\n\t";
						break;
					case EWOULDBLOCK:
						msg += "The O_NONBLOCK flag was specified, and an incompatible lease was held on the file (see fcntl(2)).";
						break;
				}
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
#else
				throw octetos::core::Exception(msg,__FILE__,__LINE__);
#endif
			}
		}
	}
	
}
