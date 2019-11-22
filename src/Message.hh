#ifndef OCTETOS_CORE_MESSAGE_HH
#define OCTETOS_CORE_MESSAGE_HH

#include "Error.hh"


namespace octetos
{
namespace core
{
        /**
         * \brief Entendida como clase base para tranmitir mensajes.
         * */
        class Message
        {
        public:
                virtual std::string getBrief() const throw();
                Message(const std::string& brief);
                
        private:
                std::string brief;                
        };
        
        /**
         * \brief Mensajes de comfirmacion de operacion.
         * */
        class Confirmation: public Message
        {
        public:
                /**
                 * \brief Requerido por Message
                 * */
                Confirmation(const std::string& brief);
        };
        
        /**
         * \brief Mensaje de advertencias.
         * */
        class Warning: public Message
        {
        public:
                /**
                 * \brief Requerido por Message
                 * */
                Warning(const std::string& brief);
        };
        
        /**
         * \brief Interface dedicada a la centralizacion de mesnajes.
         * */
        class ActivityProgress
        {
        public:
                
                /**
                 * \brief Contructor del objeto
                 * \param activities Indica el total de actividades programadas
                 * */
                ActivityProgress(int activities);
                /**
                 * \brief Agrega actividades al registro actual
                 * \param activities La cantiad de actividad a agregar.
                 * */
                void addActivities(int activities);
                
                
                /**
                 * \brief Indica que en una actividad surgio un error y agrega una descripcion del mismo
                 * */
                void step(const Error&);
                /**
                 * \brief Indica que una actividad se realizo y agrega una descripcion
                 * */
                void step(const Confirmation&);
                /**
                 * \return retorna la cantidad de actividades programadas.
                 * */
                int getActivities();
                /**
                 * \return la cantidad de actividades realizadas.
                 * */
                int getSteps();
                /**
                 * \brief Agrega un mensage
                 * */
                virtual void add(const std::string&) = 0;
                /**
                 * \brief Agrega un mensage de error
                 * */
                virtual void add(const Error&) = 0;
                /**
                 * \brief Agrega un mensage de notificacion
                 * */
                virtual void add(const Confirmation&) = 0;
                /**
                 * \brief Agrega un mensage de notificacion
                 * */
                virtual void add(const Warning&) = 0;
        private:
                /**
                 * \brief indica el total de actividades programadas
                 * */
                int activities;
                /**
                 * \brief Indica la cantiad de actividades realizadas
                 * */
                int steps;
        };
}
}

#endif
