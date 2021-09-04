
#ifndef APISHELL_HH
#define APISHELL_HH

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


#include <string>
#include <list>
#include <dirent.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "Exception.hh"

namespace oct::core
{
	struct Enviroment
	{
		std::string name;
		std::string value;
	};

	class Shell
	{
	private:

		std::string strcwd;
		int fdcwd;//TODO:verificar si es necesario
		/**
		* \brief Inidca si strcdw fua asignada con malloc
		*/
		bool strcwd_malloc;

		//bool cwd(const std::string& = "");

	public:
		Shell();
		Shell(const std::string&);
		~Shell();
		/**
		*\brief list files in current work directory
		*/
		void ls(std::list<std::string>&);
		void cd(const std::string&);
		/**
		*
		*
		*/
		void mkdir(const std::string&, bool recursive=false);
		void rm(const std::string&);
		void rename(const std::string&,const std::string&);
		void touch(const std::string&, int options = 0);
		void ln(const std::string&, int m = 0);
		/**
		*
		*
		*/
		bool exists(const std::string&);
		const std::string& cwd();
		void set(std::vector<Enviroment*>);
		int execute(const std::string&);
		void echo(const std::string&, std::ostream& out = std::cout);
		#ifndef WINDOWS_MINGW
		int chmod(const std::string&,int mode);
		uid_t uid() const;
		gid_t gid() const;
		void chown(const std::string& fn,uid_t ,gid_t);
		void chown(const std::string& fn,uid_t);
		void chown(const std::string& fn);
		#endif

		void cp(const std::string& o, const std::string& d);
	};


}

#endif
