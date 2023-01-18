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

#include "Error.hh"
#include "Buffer.hh"

namespace oct::core::v3
{

	typedef short Number;

	/**
	*\brief Implementacion de un subconjuto de semver v2.0.0
	*\details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
	*\since 2.0
	**/
	class OCTETOS_CORE_DECLSPCE_DLL Semver
	{
	public:
		class Exception : public v3::Exception
		{
		public:

		public:
			Exception();
			Exception(const Exception&);

			//>>>pereferecia
			Exception(const char* message);
			Exception(const char* message,const char* filename, unsigned int line);

			virtual ~Exception();
			
			//virtual const char* what() const throw ();

		protected:
			
		private:

		};
	public:
		/**
		* \brief Limpia todos los datos
		* */
		void init();
		/**
		* \brief Retorna el numero major.
		* */
		Number get_major() const;
		/**
		* \brief Retorna el número menor
		* */
		Number get_minor() const;
		/**
		* \brief Retorna el número patch
		* */
		Number get_patch() const;

		const char* get_stage() const;

		const char* get_build() const;

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
		* \brief Lee la cadena de texto para determinar los valores de los componentes.
		* */
		bool set(const std::string&);
		/**
		* \brief Asigna solamanete el valor Prerelease.
		* */
		void setPrerelease(const std::string&);

		operator std::string()const;
		virtual ~Semver();
		Semver(const Semver&);

		Semver();
		/**
		* \brief Asigna numero major y menor. A patch se asigna a 0, los restantas datos son limpiados.
		* */
		Semver(Number major,Number minor);
		/**
		* \brief Crea el objeto a partir de un string
		* */
		Semver(const char*);
		/**
		* \brief Asigna numero major, menor y patch, los restantas datos son limpiado
		* */
		Semver(Number major,Number minor,Number patch);
		const Semver& operator =(const Semver& v);


		virtual bool operator ==(const Semver&)const;
		virtual bool operator !=(const Semver&)const;
		virtual bool operator >(const Semver&)const;
		virtual bool operator <(const Semver&)const;
		virtual bool operator >=(const Semver&)const;
		virtual bool operator <=(const Semver&)const;
		virtual bool empty() const;
				
		bool parse(const char* );

	private:
		enum Tokens
		{
			YYEMPTY = -2,
			YYEOF = 0,                     /* "end of file"  */
			YYerror = 256,                 /* error  */
			YYUNDEF = 257,                 /* "invalid token"  */

			ENDOFINPUT,              /* ENDOFINPUT  */
			EXTRACT_KW,              /* EXTRACT_KW  */
			FROM_KW,                 /* FROM_KW  */
			NUMBERS_KW,              /* NUMBERS_KW  */
			ALL_KW,                  /* ALL_KW  */
			NUMBER_VALUE,            /* NUMBER_VALUE  */
			PRERELEASE_VALUE,        /* PRERELEASE_VALUE  */
			BUILD_VALUE             /* BUILD_VALUE  */
		};
		union Value
		{
			short sval;
			unsigned long ulval;
			const char* str;
		};
		struct Tray
		{
			Semver* version;
			Buffer buffer;
			int state;

			Tray(const char*,Semver*);
		};

	private:
		Number major;
		Number minor;
		Number patch;
		char* prerelease;
		char* build;

		Value yylval;
	private:
		void copy_prerelease(const char*);
		void free_prerelease();
		void copy_build(const char*);
		void free_build();

		int yylex(Tray* ty);
		int grammar_stmt(Tray* ty);
		int grammar_version(Tray* ty);
		int grammar_prer(Tray* ty);
		int grammar_build(Tray* ty);
	};

	extern Semver version;
}


#endif
