#ifndef OCTETOS_CORE_ERROR_HH
#define OCTETOS_CORE_ERROR_HH

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

#include <string>
#include <exception>

#include "Exception.hh"

namespace oct::core
{
	/**
	* \brief Clase dedicda a la gestion de errores
    * \details Aunque se puede comportar como una exception estandar, su pricipal capacidad radica en sus metodo get, chech y write (staticos). Unaves escrito un mesaje mediante write esta dispoble para el retos del modulo mediante la funcion get. Use chech para determinar si hay alguno error registrado sin leer.
    * */
	
	class Error : public Exception
	{
	public:
		/**
		*\brief Codigo de erros genéricos
		* */
		enum Codes
		{
			/**
			* \brief Usado cuando no se espefica codigo.
			**/
			NOTCODED,
			/**
			* \brief Cuando el motivo no es claro.
			**/
			ERROR_UNKNOW,
			/**
			* \brief se utiliza cuando se llama a get sin que halla error
			* */
			ERROR_NOTERROR,
			/**
			* \brief Cuando el se detecta un error generado fuera del alcance del manejador.
			**/
			ERROR_NOTADDRESSED,
			ERROR_ARTIFACT,
			EROOR_BUFFER,
			ERROR_LICENCE,
			ERROR_OBJECT,
			/**
			* \brief Codigo generico usado para la clase Version.
			* */
			ERROR_VERSION,
			ERROR_VERSION_INVALID_COMPARISON,
			ERROR_VERSION_PARSING,
			ERROR_LECENCE,
			ERROR_PACKAGE,
			ERROR_DB_CONNECTION = 1000,
			ERROR_DB_QUERY,
			ERROR_DB_SUPPORTED,
			ERROR_DB,
			ERROR_SOFTWARE = 2000,
			/**
			* \brief Cada modulo que implemete gestion de error deve asignar el valor de inicio de su enumeracion con este valor para evitar conflictos.
			* */
			ROOFCODE = 3001
		};
		/**
		* \brief requerido por std::exception
		* */
		virtual ~Error() throw();
		/**
		* \brief requerido por std::exception
		* */
		virtual const char* what() const throw();
		/**
		* \brief retorna un obejto std::string con la descripcion del error.
		* \details Basicamente es la misma informacion retornado por el metodo what, sin enbargo en este caso se retorna una referencia al objeto intenor que matenien la informacion
		* */
		virtual const std::string& describe() const throw();
		int getCode()const;
		/**
		* \brief Especifica en el mensaje  una descricion y codigo de error.
		* */
		Error(const std::string&) throw();
		/**
		* \brief Especifica en el mensaje  una descricion y codigo de error.
		* */
		Error(const std::string&, int code) throw();
		/**
		* \brief Especifica en el mensaje  un comentario, codigo de error, nombre de archivo y linea.
		* */
		Error(const std::string&, int code,std::string filename,int lineNumber) throw();
		/**
		* \brief Returna una copia del objeto error y limpa el registro
		* */
		/**
		* \brief Especifica en el mensaje  una descricion y codigo de error.
		* */
		Error(const Error&) throw();
		operator const std::string&();
		/**
		* \brief Retorna el error si lo hay
		* */
		[[deprecated]]  static Error get();
		/**
		* \brief Retorna el error si lo hay
		* */
		[[deprecated]]  static const Error* see() ;
		/**
		* \brief Verifica si hay error en el registro.
		* \details Esta funcion no modifica el registro. Usela al inciar una funcion si retorna true termine su funcion con error pero sin escribir uno nuevo. Una vez que la funcion apropiada reciba de nuevo el control prodra usará get para determinar el error causado.
		* \return returna true si hay un error en el registro o falso en otro caso.
		* */
		[[deprecated]]  static bool check();
		/**
		* \brief Registra un nuevo error
		* \details Si hay un error registrado la funcion retronara de inmediato con valor false, de otra forma escribira el error y retornara con valor true.
		* \return true si registro el error y falso si fallo(muy provablemento devido a que ya habia un error registrado)
		* */
		[[deprecated]]  static bool write(const Error& e);
	private:
		/**
		* \brief el mesaje de error es contruido durante la contruccion del objeto y se almacena aquí.
		* */
		//std::string full;
		int code;
		/**
		* \brief Almacena el codifo de error actual.
		* */
		static const Error* error;
	};

}

namespace octetos::core
{
	typedef oct::core::Error Error;
}

#endif
