/**
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
 * */



#if defined(__GNUC__) && defined(__linux__)
    #include <unistd.h>
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))
    #include <direct.h>
#else
    #error "Pltaforma desconocida"
#endif

#include "shell.hh"

namespace oct::core
{
#if defined(__GNUG__) && defined(__linux__)
	void Shell::cd(const std::string& dir)
	{
		int ret = ::chdir(dir.c_str());
		if(ret != 0) throw Exception("Fallo al cambia de directorio", __FILE__,__LINE__);

		#ifdef WINDOWS_MINGW
		DWORD len = 2;
		LPTSTR buf = new char(len);
		len = GetCurrentDirectory(len,buf);
		delete buf;
		GetCurrentDirectory(len,buf);

		#else
		char* buf = get_current_dir_name();
		#endif
		strcwd = buf;
		free((void*)buf);
	}
#elif defined(__GNUG__) && (defined(_WIN32) || defined(_WIN64))
	void Shell::cd(const std::string& dir)
	{
		int ret = ::_chdir(dir.c_str());
		if(ret != 0) throw Exception("Fallo al cambia de directorio", __FILE__,__LINE__);

		char* buf = _getcwd (NULL,0);

		strcwd = buf;
		free((void*)buf);
	}

#else
    #error "Pltaforma desconocida"
#endif


}
