#ifndef OCTETOS_CORE_LICENCE_HH
#define OCTETOS_CORE_LICENCE_HH

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




#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

#include "Version.hh"

namespace oct::core
{
	class OCTETOS_CORE_DECLSPCE_DLL Licence : public Object
	{
	public:
		enum Type
		{
            GPL,
            GPLv1,
            GPLv2,
            GPLv3,
            LGPLv21,
            LGPL,
            LGPLv3,
			AGPLv3,
			GNU_PERMISSIVE,
			Apachev2,
			ArtisticLicensev2,
			ClarifiedArtistic,
			BerkeleyDB,
			Boost,
			ModifiedBSD,
			CeCILLv2,
			ClearBSD,
			CryptixGeneralLicense,
			eCosv2,
			ECLv2,
			Eiffelv2,
			EUDataGrid,
			Expat,
			FreeBSD,
			Freetype,
			HPND,
			iMatix,
			imlib,
			ijg,
			informal,
			intel,
			ISC,
			MPLv2,
			NCSA,
			NetscapeJavaScript,
			NewOpenLDAPv27,
			PerlLicense,
			PublicDomain,
			Python,
			Ruby,
			SGIFreeB,
			StandardMLofNJ,
			Unicode,
			UPL,
			Unlicense,
			Vim,
			W3C,
			WebM,
			WTFPLv2,
			Wx,
			Wxwind,
			X11,
			XFree86v11,
			ZLib,
			Zopev20,
			Zopev21
		};

		static bool gnu_compatible(Type);

		Type type;
		short year;
		std::string owner;
		std::string name_public;
        std::string contact;

		std::string getText() const;
		bool write(libconfig::Setting &root);
	};


}

namespace octetos::core
{
	typedef oct::core::Licence Licence;
}

#endif
