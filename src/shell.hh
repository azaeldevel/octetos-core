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

#ifndef APISHELL_HH
#define APISHELL_HH

#include <string>
#include <list>
#if defined WINDOWS_MINGW
    #include <Error.hh>
    #include <Artifact.hh>
#else
    #include <octetos/core/Error.hh>
    #include <octetos/core/Artifact.hh>
#endif
#include <dirent.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

//#define TTRUE 1
//#define TFALSE -1
//#define TNULL 0


namespace oct::core
{
	struct Enviroment
	{
		std::string name;
		std::string value;
	};

	class DECLSPCE_DLL Shell
	{
	private:

		std::string strcwd;
		int fdcwd;
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
		bool ls(std::list<std::string>&);
		bool cd(const std::string&);
		/**
		*
		*\return TTRUE if file exists, TNULL is not exists and TFALSE if error.
		*/
		bool mkdir(const std::string&, bool recursive=false);
		bool rm(const std::string&);
		bool rename(const std::string&,const std::string&);
		bool touch(const std::string&, int options = 0);
		bool ln(const std::string&, int m = 0);
		/**
		*
		*\return TTRUE if file exists, TNULL is not exists and TFALSE if error.
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
		bool chown(const std::string& fn,uid_t ,gid_t);
		bool chown(const std::string& fn,uid_t);
		bool chown(const std::string& fn);
		#endif

		void cp(const std::string& o, const std::string& d);
	};


}

#endif
