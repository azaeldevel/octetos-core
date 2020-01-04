#ifndef OCTETOS_CORE_VERSION_HH
#define OCTETOS_CORE_VERSION_HH
#include <string>

#include <vector>

#include "Error.hh"
#include "Object.hh"
#include "common.h"


namespace octetos
{
namespace core
{
	class InvalidComparison : public Error
	{
	public:
		InvalidComparison(const std::string& msg ,std::string filename,int lineNumber);
		InvalidComparison(const std::string& msg);
	};

	namespace semver
	{						
		typedef octetos_Semver_FormatString FormatString;

	
		enum ImportCode
		{
			MySQL,
			PostgreSQL,
		};

		class Semver : public octetos_Semver
		{
		public:
			/**
			* \brief Limpia todos los datos
			* */
			void init();
			/**
			* \brief Retorna el numero major.
			* */
			short getMajor() const;
			/**
			* \brief Retorna el número menor
			* */
			short getMinor() const;
		    /**
		    * \brief Retorna el número patch
		    * */
			short getPatch() const;
			
			std::string getPrerelease() const;
		    

		    /**
		    * \brief Asigna todos los campos de version.
		    * */
			void set(short major,short minor,short patch, const std::string&);
		    /**
		    * \brief Asigna numero major, menor y patch.
		    * */
			void setNumbers(short major,short minor,short patch);
		    /**
		    * \brief Asigna numero major y menor. A patch se le asigna 0.
		    * */
			void setNumbers(short major,short minor);
		    /**
		    * \brief Asigna solamanete el valor major. A menor y patch se le asigna 0.
		    * */
			void setNumbers(short major);
			bool set(const std::string&);
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
			virtual ~Semver();			
			Semver();
		    /**
		    * \brief Asigna numero major y menor. A patch se asigna a 0, los restantas datos son limpiados.
		    * */
			Semver(short major,short minor);
		    /**
		    * \brief Asigna numero major, menor y patch, los restantas datos son limpiados
		    * */
			Semver(short major,short minor,short patch);


		    virtual bool operator ==(const Semver& v)const = 0;
		    virtual bool operator !=(const Semver& v)const = 0;
		    virtual bool operator >(const Semver& v)const = 0;
		    virtual bool operator <(const Semver& v)const = 0;
			virtual bool operator >=(const Semver& v)const = 0;
		    virtual bool operator <=(const Semver& v)const = 0;


		    /**
		    * \brief Hace una copia del objecto version.
		    * */
			const octetos_Semver& operator =(const octetos_Semver& v);
			const Semver& operator =(const Semver& v);
		};

		/**
		 * \brief Implemete un subconjuto de semver v1.0.0
		 * \details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
		 **/
		class v100: public Semver
		{					    
		public:
		    virtual bool operator ==(const Semver& v)const;
		    virtual bool operator !=(const Semver& v)const;
			virtual bool operator >=(const Semver& v)const;
		    virtual bool operator >(const Semver& v)const;
		    virtual bool operator <=(const Semver& v)const;
			virtual bool operator <(const Semver& v)const; 		            
		    /**
		    * \brief Simple mente limpa las variables intenas
		    * */
		    virtual ~v100();
			v100();
		    /**
		    * \brief Asigna numero major y menor. A patch se asigna a 0, los restantas datos son limpiados.
		    * */
			v100(short major,short minor);
		    /**
		    * \brief Asigna numero major, menor y patch, los restantas datos son limpiados
		    * */
			v100(short major,short minor,short patch);			
			/**
			*\brief Indica la version semver implemetada.
			**/
			v100 getVersion() const;
		};
	}

	typedef semver::v100 Semver;
	typedef Semver Version;
}
}
#endif
