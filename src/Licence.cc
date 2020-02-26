#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>

#include "Licence.hh"

namespace octetos
{
namespace core
{
	bool Licence::gnu_compatible(Type t)
	{
		switch(t)
		{
            case GPL:
            case GPLv1:
            case GPLv2:
            case GPLv3:
            case LGPLv21:
            case LGPL:
            case LGPLv3:
			case AGPLv3:
			case GNU_PERMISSIVE:
			case Apachev2:
			case ArtisticLicensev2:
			case ClarifiedArtistic:
			case BerkeleyDB:
			case Boost:
			case ModifiedBSD:
			case CeCILLv2:
			case ClearBSD:
			case CryptixGeneralLicense:
			case eCosv2:
			case ECLv2:
			case Eiffelv2:
			case EUDataGrid:
			case Expat:
			case FreeBSD:
			case Freetype:
			case HPND:
			case iMatix:
			case imlib:
			case ijg:
			case informal:
			case intel:
			case ISC:
			case MPLv2:
			case NCSA:
			case NetscapeJavaScript:
			case NewOpenLDAPv27:
			case PerlLicense:
			case PublicDomain:
			case Python:
			case Ruby:
			case SGIFreeB:
			case StandardMLofNJ:
			case Unicode:
			case UPL:
			case Unlicense:
			case Vim:
			case W3C:
			case WebM:
			case WTFPLv2:
			case Wx:
			case Wxwind:
			case X11:
			case XFree86v11:
			case ZLib:
			case Zopev20:	
			case Zopev21:
				return true;
		}

		return false;
	}
	bool Licence::write(libconfig::Setting &root)
	{
		libconfig::Setting &lc = root.add("licence", libconfig::Setting::TypeGroup);
		switch(type)
		{
			case Type::GPLv1:
				lc.add("type", libconfig::Setting::TypeString) = "GPLv1";
				break;
			case Type::GPLv2:
				lc.add("type", libconfig::Setting::TypeString) = "GPLv2";
				break;
			case Type::GPLv3:
				lc.add("type", libconfig::Setting::TypeString) = "GPLv3";
				break;
			case Type::LGPL:
				lc.add("type", libconfig::Setting::TypeString) = "LGPL";
				break;
			default:
				return false;
		}
		lc.add("owner", libconfig::Setting::TypeString) = owner;
		lc.add("name_public", libconfig::Setting::TypeString) = name_public;
		lc.add("year", libconfig::Setting::TypeInt) = year;
		lc.add("contact", libconfig::Setting::TypeString) = contact;
		
		return true;
	}
	
	std::string Licence::getText()const
	{
		std::string brief;
		if(type >= Type::GPL or type <= Type::GNU_PERMISSIVE)
		{
			if(!name_public.empty()) brief += name_public + " ";		
			brief += "Copyright (C) ";
			if(year > 0) brief += std::to_string(year) + " ";
			if(!owner.empty()) brief += owner;
			brief += "\nThis program comes with ABSOLUTELY NO WARRANTY.";
		}		
		
		return brief;
	}
	
	
	
	
}
}
