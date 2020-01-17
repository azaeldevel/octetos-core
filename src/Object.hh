#ifndef OCTETOS_CORE_OBJECT_HH
#define OCTETOS_CORE_OBJECT_HH

#ifdef DEBUG
        #define COLLETION_ASSISTANT
#endif


namespace octetos
{
namespace core
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
}

#endif
