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


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#if defined(__GNUG__) && defined(__ANJUTA__)
	#include <unistd.h>
	#include "config.h"
#elif defined(_WIN32) || defined(_WIN64) || defined(WINDOWS_MINGW)
	#include <locale>
	#include <codecvt>
	#include <string>
#endif

#include "shell.hh"

namespace oct::core
{
#if defined(__GNUG__) && (defined(__linux__) || defined(WINDOWS_MINGW))
	void Shell::chown(const std::string& fn,uid_t u)
	{
		chown(fn,u,gid());
	}
	void Shell::chown(const std::string& fn)
	{
		chown(fn,uid(),gid());
	}
	gid_t Shell::gid() const
	{
		return getegid();
	}
	void Shell::chown(const std::string& fn, uid_t u, gid_t g)
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
		if(ret == 0) return;

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

			throw Exception(msg,__FILE__,__LINE__);

		}

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

#if defined(__GNUG__) && defined(__linux__)
			setenv(env->name.c_str(), env->value.c_str(), 1);
#elif defined(_WIN32) || defined(_WIN64) || defined(WINDOWS_MINGW)
			_putenv((env->name + "=" + env->value).c_str());
#else
#error "Pltaforma desconocida"
#endif
		}
	}
	const String& Shell::cwd()
	{
		return strcwd;
	}


	Shell::Shell(const String& default_dir)
	{
		//strcwd = NULL;
		cd(default_dir);
	}
	Shell::Shell()
	{
		//strcwd = NULL;
#if defined(__GNUG__) && defined(__linux__)
		String dir = ".";
#elif defined(_WIN32) || defined(_WIN64) || defined(WINDOWS_MINGW)
		std::string dirTemp = ".";
		String dir(dirTemp.begin(), dirTemp.end());
#endif
		cd(dir);
	}
	Shell::~Shell()
	{

	}

}
