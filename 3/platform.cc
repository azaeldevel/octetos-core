
/*
 * Copyright (C) 2022 Azael Reyes <azael.devel@gmail.com>
 *
 * CC is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CC is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "platform.hh"

#if __linux__
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
    #if defined LINUX_ARCH

    #elif defined LINUX_GENTOO

    #elif defined LINUX_DEBIAN

    #endif
#elif (defined(_WIN32) || defined(_WIN64))
    #include <userenv.h>
#else
	#error "Plataforma desconocida."
#endif

namespace oct::core::v3
{

    std::filesystem::path get_user_directory()
    {
#if __linux__
	    //home directory
        struct passwd *pw = getpwuid(getuid());
        std::filesystem::path home = pw->pw_dir;

        //configure directory
        return home/configure_directory;
#elif (defined(_WIN32) || defined(_WIN64))
        std::filesystem::path homeDir;
        homeDir = _wgetenv(L"USERPROFILE");
        if(homeDir.empty())
        {
            HANDLE hToken;
            if (OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &hToken))
            {
                DWORD len = MAX_PATH;
                WCHAR path[MAX_PATH];
                if (GetUserProfileDirectoryW(hToken, path, &len))
                {
                    homeDir = path;
                }
                CloseHandle(hToken);
            }
        }
        return homeDir;
#else
	#error "Plataforma desconocida."
#endif
    }

}
