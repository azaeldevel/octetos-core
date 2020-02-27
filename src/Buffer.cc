#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#include "Buffer.hh"

void Buffer::unget()
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
char Buffer::get_char()
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


