
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

octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = common.h common.hh Version.hh Message.hh Error.hh Object.hh Artifact.hh Licence.hh


lib_LTLIBRARIES =  \
	liboctetos-parser-version-c.la \
	liboctetos-core-c.la \
	liboctetos-core-cc.la 


liboctetos_parser_version_c_la_CFLAGS=-fPIC -Wl,-Bsymbolic

liboctetos_parser_version_c_la_LDFLAGS=-shared -fPIC -Wl,-Bsymbolic

liboctetos_parser_version_c_la_SOURCES =  \
	parser.tab.c \
	lexer.c 




liboctetos_core_c_la_LIBADD = liboctetos-parser-version-c.la

liboctetos_core_c_la_CFLAGS= -DENABLED_AUTOTOOLS -fPIC -Wl,-Bsymbolic

liboctetos_core_c_la_LDFLAGS= -shared -fPIC -Wl,-Bsymbolic

liboctetos_core_c_la_SOURCES = common-c.c




liboctetos_core_cc_la_LIBADD = 

liboctetos_core_cc_la_CPPFLAGS= -DENABLED_AUTOTOOLS -fPIC -Wl,-Bsymbolic
 
liboctetos_core_cc_la_LDFLAGS= -shared -fPIC -Wl,-Bsymbolic

liboctetos_core_cc_la_SOURCES = parser.tab.c \
	lexer.c \
	common-c.c \
	common.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Version.cc \
	Licence.cc




bin_PROGRAMS = \
	develop-parser-version

bin_SCRIPTS = develop.py

develop_parser_version_CFLAGS =

develop_parser_version_SOURCES = \
	develop-parser-version.cc

develop_parser_version_LDADD = libparser-version-c.la


developdir = $(pythondir)/python_foobar

develop_PYTHON = \
	develop.py



if NATIVE_WIN32
	develop_parser_version_LDFLAGS += -mwindows
endif


