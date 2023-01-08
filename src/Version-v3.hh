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

#include "Exception-v3.hh"
#include "Buffer.hh"

namespace oct::core::v3
{
	/**
	*\brief Implemete un subconjuto de semver v2.0.0
	*\details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
	*\since 2.0
	**/
	class OCTETOS_CORE_DECLSPCE_DLL Semver
	{
	public:
		typedef short Number;

		class ExceptionLexer : public Exception
		{
		public:
			enum Errors
			{
				NoError,
				NOT_BUFFER_CREATED,
			};
		public:
			ExceptionLexer();
			ExceptionLexer(unsigned int code);
			ExceptionLexer(unsigned int code, const char* subject);
			ExceptionLexer(unsigned int code, const char* filename, unsigned int line);
			ExceptionLexer(unsigned int code, const char* subject, const char* filename, unsigned int line);

			const char* what() const throw ();
		};

	public:

		/**
		* \brief Crea el objeto a partir de un string
		* */
		Semver(const char*);
		Semver(const std::string&);
		Semver(const Semver&);
		Semver();
		/**
		* \brief Asigna numero major y menor. A patch se asigna a 0, los restantas datos son limpiados.
		* */
		Semver(Number major,Number minor);
		/**
		* \brief Asigna numero major, menor y patch, los restantas datos son limpiado
		* */
		Semver(Number major,Number minor,Number patch);

		virtual ~Semver();

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
		/**
		* \brief Retorna el número stage o Pre-release number (prefijo -)
		* */
		const char* get_stage() const;
		/**
		* \brief Retorna el número build (prefijo +)
		* */
		const char* get_build() const;

		/**
		* \brief Asigna todos los campos de version.
		* */
		void set(Number major,Number minor,Number patch, const std::string&);
		/**
		* \brief Asigna numero major, menor y patch.
		* */
		void set(Number major,Number minor,Number patch);
		/**
		* \brief Asigna numero major y menor. A patch se le asigna 0.
		* */
		void set(Number major,Number minor);
		/**
		* \brief Asigna solamanete el valor major. A menor y patch se le asigna 0.
		* */
		void set(Number major);
		/**
		* \brief Asigna solamanete el valor Prerelease.
		* */
		void setPrerelease(const char*);

		void setBuild(const char*);



		const Semver& operator =(const Semver& v);

		operator std::string()const;

		virtual bool operator ==(const Semver&)const;
		virtual bool operator !=(const Semver&)const;
		virtual bool operator >(const Semver&)const;
		virtual bool operator <(const Semver&)const;
		virtual bool operator >=(const Semver&)const;
		virtual bool operator <=(const Semver&)const;
		virtual bool empty() const;

		virtual Semver& operator =(const char*);
		virtual Semver& operator =(const std::string&);


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
		void copy_build(const char*);

		int yylex(Tray* ty);
		int grammar_stmt(Tray* ty);
		int grammar_version(Tray* ty);
		int grammar_prer(Tray* ty);
		int grammar_build(Tray* ty);
	};

	extern Semver version;
}


#endif
