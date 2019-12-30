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


semver-100.tab.c semver-100.h : semver-100.y
	bison -d -o $@ $<

semver-100.c : semver-100.l
	flex -o $@ $<


liboctetos_core_la_LDFLAGS = 
if PLATFORM_WIN32
liboctetos_core_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_core_la_LDFLAGS += -export-dynamic
endif
liboctetos_core_la_LIBADD = 
liboctetos_core_la_SOURCES = \
	semver-100.tab.c \
	semver-100.c \
	version-semver-comparators-100.cc\
	version-semver-100.cc\
	Version.cc \
	common-c.c \
	common.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Licence.cc


octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = common.h common.hh Version.hh Message.hh Error.hh Object.hh Artifact.hh Licence.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core.pc

EXTRA_DIST = \
	octetos-core.pc.in
