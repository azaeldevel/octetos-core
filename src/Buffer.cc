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
#include <stdlib.h> 
#include <string.h>

#include "Buffer.hh"

void Buffer::prev_char()
{
	forward--;
}
const char* Buffer::get_text() const
{
	return text;
}
char Buffer::check_char(short p)
{
	return buffer1[forward + p];
}
void Buffer::back()
{
	forward = begin;
}
void Buffer::proceed()
{
	if(text)
	{
		delete text;
	}
	short len = forward - begin + 1;
	text = (char*)malloc(len);
	memcpy(text,&(buffer1[begin]),len);
	text[len] = 0;
	begin = forward + 1;
}
char Buffer::next_char()
{
	forward++;
	return buffer1[forward];	 
}
Buffer::Buffer(const char* str)
{
	bsize = strlen(str);
	short fullsize = bsize*2;
	
	buffer1 = (char*)malloc(fullsize);
	buffer2 = NULL;
	begin = 0;
	forward = -1;
	text = NULL;
	
	strcpy(buffer1,str);
}


