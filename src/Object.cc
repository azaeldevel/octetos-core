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
//#include <iostream>
//#include <cstdlib>
//#include <cstring>
//#include <string.h>
//#include <string>

#ifdef HAVE_CONFIG_H
    #include "config.h"
#elif defined WINDOWS_MINGW && defined CODEBLOCKS
    #include "config-cb.h"
#elif defined LINUX && defined CODEBLOCKS
    #include "config-cb.h"
#endif
#include "Object.hh"

namespace oct::core
{
	bool Object::checkCollectionAssistant()const
	{
#ifdef COLLETION_ASSISTANT
		return true;
#else
		return false;
#endif
	}
        Object::~Object()
        {
#ifdef COLLETION_ASSISTANT
                if(parent != NULL)
                {
                        parent->removeChild(this);
                }
                if(countChilds > 0)
                {
                        std::cerr << "Una instacia de '" << typeid(*this).name() << "' termino sin que todos sus hijos terminaran  primero" << std::endl;
                }
#endif
        }

        Object::Object()
        {
#ifdef COLLETION_ASSISTANT
                countChilds = 0;
                parent = NULL;
#endif
        }

#ifdef COLLETION_ASSISTANT
        unsigned int Object::getCountChilds()
        {
                return countChilds;
        }
        void Object::addChild(Object* child)
        {
                countChilds++;
                child->parent = this;
        }
        void Object::removeChild(Object* child)
        {
                countChilds--;
                child->parent = NULL;
        }
#endif


#ifdef __GNUC__
	std::string getPakageName()
	{
		return PACKAGE;
	}
#endif

}
