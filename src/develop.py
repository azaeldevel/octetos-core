#!/usr/bin/env python
# -*- Mode: Python; coding: utf-8; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- 
#
# main.py
# Copyright (C) 2019 Azael R. <azael.devel@gmail.com>
# 
# python-foobar is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# python-foobar is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.

print "Hello World! 2"
import ctypes 
NUM = 16      
# libfun loaded to the python file 
# using fun.myFunction(), 
# C function can be accessed 
# but type of argument is the problem. 
                         
fun = ctype.CDLL(/usr/local/lib/libparser-version-c.so)   
# Now whenever argument  
# will be passed to the function                                                         
# ctypes will check it. 
            
fun.myFunction.argtypes(ctypes.c_int) 
  
# now we can call this  
# function using instant (fun) 
# returnValue is the value  
# return by function written in C  
# code 
returnVale = fun.myFunction(NUM) 

