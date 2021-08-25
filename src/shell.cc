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

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef HAVE_CONFIG_H
    #include "config.h"
#elif defined WINDOWS_MINGW && defined CODEBLOCKS
    #include "config-cb.h"
#endif
#include "shell.hh"

namespace oct::core
{
    #ifndef WINDOWS_MINGW
	bool Shell::chown(const std::string& fn,uid_t u)
	{
		return chown(fn,u,gid());
	}
	bool Shell::chown(const std::string& fn)
	{
		return chown(fn,uid(),gid());
	}
	gid_t Shell::gid() const
	{
		return getegid();
	}
	bool Shell::chown(const std::string& fn, uid_t u, gid_t g)
	{

		/*std::string text = "user :";
		text += std::to_string(u);
		text += "\n";
		echo(text);

		std::string textg = "group :";
		textg += std::to_string(g);
		textg += "\n";
		echo(textg);*/

		int ret = ::chown(fn.c_str(),u,g);
		if(ret == 0) return true;

		if(errno != 0)
		{
			std::string msg = "Fail on floor '";
			switch(errno)
			{
				case EACCES:
					msg += "Search permission is denied on a component of the path prefix.";
					break;
				case EFAULT:
					msg += "pathname points outside your accessible address space.";
					break;
				case ELOOP:
					msg += "Too many symbolic links were encountered in resolving";
					break;
				case ENAMETOOLONG:
					msg += "pathname is too long";
					break;
				case ENOENT:
					msg += "Insufficient kernel memory was available.";
					break;
				case ENOTDIR:
					msg += "A component of the path prefix is not a directory.\nor \npathname is relative and dirfd is a fil descriptor referring to a file other than a directory.";
					break;
				case EPERM:
					msg += "The calling process did not have the required permissions (see above) to change owner and/or group\nor\nThe file is marked immutable or append-only.";
					break;
				case EROFS:
					msg += "The named file resides on a read-only filesystem.";
					break;
				case EBADF:
					msg += "fd is not a valid open file descriptor.\nor\ndirfd is not a valid file descriptor.";
					break;
				case EIO:
					msg += "A low-level I/O error occurred while modifying the inode.";
					break;
				case EINVAL:
					msg += "Invalid flag specified in flags.";
					break;
			}

			throw octetos::core::Error(msg,errno,__FILE__,__LINE__);

		}

		return false;
	}
	uid_t Shell::uid() const
	{
		return geteuid();
	}
    #endif

	void Shell::echo(const std::string& text, std::ostream& o)
	{
		o << text;
	}
	int Shell::execute(const std::string& cmd)
	{
		return system(cmd.c_str());
	}
	void Shell::set(std::vector<Enviroment*> v)
	{
		for(const Enviroment* env : v)
		{
            #ifdef WINDOWS_MINGW
                _putenv((env->name + "=" + env->value).c_str());
			#else
                setenv(env->name.c_str(),env->value.c_str(),1);
		    #endif
		}
	}
	const std::string& Shell::cwd()
	{
		return strcwd;
	}


	Shell::Shell(const std::string& default_dir)
	{
		//strcwd = NULL;
		cd(default_dir);
	}
	Shell::Shell()
	{
		//strcwd = NULL;
		cd(".");
	}
	Shell::~Shell()
	{

	}

}
