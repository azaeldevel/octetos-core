#include <stdio.h>
#include <string.h>

#include "semver-100.h"
#include "Buffer.hh"
#include <iostream>

#include "semver-100.tab.h"

bool is_all_keyword(Buffer* buffer)
{
	char c;

	c = buffer->get_char();
	if(c != 'l') 
	{
		buffer->back();
		return false;
	}
	c = buffer->get_char();
	if(c != 'l') 
	{
		buffer->back();
		return false;
	}

	//fin de la palabra
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
	//std::cout << "is_extract_keyword()\n";
	char c;

	c = buffer->get_char();
	//std::cout << "c:" << c << "\n";
	if(c != 'x') 
	{
		buffer->back();
		return false;
	}
	c = buffer->get_char();
	//std::cout << "c:" << c << "\n";
	if(c != 't')
	{
		buffer->back();
		return false;
	}
	c = buffer->get_char();
	//std::cout << "c:" << c << "\n";
	if(c != 'r')
	{
		buffer->back();
		return false;
	}
	c = buffer->get_char();
	//std::cout << "c:" << c << "\n";
	if(c != 'a') 
	{
		buffer->back();
		return false;
	}
	c = buffer->get_char();
	//std::cout << "c:" << c << "\n";
	if(c != 'c') 
	{
		buffer->back();
		return false;
	}
	c = buffer->get_char();
	//std::cout << "c:" << c << "\n";
	if(c != 't') 
	{
		buffer->back();
		return false;
	}

	
	c = buffer->check_char(1);
	if(c != ' ') 
	{
		//std::cout << "Espacio: '" << c << "'\n";
		buffer->back();
		return false;
	}
	else
	{
		
	}

	std::cout << "Preceding: yes\n";
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
	std::cout << "yylex --> Step 1: \n";
	if(!ty->buffer)
	{
		ty->buffer = new Buffer(ty->str); 
	}
	std::cout << "yylex --> Step 2: \n";
	Buffer* buffer = (Buffer*)ty->buffer;
	std::cout << "yylex --> Step 3: \n";
	char c = buffer->get_char();
	std::cout << "yylex --> Step 4: \n";
	int state = 0;
	
	while (true)
	{
		//std::cout << c << " \n";
		//std::cout << "Estado " << state << "\n";
		switch(state)
		{
			case 0:
				if(is_letter(c)) 
				{
					//std::cout << c << " --> es letra";
					if(c == 'e')
					{
						state = EXTRACT_KW;
					}
					else if(c == 'f')
					{
						state = FROM_KW;
					}
					else if(c == 'n')
					{
						state = NUMBERS_KW;
					}
					else if(c == 'a')
					{
						state = ALL_KW;
					}
				}
				else if(is_digit(c))
				{
					state = NUMBER_VALUE;
				}
				else
				{
					state = -1;
				}
				break;
			case EXTRACT_KW:
				if(is_extract_keyword(buffer))
				{
					std::cout << "keyword " << buffer->get_text() << "\n";
					return EXTRACT_KW;
				}
				break;
			case ALL_KW:
				if(is_all_keyword(buffer)) 
				{
					std::cout << " EXTRACT \n";
					return ALL_KW;
				}
				break;
			case NUMBERS_KW:
				if(is_letter(c)) 
				{
					//std::cout << " --> es letra";
				}
				//std::cout << "\n";
				break;
			case FROM_KW:
				if(is_letter(c)) 
				{
					//std::cout << " --> es letra";
				}
				break;
			case NUMBER_VALUE:
				//std::cout << "Char : " << c;
				if(is_digit(c))  
				{
					//std::cout << " --> es digito";
				}
				//std::cout << "\n";
				break;
			default:
				return -1;
		}
	}
	
	std::cout << "yylex --> Step 5: \n";
	
	return 0;
}
