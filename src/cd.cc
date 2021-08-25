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
#ifdef WINDOWS_MINGW
    #include <windows.h>
    #include <winbase.h>
    #include <winuser.h>
    #include <windef.h>
    #include <setupapi.h>
#endif


#include "shell.hh"

namespace oct::core
{

	bool Shell::cd(const std::string& dir)
	{
		int ret = chdir(dir.c_str());

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

		if(ret == 0) return true;
		return false;
	}



}
