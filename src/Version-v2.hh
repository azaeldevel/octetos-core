#ifndef OCTETOS_CORE_VERSION_V2_HH
#define OCTETOS_CORE_VERSION_V2_HH

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
#include "common.h"

namespace oct::core::v2
{
	class OCTETOS_CORE_DECLSPCE_DLL InvalidComparison : public Error
	{
	public:
		InvalidComparison(const std::string& msg ,std::string filename,int lineNumber);
		InvalidComparison(const std::string& msg);
	};
	
	/**
	*\brief interface para impermentar protocvo de versionado
	*\since 2.0
	**/
	class OCTETOS_CORE_DECLSPCE_DLL Version
	{
	public:
		virtual bool operator ==(const Version&)const = 0;
		virtual bool operator !=(const Version&)const = 0;
		virtual bool operator >(const Version&)const = 0;
		virtual bool operator <(const Version&)const = 0;
		virtual bool operator >=(const Version&)const = 0;
		virtual bool operator <=(const Version&)const = 0;
	};

	typedef octetos_core_Semver_FormatString FormatString;
	typedef octetos_core_semver_Number Number;

	/**
	*\brief Implementacion de un subconjuto de semver v2.0.0
	*\details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
	*\since 2.0
	**/
	class OCTETOS_CORE_DECLSPCE_DLL Semver : private octetos_core_Semver , public Version
	{
	public:
		enum ImportCode
		{
			MySQL,
			PostgreSQL,
		};

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

		std::string getPrerelease() const;

		const char* getBuild() const;

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
		/**
		*\brief La version especificada la convierte a formato semver
		*\param ver Versión en formato númerico
		*\param import Código del formato en que se recive la versión.
		**/
		bool set(unsigned long ver,ImportCode import);
		/**
		* \brief Retorna una representa en texto de la version.
		* \param formato Determina el formato generado.
		* */
		std::string toString(FormatString formato = FormatString::FullString) const;
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
		/**
		* \brief Hace una copia del objecto version.
		* */
		const octetos_core_Semver& operator =(const octetos_core_Semver& v);
		const Semver& operator =(const Semver& v);
		bool extractNumbers(const std::string&);


		virtual bool operator ==(const Version&)const;
		virtual bool operator !=(const Version&)const;
		virtual bool operator >(const Version&)const;
		virtual bool operator <(const Version&)const;
		virtual bool operator >=(const Version&)const;
		virtual bool operator <=(const Version&)const;
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
