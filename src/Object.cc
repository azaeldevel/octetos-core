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
#if defined(__linux__)
	#include "config.h"
#elif defined(_WIN32) || defined(_WIN64)
#else
    #error "Plataforma desconocida"
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

	std::string getPakageName()
	{
		return PACKAGE;
	}


}
