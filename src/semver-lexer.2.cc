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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "Buffer.hh"
#include "Version-v2.hh"


namespace oct::core::v2
{

Semver::Tray::Tray(const char* str, Semver* ver) : buffer(str), version(ver)
{
}


bool is_numbers_keyword(Buffer* buffer)
{
	char c;

	c = buffer->next_char();
	if(c != 'n')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'u')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'm')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'b')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'e')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'r')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 's')
	{
		buffer->back();
		return false;
	}

	c = buffer->check_char(1);
	if(c != ' ')
	{
		buffer->back();
		return false;
	}

	buffer->proceed();
	return true;
}

bool is_from_keyword(Buffer* buffer)
{
	char c;

	c = buffer->next_char();
	if(c != 'f')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'r')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'o')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'm')
	{
		buffer->back();
		return false;
	}

	c = buffer->check_char(1);
	if(c != ' ')
	{
		buffer->back();
		return false;
	}

	buffer->proceed();
	return true;
}

bool is_all_keyword(Buffer* buffer)
{
	char c;

	c = buffer->next_char();
	if(c != 'a')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'l')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'l')
	{
		buffer->back();
		return false;
	}

	c = buffer->check_char(1);
	if(c != ' ')
	{
		buffer->back();
		return false;
	}

	buffer->proceed();
	return true;
}
bool is_extract_keyword(Buffer* buffer)
{
	char c;

	c = buffer->next_char();
	if(c != 'e')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'x')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 't')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'r')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'a')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 'c')
	{
		buffer->back();
		return false;
	}
	c = buffer->next_char();
	if(c != 't')
	{
		buffer->back();
		return false;
	}


	c = buffer->check_char(1);
	if(c != ' ')
	{
		buffer->back();
		return false;
	}
	//std::cout << "Proceding : yes\n";
	buffer->proceed();
	return true;
}
bool is_letter(char c)
{
	if( c >= 65 and c <= 90) return true;
	else if( c >= 97 and c <= 122) return true;
	return false;
}
bool is_digit(char c)
{
	if( c >= 48 and c <= 57) return true;
	return false;
}
int Semver::yylex(Semver::Tray* ty)
{
	//std::cout << "yylex --> Step 1: \n";
	//if(not ty->buffer) throw ExceptionLexer(ExceptionLexer::NOT_BUFFER_CREATED,__FILE__,__LINE__);

	//std::cout << "yylex --> Step 2: \n";
	//Buffer* buffer = (Buffer*)ty->buffer;
	//std::cout << "yylex --> Step 3: \n";
	char c = ty->buffer.next_char();
	if(ty->buffer.empty()) return ENDOFINPUT;
	//std::cout << "yylex --> Step 4: \n";

	while (true)
	{
		switch(ty->state)
		{
			case 0:
				//std::cout << "Estado : Inicial\n";
				if(is_digit(c))
				{
					//std::cout << "c : '" << c << "'\n";
					ty->state = NUMBER_VALUE;
				}
				else if(is_letter(c))
				{
					return c;
				}
				else if(c == '.')
				{
					//std::cout << "c : '" << c << "'\n";
					ty->buffer.proceed();
					ty->state = 0;
					return c;
				}
				else if(c == '-')
				{
					//std::cout << "c : '" << c << "'\n";
					ty->buffer.proceed();
					ty->state = PRERELEASE_VALUE;
					//std::cout << "prefix : '" << c << "'\n";
					return c;
				}
				else if(c == '+')
				{
					ty->buffer.proceed();
					ty->state = BUILD_VALUE;
					return c;
				}
				else
				{
					ty->state = -1;
				}
				break;
			case NUMBER_VALUE:
				while(is_digit(ty->buffer.check_char(1)))
				{
					//std::cout << "c : '" << c << "'\n";
					c = ty->buffer.next_char();
				}
				//buffer->prev_char();
				ty->buffer.proceed();
				//std::cout << "Number '" << buffer->get_text() << "'\n";
				//std::cout << "Number '" << atoi(buffer->get_text()) << "'\n";
				yylval.sval = atoi(ty->buffer.get_text());
				//std::cout << "Number '" << yylval.sval << "'\n";
				ty->state = 0;
				return NUMBER_VALUE;
			case PRERELEASE_VALUE:
			{
				//std::cout << "Estado : PRERELEASE_VALUE\n";
				//std::cout << "PRER- '" << c << "'\n";
				char c_post = ty->buffer.check_char(1);
				while(is_digit(c_post) or is_letter(c_post) and c_post != '+')
				{
					//std::cout << "c : '" << c << "'\n";
					c = ty->buffer.next_char();
					c_post = ty->buffer.check_char(1);
				}
				ty->buffer.proceed();
				//std::cout << "Prerelease 1 '" << buffer->get_text() << "'\n";
				yylval.str = ty->buffer.get_text();
				ty->state = 0;
				return PRERELEASE_VALUE;
			}
			case BUILD_VALUE:
			{
				while(is_digit(ty->buffer.check_char(1)) or is_letter(ty->buffer.check_char(1)))
				{
					c = ty->buffer.next_char();
				}
				ty->buffer.proceed();
				//std::cout << "Build 1 '" << buffer->get_text() << "'\n";
				yylval.str = ty->buffer.get_text();
				ty->state = 0;
				return BUILD_VALUE;
			}
			case ENDOFINPUT:
				return ENDOFINPUT;
		}
	}

	return 0;
}



}
