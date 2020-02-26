#ifndef OCTETOS_CORE_LICENCE_HH
#define OCTETOS_CORE_LICENCE_HH
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

#include "Version.hh"


namespace octetos
{
namespace core
{
	class Licence : public Object
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
}

#endif
