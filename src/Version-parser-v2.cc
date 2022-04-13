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


#include <iostream>
#include <stdio.h>
#include <string.h>


#include "Version-v2.hh"
#include "semver.tab.3.h"
#include "Buffer.hh"

namespace oct::core::v2
{
	int grammar_build(octetos_core_Tray* ty)
	{
		int tok = v3::yylex(ty);
		
		if(tok == v3::BUILD_VALUE)
		{
			//std::cout << "Build 1 '" << v3::yylval.str << "'\n";
			if(ty->version->build) free((void*)ty->version->build);
			short strl = strlen(v3::yylval.str);
			char* newstr = (char*)malloc(strl + 1);
			strcpy(newstr,v3::yylval.str);				
			ty->version->build = newstr;
			return tok;
		}

		return tok;
	}
	int grammar_prer(octetos_core_Tray* ty)
	{
		int tok = v3::yylex(ty);
		//std::cout << "tok prer 2 '" << tok << "'\n";
		
		if(tok == v3::PRERELEASE_VALUE)
		{
			//std::cout << "Prerelease 2 '" << v3::yylval.str << "'\n";
			if(ty->version->prerelease) free((void*)ty->version->prerelease);
			short strl = strlen(v3::yylval.str);
			char* newstr = (char*)malloc(strl + 1);
			strcpy(newstr,v3::yylval.str);				
			ty->version->prerelease = newstr;
			return tok;
		}

		return tok;
	}
	int grammar_version(octetos_core_Tray* ty)
	{
		int tok = v3::yylex(ty);
		//std::cout << "tok " << tok << "\n";
		
		if(tok == v3::NUMBER_VALUE)
		{
			//ty->version->major = atoi(((Buffer*)ty->buffer)->get_text());
			ty->version->major = v3::yylval.sval;
			//std::cout << "Major : " << ty->version->major << "\n";
			tok = v3::yylex(ty);
			if(tok == v3::ENDOFINPUT) return tok;
			if(tok == '.')
			{
				tok = v3::yylex(ty);
				if(tok == v3::ENDOFINPUT) return tok;
				if(tok == v3::NUMBER_VALUE)
				{
					ty->version->minor = v3::yylval.sval;
					//std::cout << "minor : " << ty->version->minor << "\n";
					tok = v3::yylex(ty);
					//std::cout << "next : " << tok << "\n";
					if(tok == v3::ENDOFINPUT) return tok;
					if(tok == '.')
					{
						tok = v3::yylex(ty);
						if(tok == v3::ENDOFINPUT) return tok;
						if(tok == v3::NUMBER_VALUE)
						{
							ty->version->patch = v3::yylval.sval;
						}
					}
				}
			}
		}
		
		return tok;
	}
	/**
	  * \brief
	  * \ return true si la gramatica coincide false en otro caso.
	  */
	int grammar_stmt(octetos_core_Tray* ty)
	{
		int tok = grammar_version(ty);

		if(tok == v3::ENDOFINPUT) return tok;
		
		if(tok == '-')
		{
			tok = grammar_prer(ty);
		}

		if(tok == v3::ENDOFINPUT) return tok;
		if(tok == v3::PRERELEASE_VALUE) tok = v3::yylex(ty);
		//std::cout << "tok : " << tok << "<<--\n";
		
		if(tok == '+')
		{
			//std::cout << "tok : " << tok << "<<--\n";
			tok = grammar_build(ty);
		}
		
		return tok;
	}
	bool Semver::parser(const char* str)
	{
		octetos_core_Tray ty;
        ty.dysplay_erro = 0;
        ty.version = this;
        ty.state = 0;
        //ty.str = str;
		//std::cout << "String : " << ty.str << "<<--\n";
        ty.buffer = new Buffer(str);
		//std::cout << "Buffer : " << ((Buffer*)ty.buffer)->get_buffer(0) << "<<--\n";
		
		//parser
		bool ret = grammar_stmt(&ty);
		//std::cout << "Major : " << major << "<<--\n";
		
		delete (Buffer*)ty.buffer;		
        return ret;
	}
}
