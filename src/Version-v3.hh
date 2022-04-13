#ifndef OCTETOS_CORE_VERSION_V3_HH
#define OCTETOS_CORE_VERSION_V3_HH

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
#include <vector>


#include "common.h"
#include "semver-lexer.h"

namespace oct::core::v3
{
	
	/**
	*\brief interface para impermentar protocvo de versionado
	*\since 2.0
	**/
	class Version
	{
	public:
		virtual bool operator ==(const Version&)const = 0;
		virtual bool operator !=(const Version&)const = 0;
		virtual bool operator >(const Version&)const = 0;
		virtual bool operator <(const Version&)const = 0;
		virtual bool operator >=(const Version&)const = 0;
		virtual bool operator <=(const Version&)const = 0;
		virtual bool empty() const= 0;//TODO:proponer para nueva interface
		virtual Version& operator =(const char*) = 0;//TODO:proponer para nueva interface
		virtual Version& operator =(const std::string&) = 0;//TODO:proponer para nueva interface
	};

	typedef octetos_core_Semver_FormatString FormatString;
	typedef octetos_core_semver_Number Number;

	/**
	*\brief Implemete un subconjuto de semver v2.0.0
	*\details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
	*\since 2.0
	**/
	class Semver : private octetos_core_Semver , public v3::Version
	{
	public:
		/**
		* \brief Limpia todos los datos
		* */
		void init();
		/**
		* \brief Retorna el numero major.
		* */
		Number getMajor() const;
		/**
		* \brief Retorna el número menor
		* */
		Number getMinor() const;
		/**
		* \brief Retorna el número patch
		* */
		Number getPatch() const;

		const char* getPrerelease() const;

		/**
		* \brief Asigna todos los campos de version.
		* */
		void set(Number major,Number minor,Number patch, const std::string&);
		/**
		* \brief Asigna numero major, menor y patch.
		* */
		void setNumbers(Number major,Number minor,Number patch);
		/**
		* \brief Asigna numero major y menor. A patch se le asigna 0.
		* */
		void setNumbers(Number major,Number minor);
		/**
		* \brief Asigna solamanete el valor major. A menor y patch se le asigna 0.
		* */
		void setNumbers(Number major);
		/**
		* \brief Asigna solamanete el valor Prerelease.
		* */
		void setPrerelease(const char*);

		void setBuild(const char*);

		operator std::string()const;
		virtual ~Semver();
		Semver(const Semver&);
		Semver();
		/**
		* \brief Crea el objeto a partir de un string
		* */
		Semver(const char*);
		/**
		* \brief Asigna numero major y menor. A patch se asigna a 0, los restantas datos son limpiados.
		* */
		Semver(Number major,Number minor);
		/**
		* \brief Asigna numero major, menor y patch, los restantas datos son limpiado
		* */
		Semver(Number major,Number minor,Number patch);

		const Semver& operator =(const Semver& v);


		virtual bool operator ==(const Version&)const;
		virtual bool operator !=(const Version&)const;
		virtual bool operator >(const Version&)const;
		virtual bool operator <(const Version&)const;
		virtual bool operator >=(const Version&)const;
		virtual bool operator <=(const Version&)const;
		virtual bool empty() const;

		virtual Version& operator =(const char*);
		virtual Version& operator =(const std::string&);


		bool parse(const char* );
	};

	
}


#endif
