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
	class Version : public Object
	{
	public:
        virtual bool operator ==(const Version& v)const = 0;
        virtual bool operator !=(const Version& v)const = 0;
        virtual bool operator >(const Version& v)const = 0;
        virtual bool operator <(const Version& v)const = 0;
		virtual bool operator >=(const Version& v)const = 0;
        virtual bool operator <=(const Version& v)const = 0;
	};

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
		};

		/**
		 * \brief Implemete un subconjuto de semver v1.0.0, la reduciones aplicada
		 * a los componentes pre-release y build. Su principal utilidad radica
		 * en el manejo de los numero, mayor, menor y patch.
		 * \details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
		 **/
		class v100: public Version, private octetos_Semver
		{
		public:

					    
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
		    virtual bool operator ==(const Version& v)const;
		    virtual bool operator !=(const Version& v)const;
		    /**
		    * \brief Determina el orden relativo entre dos obejtos Version
		    * \return true si el objeto pasado como parametro es amyor o igual, false en otro caso
		    * */
			virtual bool operator >=(const Version& v)const;
		    virtual bool operator >(const Version& v)const;
		    virtual bool operator <=(const Version& v)const;
		    /**
		    * \brief Determina el orden relativo entre dos obejtos Version
		    * \return true si el objeto pasado como parametro es menor, false en otro caso
		    * */
			bool operator <(const Version& v)const;
		    /**
		    * \brief Hace una copia del objecto version.
		    * */
			const v100& operator =(const v100& v);
		    /**
		    * \brief Hace una copia del objecto version.
		    * */
			const octetos_Semver& operator =(const octetos_Semver& v);
		            
		    /**
		    * \brief Simple mente limpa las variables intenas
		    * */
		    ~v100();
		    v100(const v100*);
		    v100(const v100&);
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
			/**
			*\brief Indica la version semver implemetada.
			**/
			v100 getVersion() const;
		};
	}

	typedef semver::v100 Semver;
}
}
#endif
