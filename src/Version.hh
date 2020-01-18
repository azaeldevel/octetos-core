#ifndef OCTETOS_CORE_VERSION_HH
#define OCTETOS_CORE_VERSION_HH
#include <string>
#include <vector>

#include "Error.hh"
#include "Object.hh"
#include "common.h"
#include "semver-parser.h"

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

	class Version
	{
	public:
		virtual bool operator ==(const Version&)const = 0;
		virtual bool operator !=(const Version&)const = 0;
		virtual bool operator >(const Version&)const = 0;
		virtual bool operator <(const Version&)const = 0;
		virtual bool operator >=(const Version&)const = 0;
		virtual bool operator <=(const Version&)const = 0;
	};
	
	namespace semver
	{						
		typedef octetos_core_Semver_FormatString FormatString;
		typedef octetos_core_semver_Number Number;
	
		enum ImportCode
		{
			MySQL,
			PostgreSQL,
		};

		class Semver : protected octetos_core_Semver , public core::Version
		{
		private:
			int (*parser)(struct octetos_core_Tray*,const char*);
			void* handle;
		protected:
			bool loadParser(const char* sufix);
			
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
		    
			bool isDevelopingStage() const;
			
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
			operator std::string();
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
		    /**
		    * \brief Hace una copia del objecto version.
		    * */
			const octetos_core_Semver& operator =(const octetos_core_Semver& v);
			const Semver& operator =(const Semver& v);		
			/**
			*\brief Indica la version semver implemetada.
			**/
			virtual const Semver& getVersion() const = 0;
		
			bool extractNumbers(const std::string&);
		};

		/**
		 * \brief Implemete un subconjuto de semver v1.0.0
		 * \details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
		 **/
		class v100: public Semver
		{		
		private:
			static v100* version;
						    
		public:
		    virtual bool operator ==(const Version& v)const;
		    virtual bool operator !=(const Version& v)const;
			virtual bool operator >=(const Version& v)const;
		    virtual bool operator >(const Version& v)const;
		    virtual bool operator <=(const Version& v)const;
			virtual bool operator <(const Version& v)const; 		            
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

			virtual const Semver& getVersion() const;
		};

		/**
		 * \brief Implemete un subconjuto de semver v2.0.0
		 * \details Acerda de 'Semantica de Versionado' https://semver.org/spec/v2.0.0.html.
		 **/
		class v200: public Semver
		{	
		private:
			static v200* version;
							    
		public:
		    virtual bool operator ==(const Version& v)const;
		    virtual bool operator !=(const Version& v)const;
			virtual bool operator >=(const Version& v)const;
		    virtual bool operator >(const Version& v)const;
		    virtual bool operator <=(const Version& v)const;
			virtual bool operator <(const Version& v)const; 		            
		    /**
		    * \brief Simple mente limpa las variables intenas
		    * */
		    virtual ~v200();
			v200();
		    /**
		    * \brief Asigna numero major y menor. A patch se asigna a 0, los restantas datos son limpiados.
		    * */
			v200(short major,short minor);
		    /**
		    * \brief Asigna numero major, menor y patch, los restantas datos son limpiados
		    * */
			v200(short major,short minor,short patch);	

			virtual const Semver& getVersion() const;	
		};
	}

	typedef semver::v100 Semver;
	typedef semver::v100 Semver_v100;
	typedef semver::v200 Semver_v200;
	
	/**
	 * \brief retorna la version actual de componente
	 **/
	Semver getPakageVersion();	
}
}
#endif
