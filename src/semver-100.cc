#include <stdio.h>
#include <string.h>

#include "semver-100.h"
#include "Buffer.hh"
#include <iostream>

#include "semver-100.tab.h"


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
extern "C" int yylex(struct octetos_core_Tray* ty)
{
	//std::cout << "yylex --> Step 1: \n";
	if(!ty->buffer)
	{
		ty->buffer = new Buffer(ty->str); 
	}
	//std::cout << "yylex --> Step 2: \n";
	Buffer* buffer = (Buffer*)ty->buffer;
	//std::cout << "yylex --> Step 3: \n";
	char c = buffer->next_char();
	//std::cout << "yylex --> Step 4: \n";
	
	while (true)
	{		
		while(c == ' ')
		{// consume los porximos espacios en blanco
			buffer->proceed();
			c = buffer->next_char();
		}
		if(c != ' ')
		{
			buffer->prev_char();
		}
		//std::cout << "Estado " << ty->state << "--" << c << "-->\n";
		switch(ty->state)
		{
			case 0:
				//std::cout << "Estado : Inicial\n";
				if(is_letter(c)) 
				{
					if(c == 'e')
					{
						ty->state = EXTRACT_KW;
					}
					else if(c == 'f')
					{
						ty->state = FROM_KW;
					}
					else if(c == 'n')
					{
						ty->state = NUMBERS_KW;
					}
					else if(c == 'a')
					{
						ty->state = ALL_KW;
					}
				}
				else if(is_digit(c))
				{
					ty->state = NUMBER_VALUE;
				}
				else
				{
					ty->state = -1;
				}
				break;
			case EXTRACT_KW:
				//std::cout << "Estado : EXTRACT_KW\n";
				if(is_extract_keyword(buffer))
				{
					//std::cout << "keyword '" << buffer->get_text() << "'\n";
					ty->state = 0;
					return EXTRACT_KW;
				}
				break;
			case ALL_KW:
				//std::cout << "Estado : ALL_KW\n";
				if(is_all_keyword(buffer)) 
				{
					//std::cout << "keyword '" << buffer->get_text() << "'\n";
					ty->state = 0;
					return ALL_KW;
				}
				break;
			case FROM_KW:
				//std::cout << "Estado : FROM_KW\n";
				if(is_from_keyword(buffer)) 
				{
					//std::cout << "keyword '" << buffer->get_text() << "'\n";
					ty->state = 0;
					return FROM_KW;
				}
				break;
			case NUMBERS_KW:
				//std::cout << "Estado : NUMBERS_KW\n";
				if(is_numbers_keyword(buffer)) 
				{
					//std::cout << "keyword '" << buffer->get_text() << "'\n";
					ty->state = 0;
					return NUMBERS_KW;
				}
				break;
			case NUMBER_VALUE:
				//std::cout << "Estado : NUMBER_VALUE\n";
				c = buffer->next_char();
				if(is_digit(c))
				{
					while(is_digit(c))  
					{
						c = buffer->next_char();
					}
					buffer->prev_char();
					buffer->proceed();
					yylval.sval=(short)atoi(buffer->get_text());
					//std::cout << "Number '" << buffer->get_text() << "'\n";
					return NUMBER_VALUE;
				}	
				
				if(c == '.')
				{
					//c = buffer->next_char(); //se hizo unget
					buffer->proceed();
					return '.';
				}
				else if(c == '-')
				{
					ty->state = PRERELEASE_VALUE;
					buffer->proceed();
					return '-';
				}				
				break;
			case PRERELEASE_VALUE:
			{
				//std::cout << "Estado : PRERELEASE_VALUE\n";
				//std::cout << "PRER- '" << c << "'\n";
				nextChartPreR:
				c = buffer->next_char();
				if(is_digit(c) || is_letter(c) || c == '-' || c == '.' )
				{
					goto nextChartPreR;
				}		
				else if (c == 0)
				{
					buffer->prev_char();
				}
				else
				{
					return ENDOFINPUT;
				}
				buffer->proceed();
				//std::cout << "Prerelease '" << buffer->get_text() << "'\n";
				short strl = strlen(buffer->get_text());
				yylval.str = (char*)malloc(strl+1);
				strcpy((char*)(yylval.str),buffer->get_text());
				ty->state = ENDOFINPUT;
				return PRERELEASE_VALUE;
			}
			case ENDOFINPUT:	
				return ENDOFINPUT;
			default:
				return 0;
		}
	}
	
	return 0;
}
