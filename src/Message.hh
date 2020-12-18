#ifndef OCTETOS_CORE_MESSAGE_HH
#define OCTETOS_CORE_MESSAGE_HH
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


#include "Error.hh"
#include "Exception.hh"

#include "defines.hh"


namespace octetos
{
namespace core
{
        /**
         * \brief Entendida como clase base para tranmitir mensajes.
         * */
        class DECLSPCE_DLL Message
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
        class DECLSPCE_DLL Confirmation: public Message
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
        class DECLSPCE_DLL Warning: public Message
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
        class DECLSPCE_DLL ActivityProgress
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
                 * \brief Agrega un mensage de error
                 * */
                virtual void add(const Exception&) = 0;
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
