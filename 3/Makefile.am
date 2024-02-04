
AM_CPPFLAGS = \
	-Wall\
	-pedantic\
	-std=c++20\
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"


lib_LTLIBRARIES = liboctetos-core.la

liboctetos_core_la_CXXFLAGS = $(OCTETOS_CORE_DEP_FLAGS) 
liboctetos_core_la_LIBADD = $(OCTETOS_CORE_DEP_LIBS)
liboctetos_core_la_SOURCES = \
	platform.cc \
	Configuration.cc \
	string.cc \
	version.cc \
	tree.cc \
	Buffer.cc


octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = Configuration.hh platform.hh Buffer.hh entity.hh tree.hh version.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core-3.pc

EXTRA_DIST = octetos-core-3.pc.in


uninstall-local:
	-rm -r $(jsdir)



version_SOURCES = version-main.cc 
version_LDADD = $(LIBS) liboctetos-core.la
version_CXXFLAGS = $(FLAGS) 



