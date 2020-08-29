AUTOMAKE_OPTIONS=foreign 1.4


lib_LTLIBRARIES = liboctetos-core.la

semver.tab.c : semver.y 
	bison -d -o $@ $<

liboctetos_core_la_CFLAGS = -fPIC
liboctetos_core_la_CPPFLAGS = -fPIC
liboctetos_core_la_CXXFLAGS = -fPIC
liboctetos_core_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_core_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_core_la_LDFLAGS += -export-dynamic

liboctetos_core_la_LIBADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS)
endif
liboctetos_core_la_LIBDADD =
liboctetos_core_la_SOURCES = \
	common.c \
	Artifact.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Licence.cc \
	Version.cc \
	version-semver.cc \
	semver.tab.c \
	semver-lexer.cc \
	Buffer.cc

libshmem_la_SOURCES = dummy.c
libshmem_la_CFLAGS = -fPIC

octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = semver-lexer.h common.h Version.hh Message.hh Error.hh Object.hh Artifact.hh Licence.hh Buffer.hh
include_HEADERS = semver-lexer.h common.h Version.hh Message.hh Error.hh Object.hh Artifact.hh Licence.hh Buffer.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core.pc

EXTRA_DIST = octetos-core.pc.in


uninstall-local:
	-rm -r $(jsdir)
