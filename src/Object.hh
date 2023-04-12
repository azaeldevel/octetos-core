#ifndef OCTETOS_CORE_OBJECT_HH
#define OCTETOS_CORE_OBJECT_HH

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

#include "defines.hh"

namespace oct::core
{

	/**
	 * \brief retorna el nombre del componente
	 **/
	std::string getPakageName();

	/**
	* \brief Clase base común de toolkit.
	* \private en desarrollo
	* */
	class Object
	{
	public:
		/**
		* \brief Contrucctor por default
		* */
		Object();
        /**
        * \brief Destructor
        * */
		virtual ~Object();
		bool checkCollectionAssistant()const;

#ifdef COLLETION_ASSISTANT
        protected:
        /**
        * \brief registra el objeto pasado como hijo.
        * */
        void addChild(Object*);
        /**
        * \brief Borra el objeto indicdo como hijo
        * */
        void removeChild(Object*);
        /**
        * \brief Retorna un contador de hijos registrado
        * */
        unsigned int getCountChilds();
    private:
        unsigned int countChilds;
        Object* parent;
        const char* createdFile;
        unsigned int line;
#endif
    };

}


namespace octetos::core
{
    typedef oct::core::Object Object;
}

#endif
