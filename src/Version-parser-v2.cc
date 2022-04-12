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


#include "Version-v2.hh"
#include "semver.tab.3.h"
#include "Buffer.hh"
#include <iostream>

namespace oct::core::v2
{

	void grammar_stmt(octetos_core_Tray* ty)
	{
		int tok = oct::core::v3::yylex(ty);

		switch(tok)
		{
		case v3::ENDOFINPUT:

			return;
		case v3::EXTRACT_KW:
			std::cout << "EXTRACT";
			return;
		case v3::FROM_KW:
			std::cout << "FROM";
			return;
		case v3::NUMBERS_KW:
			std::cout << "NUMBERS";
			return;
		case v3::ALL_KW:
			std::cout << "ALL";
			return;
		case v3::NUMBER_VALUE:
			std::cout << "NUMBER";
			return;
		case v3::PRERELEASE_VALUE:
			std::cout << "PRERELEASE";
			return;
		case v3::BUILD_VALUE:
			std::cout << "BUILD";				
			return;
		}

		
	}
	bool Semver::parser(const char* str)
	{
		octetos_core_Tray ty;
        ty.dysplay_erro = 0;
        ty.version = this;
        ty.state = 0;
        std::string cmdstr = "extract all from ";
        cmdstr += str;
        ty.str = (char*)cmdstr.c_str();
        ty.buffer = new Buffer(ty.str);

		//parser
		std::cout << str << "\n";
		grammar_stmt(&ty);
		
		delete ty.buffer;
        return false;
	}
}
