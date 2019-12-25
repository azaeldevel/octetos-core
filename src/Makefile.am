AUTOMAKE_OPTIONS=foreign 1.4

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(CUNIT_CFLAGS) \
	$(all_includes)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = liboctetos-core.la

bin_PROGRAMS = test-v0

parser.tab.c parser.tab.h : parser-version.y
	bison -d -o $@ $<

lexer.c : lexer-version.l
	flex -o $@ $<

liboctetos_core_la_LDFLAGS = 
liboctetos_core_la_LIBADD = $(CUNIT_LIBS)
liboctetos_core_la_SOURCES = \
	parser.tab.c \
	lexer.c \
	common-c.c \
	common.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Version.cc \
	Licence.cc
if PLATFORM_WIN32
liboctetos_core_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_core_la_LDFLAGS += -export-dynamic
endif


test_v0_LDADD = $(CUNIT_LIBS) liboctetos-core.la
test_v0_SOURCES = test-v0.cc



octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = common.h common.hh Version.hh Message.hh Error.hh Object.hh Artifact.hh Licence.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core.pc

EXTRA_DIST = \
	octetos-core.pc.in
