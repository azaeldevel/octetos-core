
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>

#if defined(__GNUC__) && defined(__linux__)
    #include <unistd.h>
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))
    #include <direct.h>
#else
    #error "Pltaforma desconocida"
#endif

#include "Exception.hh"
#include "shell.hh"

namespace oct::core
{
#if defined(__GNUC__) && defined(__linux__)
	void Shell::mkdir(const std::string& name, bool recursive)
	{
		//Precessing
		std::string stractual;
		if(recursive)
		{
		   	std::vector<std::string> result;
		   	std::stringstream s_stream(name); //create string stream from the string
		   	while(s_stream.good())
		   	{
			  	std::string substr;
			  	getline(s_stream, substr, '/'); //get first string delimited by /
			  	result.push_back(substr);
		   	}

		   	std::string newpath ;
		   	for(const std::string& s : result)
		   	{
		   		if(s.empty())
		   		{
		   			newpath += "/";
		   			continue;
		   		}
		   		else
		   		{
		   			newpath += s;
		   		}

		   		//std::cout << newpath << "\n";
		   		stractual = newpath;
		   		//std::cout << "\tstractual :" << stractual << "\n";
		   		bool ret = exists(newpath);
		   		if( ret == false )
		   		{
		   			if(::mkdir(newpath.c_str(),0777) == -1)
		   			{
			   			std::string msg = "Fail on calling mkdir : '";
				   		msg += newpath + "'";
						throw Exception(msg,__FILE__,__LINE__);
		   			}
		   		}

		   		newpath += "/";
		   	}
		   	return;
	   	}
	   	else
	   	{
	   		//std::cout << "Step 1\n";
	   		std::vector<std::string> result;
		   	std::stringstream s_stream(name); //create string stream from the string
		   	//std::cout << "Step 2\n";
		   	while(s_stream.good())
		   	{
			  	std::string substr;
			  	getline(s_stream, substr, '/'); //get first string delimited by /
			  	result.push_back(substr);
		   	}

		   	//std::cout << "Step 3\n";
		   	std::string newpath ;
		   	for(int i = 0; i < result.size() - 1 ; i++)
		   	{
		   		newpath += result[i] + "/";
			   	//std::cout << "Step 4\n";
			   	bool ret = exists(newpath);
		   		if( ret == false)
			   	{
			   		std::string msg = "No existe el archivo ";
			   		msg += newpath;
					throw Exception(msg,__FILE__,__LINE__);
			   	}
		   	}
		   	stractual = newpath;
		   	int ret = ::mkdir(name.c_str(),0777);
			if(ret == 0) return;
	   	}

		ERROR:
		//validacion de error
		if(errno != 0)
		{
			std::string msg = "Fail on floor '";
			msg += stractual + "' \n\t";
			switch(errno)
			{
				case EACCES:
					msg += "Search permission is denied on a component of the path prefix, or write permission is denied on the parent directory of the directory to be created";
					break;
				case EEXIST:
					msg += "The named file exists";
					break;
				case ELOOP:
					msg += "A loop exists in symbolic links encountered during resolution of the path argument";
					break;
				case EMLINK:
					msg += "The link count of the parent directory would exceed {LINK_MAX}";
					break;
				case ENAMETOOLONG:
					msg += "The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}";
					break;
				case ENOENT:
					msg += "A component of the path prefix specified by path does not name an existing directory or path is an empty string";
					break;
				case ENOSPC:
					msg += "The file system does not contain enough space to hold the contents of the new directory or to extend the parent directory of the new directory";
					break;
				case ENOTDIR:
					msg += "A component of the path prefix is not a directory";
					break;
				case EROFS:
					msg += "The parent directory resides on a read-only file system";
					break;
			}

			throw Exception(msg,__FILE__,__LINE__);
		}
	}
#elif defined(__GNUC__) && (defined(_WIN32) || defined(_WIN64))
void Shell::mkdir(const std::string& name, bool recursive)
	{
		//Precessing
		std::string stractual;
		if(recursive)
		{
		   	std::vector<std::string> result;
		   	std::stringstream s_stream(name); //create string stream from the string
		   	while(s_stream.good())
		   	{
			  	std::string substr;
			  	getline(s_stream, substr, '/'); //get first string delimited by /
			  	result.push_back(substr);
		   	}

		   	std::string newpath ;
		   	for(const std::string& s : result)
		   	{
		   		if(s.empty())
		   		{
		   			newpath += "/";
		   			continue;
		   		}
		   		else
		   		{
		   			newpath += s;
		   		}

		   		//std::cout << newpath << "\n";
		   		stractual = newpath;
		   		//std::cout << "\tstractual :" << stractual << "\n";
		   		bool ret = exists(newpath);
		   		if( ret == false )
		   		{
		   			if(::_mkdir(newpath.c_str()) == -1)
		   			{
			   			std::string msg = "Fail on calling mkdir : '";
				   		msg += newpath + "'";
						throw Exception(msg,__FILE__,__LINE__);
		   			}
		   		}

		   		newpath += "/";
		   	}
		   	return;
	   	}
	   	else
	   	{
	   		//std::cout << "Step 1\n";
	   		std::vector<std::string> result;
		   	std::stringstream s_stream(name); //create string stream from the string
		   	//std::cout << "Step 2\n";
		   	while(s_stream.good())
		   	{
			  	std::string substr;
			  	getline(s_stream, substr, '/'); //get first string delimited by /
			  	result.push_back(substr);
		   	}

		   	//std::cout << "Step 3\n";
		   	std::string newpath ;
		   	for(int i = 0; i < result.size() - 1 ; i++)
		   	{
		   		newpath += result[i] + "/";
			   	//std::cout << "Step 4\n";
			   	bool ret = exists(newpath);

		   		if( ret == false)
			   	{
			   		std::string msg = "No existe el archivo ";
			   		msg += newpath;
					throw Exception(msg,__FILE__,__LINE__);
			   	}
		   	}
		   	stractual = newpath;
		   	int ret = ::_mkdir(name.c_str());
		   	if(ret == 0) return;
	   	}

		ERROR:
		//validacion de error
		if(errno != 0)
		{
			std::string msg = "Fail on floor '";
			msg += stractual + "' on ";
			msg += cwd() + "' \n\t";
			switch(errno)
			{
				case EACCES:
					msg += "Search permission is denied on a component of the path prefix, or write permission is denied on the parent directory of the directory to be created";
					break;
				case EEXIST:
					msg += "The named file exists";
					break;
				case ELOOP:
					msg += "A loop exists in symbolic links encountered during resolution of the path argument";
					break;
				case EMLINK:
					msg += "The link count of the parent directory would exceed {LINK_MAX}";
					break;
				case ENAMETOOLONG:
					msg += "The length of the path argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}";
					break;
				case ENOENT:
					msg += "A component of the path prefix specified by path does not name an existing directory or path is an empty string";
					break;
				case ENOSPC:
					msg += "The file system does not contain enough space to hold the contents of the new directory or to extend the parent directory of the new directory";
					break;
				case ENOTDIR:
					msg += "A component of the path prefix is not a directory";
					break;
				case EROFS:
					msg += "The parent directory resides on a read-only file system";
					break;
			}

			throw Exception(msg,__FILE__,__LINE__);
		}
	}
#elif defined(_WIN32) || defined(_WIN64)
	void Shell::mkdir(const std::string& name, bool recursive)
	{
		throw Exception("No implemketado aun.",__FILE__,__LINE__);
	}
#else
	#error "Pltaforma desconocida"
#endif

}
