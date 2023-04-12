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

namespace oct::core
{

bool Buffer::empty() const
{
	if(buffer1[forward] == 0) return true;
	if(forward + 1 <= bsize) return false;

	return false;
}
void Buffer::prev_char()
{
	forward--;
}
const char* Buffer::get_text() const
{
	return text;
}
const char* Buffer::get_buffer(unsigned short index) const
{
	if(index == 0) return buffer1;

	return NULL;
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
	//if(forward <= begin) return;
	short len = (forward - begin) + 1;
	if (len == 0) return;
	text = (char*) malloc(len);
	memcpy(text,&(buffer1[begin]),len);
	text[len] = 0;
	begin = forward + 1;
	if (not text) return;
	bufs.push_back(text);
}
char Buffer::next_char()
{
	forward++;
	return buffer1[forward];
}
Buffer::Buffer(const char* str)
{
	bsize = short(strlen(str)) + 1;

	buffer1 = (char*) malloc(bsize);
	if(not buffer1) return;
	buffer2 = NULL;
	begin = 0;
	forward = -1;
	text = NULL;
#ifdef COMPILER_VS
	strcpy_s(buffer1, bsize,str);
#elif defined __GNUC__
	strcpy(buffer1, str);
#else
#error "opilador Desconocido."
#endif
}
Buffer::~Buffer()
{
	if (buffer1) free(buffer1);
	if (buffer2) free(buffer2);
	for (char* p : bufs)
	{
		if(p) free(p);
	}
}

}
