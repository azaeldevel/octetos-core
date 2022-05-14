AM_YFLAGS = -d

lib_LTLIBRARIES = liboctetos-core.la


BUILT_SOURCES = semver.tab.h

liboctetos_core_la_CXXFLAGS = $(CUNIT_CFLGAS) $(LIBCONFIG_CFLGAS) $(OPENSSL_CFLGAS)  
liboctetos_core_la_LIBADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS) $(OPENSSL_LIBS)
liboctetos_core_la_SOURCES = \
	common.c \
	Artifact-v2.cc \
	Exception-v2.cc \
	Exception-v3.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Licence.cc \
	semver-lexer.cc \
	semver-lexer.2.cc \
	semver-lexer.3.cc \
	Version-parser-v2.cc \
	Version-parser-v3.cc \
	Version-v2.cc \
	Version-v3.cc \
	semver.tab.c \
	Buffer.cc \
	Memory.cc \
	core.cc \
	shell.cc cd.cc ls.cc exists.cc mkdir.cc rename.cc rm.cc touch.cc \
	MD5sum.cc \
	semver.y


octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = common.h Version.hh Version-v2.hh Version-v3.hh Message.hh Error.hh \
	Object.hh Artifact.hh Artifact-v2.hh Licence.hh Buffer.hh defines.hh Exception.hh Exception-v2.hh Exception-v3.hh data.hh \
	memory.hh Memory.hh core.hh shell.hh MD5sum.hh

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
