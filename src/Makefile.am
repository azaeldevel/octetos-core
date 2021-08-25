
lib_LTLIBRARIES = liboctetos-core.la

semver.tab.c : semver.y 
	bison  -d -o $@ $<

liboctetos_core_la_CXXFLAGS = $(CUNIT_CFLGAS) $(LIBCONFIG_CFLGAS)  
liboctetos_core_la_LIBADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS)   
liboctetos_core_la_SOURCES = \
	common.c \
	Artifact.cc \
	Exception.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Licence.cc \
	Version.cc \
	version-semver.cc \
	semver.tab.c \
	semver-lexer.cc \
	Buffer.cc \
	memory.cc \
	core.cc


octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = semver-lexer.h common.h Version.hh Message.hh Error.hh \
	Object.hh Artifact.hh Licence.hh Buffer.hh defines.hh Exception.hh data.hh \
	memory.hh core.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core.pc

EXTRA_DIST = octetos-core.pc.in


uninstall-local:
	-rm -r $(jsdir)

noinst_PROGRAMS = develop testArrayCpp testArrayClass

develop_SOURCES = develop.cc 
develop_LDADD = liboctetos-core.la

testArrayCpp_SOURCES = testArrayC++.cc 
testArrayCpp_LDADD = liboctetos-core.la

testArrayClass_SOURCES = testArrayClass.cc 
testArrayClass_LDADD = liboctetos-core.la
