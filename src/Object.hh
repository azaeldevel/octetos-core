#ifndef TOOLKIT_COMMON_OBJECT_HPP
#define TOOLKIT_COMMON_OBJECT_HPP

#ifndef DEBUG
        #define COLLETION_ASSISTANT
#endif


namespace octetos
{
namespace core
{
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
