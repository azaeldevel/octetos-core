#ifndef OCTETOS_CORE_EXCEPTION_HH
#define OCTETOS_CORE_EXCEPTION_HH

/**
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
 * */


#include "Exception-v2.hh"
#include "Exception-v3.hh"

namespace oct
{
	namespace core
	{
		using v2::Exception;
		using v2::InternalException;
	}
}

namespace octetos
{
	namespace core
	{
		using oct::core::v2::Exception;
		using oct::core::v2::InternalException;
	}
}

#endif
