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
#include "Message.hh"

namespace oct::core
{


        Warning::Warning(const std::string& brief): Message(brief)
        {}


        Confirmation::Confirmation(const std::string& brief): Message(brief)
        {

        }





        std::string Message::getBrief() const throw()
        {
                return brief;
        }
        Message::Message(const std::string& brief)
        {
                this->brief = brief;
        }


        void ActivityProgress::addActivities(int activities)
        {
                this->activities += activities;
        }
        void ActivityProgress::step(const Error& msg)
        {
                steps++;
                add(msg);
        }
        void ActivityProgress::step(const Confirmation& msg)
        {
                steps++;
                add(msg);
        }

        ActivityProgress::ActivityProgress(int activities)
        {
                steps = 0;
                this->activities = activities;
        }


}
