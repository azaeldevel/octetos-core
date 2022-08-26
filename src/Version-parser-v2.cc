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
#include "Buffer.hh"

namespace oct::core::v2
{
	int Semver::grammar_build(Semver::Tray* ty)
	{
		int tok = yylex(ty);
		
		if(tok == BUILD_VALUE)
		{
			copy_build(yylval.str);
			return true;
		}

		return false;
	}
	int Semver::grammar_prer(Semver::Tray* ty)
	{
		int tok = yylex(ty);
		//std::cout << "tok prer 2 '" << tok << "'\n";
		
		if(tok == PRERELEASE_VALUE)
		{
			copy_prerelease(yylval.str);
			return true;
		}

		return false;
	}
	int Semver::grammar_version(Semver::Tray* ty)
	{
		int tok = yylex(ty);
		//std::cout << "tok " << tok << "\n";
		
		if(tok == NUMBER_VALUE)
		{
			//ty->version->major = atoi(((Buffer*)ty->buffer)->get_text());
			ty->version->major = yylval.sval;
			//std::cout << "Major : " << ty->version->major << "\n";
			tok = yylex(ty);
			if(tok == ENDOFINPUT) return tok;
			if(tok == '.')
			{
				tok = yylex(ty);
				if(tok == ENDOFINPUT) return tok;
				if(tok == NUMBER_VALUE)
				{
					ty->version->minor = yylval.sval;
					//std::cout << "minor : " << ty->version->minor << "\n";
					tok = yylex(ty);
					//std::cout << "next : " << tok << "\n";
					if(tok == ENDOFINPUT) return tok;
					if(tok == '.')
					{
						tok = yylex(ty);
						if(tok == ENDOFINPUT) return tok;
						if(tok == NUMBER_VALUE)
						{
							ty->version->patch = yylval.sval;
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
	int Semver::grammar_stmt(Tray* ty)
	{
		//std::cout << "grammar_stmt  Step 1\n";
		
		int tok = grammar_version(ty);
		
		//std::cout << "grammar_stmt  Step 2\n";

		if(tok == ENDOFINPUT) return tok;
		
		//std::cout << "grammar_stmt  Step 3\n";

		tok = yylex(ty);
		
		if(tok == '-')
		{
			tok = grammar_prer(ty);
		}
		
		//std::cout << "grammar_stmt  Step 4\n";
		
		if(tok == ENDOFINPUT) return tok;
		
		//std::cout << "grammar_stmt  Step 5\n";
		
		tok = yylex(ty);
		
		if(tok == '+')
		{
			tok = grammar_build(ty);
		}
		
		//std::cout << "grammar_stmt  Step 6\n";
		
		return true;
	}
	bool Semver::parse(const char* str)
	{
		Tray ty(str, this);
        //ty.dysplay_erro = 0;
        //ty.version = this;
        ty.state = 0;
        //ty.str = str;
		//std::cout << "String : " << ty.str << "<<--\n";
        //ty.buffer = new Buffer(str);
		//std::cout << "Buffer : " << ((Buffer*)ty.buffer)->get_buffer(0) << "<<--\n";
		
		//parser
		bool ret = grammar_stmt(&ty);
		//std::cout << "Major : " << major << "<<--\n";
		
		//delete ty.buffer;		
        return ret;
	}
}
