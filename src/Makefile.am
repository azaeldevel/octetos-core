AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(OCTETOS_CORE_BASE_CFLAGS). "\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-DOCTETOS_CORE_LOCALEDIR=\"${OCTETOS_CORE_LOCALEDIR}\"

AM_YFLAGS = -d	

AM_CFLAGS =\
	 -Wall\
	 -g 


LIBS = $(OCTETOS_CORE_BASE_LIBS) 
FLAGS = $(OCTETOS_CORE_BASE_FLAGS) -DCOMPILER_GCC -I$(top_builddir) -I/usr/include/glibmm-2.4 -I/usr/lib/glibmm-2.4/include -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include
if OCTETOS_CORE_ENABLE_DEV
FLAGS += -DOCTETOS_CORE_ENABLE_DEV
endif



liboctetos_core_la_CXXFLAGS = $(FLAGS) 
liboctetos_core_la_LIBADD = $(LIBS)
liboctetos_core_la_SOURCES = \
	Artifact-v2.cc \
	Exception-v2.cc \
	Exception-v3.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Licence.cc \
	semver-lexer.2.cc \
	semver-lexer.3.cc \
	Version-parser-v2.cc \
	Version-parser-v3.cc \
	Version-v2.cc \
	Version-v3.cc \
	Buffer.cc \
	Memory.cc \
	core.cc \
	shell.cc cd.cc ls.cc exists.cc mkdir.cc rename.cc rm.cc touch.cc \
	MD5sum.cc \
	common.c


octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = common.h Version.hh Version-v2.hh Version-v3.hh Message.hh Error.hh \
	Object.hh Artifact.hh Artifact-v2.hh Licence.hh Buffer.hh defines.hh Exception.hh Exception-v2.hh Exception-v3.hh data.hh \
	memory.hh Memory.hh core.hh shell.hh MD5sum.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core.pc

EXTRA_DIST = octetos-core.pc.in


uninstall-local:
	-rm -r $(jsdir)

noinst_PROGRAMS = develop develop-2 testArrayCpp testArrayClass develop-lexer-flex-c90 develop-lexer-occ-c90 occ-c90

develop_SOURCES = develop.cc 
develop_LDADD = $(LIBS) liboctetos-core.la
develop_CXXFLAGS = $(FLAGS) 

develop_2_SOURCES = develop-2.cc 
develop_2_LDADD = $(LIBS) liboctetos-core.la
develop_2_CXXFLAGS = $(FLAGS)

version_SOURCES = version-main.cc 
version_LDADD = $(LIBS) liboctetos-core.la
version_CXXFLAGS = $(FLAGS) 

testArrayCpp_SOURCES = testArrayC++.cc 
testArrayCpp_LDADD = liboctetos-core.la

testArrayClass_SOURCES = testArrayClass.cc 
testArrayClass_LDADD = liboctetos-core.la

develop_lexer_occ_c90_SOURCES = develop-lexer-occ-c90.cc
develop_lexer_occ_c90_LDADD = 
develop_lexer_occ_c90_CXXFLAGS = $(OCTETOS_CC_CFLGAS) 

develop_lexer_flex_c90_SOURCES = lexer-c90.l
develop_lexer_flex_c90_LDADD = -lfl
develop_lexer_flex_c90_CXXFLAGS = $(OCTETOS_CC_CFLGAS)

occ_c90_SOURCES = main-occ-c90.cc
occ_c90_LDADD = 
occ_c90_CXXFLAGS = $(OCTETOS_CC_CFLGAS) 

