AUTOMAKE_OPTIONS=foreign 1.4

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(all_includes)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = liboctetos-semver-100.la liboctetos-semver-200.la liboctetos-core.la


semver-100.tab.c semver-100.h : semver-100.y
	bison -d -o $@ $<
semver-100.c : semver-100.l
	flex -o $@ $<

semver-200.tab.c semver-200.h : semver-200.y
	bison -d -o $@ $<
semver-200.c : semver-200.l
	flex -o $@ $<

liboctetos_semver_100_la_CFLAGS = -fPIC
liboctetos_semver_100_la_CPPFLAGS = -fPIC
if WITH_SANDBOX
liboctetos_semver_100_la_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
liboctetos_semver_100_la_CXXFLAGS = -fPIC
liboctetos_semver_100_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_semver_100_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_semver_100_la_LDFLAGS += -export-dynamic
endif
liboctetos_semver_100_la_LIBADD = -ldl
liboctetos_semver_100_la_SOURCES = \
	semver-100.tab.c \
	semver-100.c \
	common.c

liboctetos_semver_200_la_CFLAGS = -fPIC
liboctetos_semver_100_la_CPPFLAGS = -fPIC
if WITH_SANDBOX
liboctetos_semver_100_la_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
liboctetos_semver_200_la_CXXFLAGS = -fPIC
liboctetos_semver_200_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_semver_200_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_semver_200_la_LDFLAGS += -export-dynamic
endif
liboctetos_semver_200_la_LIBADD = -ldl
liboctetos_semver_200_la_SOURCES = \
	semver-200.tab.c \
	semver-200.c \
	common.c

liboctetos_core_la_CFLAGS = -fPIC
liboctetos_core_la_CPPFLAGS = -fPIC
if WITH_SANDBOX
liboctetos_core_la_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
liboctetos_core_la_CXXFLAGS = -fPIC
if WITH_SANDBOX
liboctetos_core_la_CXXFLAGS += -DSANDBOX
endif
liboctetos_core_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_core_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_core_la_LDFLAGS += -export-dynamic
endif
liboctetos_core_la_LIBDADD = -ldl
liboctetos_core_la_SOURCES = \
	common.c \
	Artifact.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Licence.cc \
	Version.cc \
	version-semver.cc \
	version-semver-100.cc \
	version-semver-200.cc

#noinst_PROGRAMS = develop

#develop_LDADD = $(CUNIT_LIBS)  liboctetos-core.la -ldl
#develop_CPPFLAGS =
#develop_SOURCES = develop.cc

octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = semver-parser.h common.h Version.hh Message.hh Error.hh Object.hh Artifact.hh Licence.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core.pc

EXTRA_DIST = \
	octetos-core.pc.in
