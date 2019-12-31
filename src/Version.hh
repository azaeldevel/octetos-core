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
		/**
		* \brief Representa la fase del proyecto.
		* \details Tipicamente un proyecto o sprint comienz en la vervion X-alpha, luego pasa a X-beta y finalmente se genera X-release, lo que sigue a continuacion del guion es la fase aqui representado
		**/
		typedef octetos_version_Stage Stage;
						
		typedef octetos_Semver_FormatString FormatString;
		/**
		 * \brief Implemete un subconjuto de semver v1.0.0, la reduciones aplicada
		 * a los componentes pre-release y build. Su principal utilidad radica
		 * en el manejo de los numero, mayo, menor y patch
		 * \details Acerda de 'Semantica de Versionado' https://semver.org/spec/v1.0.0.html.
		 **/
		class v100: public Version, private octetos_Semver
		{
		public:	
			enum ImportCode
			{
				MySQL,
			};

					    
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
		    /**
		    * \brief Retorna build
		    * */
			unsigned long getBuildUL() const;
		    std::string getBuildString() const;
		    //const Build& getBuild() const;
		    /**
		    * \brief Retorna el estado
		    * */
			Stage getStage() const;
			const char* getStageString() const;
		    short getStageNumber() const;
		    /**
		    * \brief Retorna el nombre de la version
		    * */
			const std::string& getName() const;
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
			void set(short major,short minor,short patch,Stage stage,unsigned long build, const std::string& name);
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
		    * \brief Asigna la etapa del proyecto
		    * */
			void setStage(Stage stage);
		    /**
		    * \brief Asigna la etapa del proyecto
		    * */
			void setStage(Stage stage,short number);
		    /**
		    * \brief Asigna el build de la version
		    * \details Solo se acepta un entero largo positivo. por lo que no se aceptan metadatos en el sentido convencional, tampoco tiene signifacod alguno el compracion o validaciones por lo que es libre ade asignar el valor que desea
		    * */
			void setBuild(unsigned long);
		    //void setBuild(const Version&);
		    //void setBuild(const Version*);
		    void setBuild(const std::string&);
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
			*\brief Optine los componentes numericos correspondientes a la version,
			* sin que sea necesaio que toda la string tenga el formato correcto, solo
			* solo es necesario que los componentes numericos esten al pricipio de la caena.
			**/
			bool extractNumbers(const std::string& str);			
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
