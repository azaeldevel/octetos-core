
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


parser.tab.c parser.tab.h : parser-version.y
	bison -d -o $@ $<

lexer.c : lexer-version.l
	flex -o $@ $<



lib_LTLIBRARIES =  \
	libparser-version-c.la \
	liboctetos-core-cc.la


libparser_version_c_la_CFLAGS=-fPIC -Wl,-Bsymbolic

libparser_version_c_la_LDFLAGS=-shared -fPIC -Wl,-Bsymbolic

libparser_version_c_la_SOURCES =  \
	parser.tab.c \
	lexer.c


liboctetos_core_cc_la_LIBADD = libparser-version-c.la

liboctetos_core_cc_la_CPPFLAGS= -DENABLED_AUTOT -fPIC -Wl,-Bsymbolic
 
liboctetos_core_cc_la_LDFLAGS= -shared -fPIC -Wl,-Bsymbolic

liboctetos_core_cc_la_SOURCES =  \
	common.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Version.cc \
	Version-parser.cc \
	Licence.cc


bin_PROGRAMS = \
	develop-parser-version


develop_parser_version_CFLAGS =

develop_parser_version_SOURCES = \
	develop-parser-version.cc

develop_parser_version_LDADD = libparser-version-c.la






if NATIVE_WIN32
	develop_parser_version_LDFLAGS += -mwindows
endif
