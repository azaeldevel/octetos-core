

AM_CPPFLAGS = \
	-Wall\
	-pedantic\
	-std=c++20\
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"


check_PROGRAMS = v3
TESTS= $(check_PROGRAMS)

v3_LDFLAGS =
v3_LDADD = $(OCTETOS_CORE_DEP_LIBS) $(CUNIT_LIBS)
v3_CXXFLAGS = $(OCTETOS_CORE_DEP_FLAGS) $(CUNIT_CFLAGS) -DOCTETOS_CORE_V3_TDD -DOCTETOS_CORE_VERSION_MAJOR=3 -DOCTETOS_CORE_VERSION_MINOR=0 -DOCTETOS_CORE_VERSION_PATCH=0
v3_SOURCES = main.cc v3.cc ../3/Configuration.cc ../3/version.cc ../3/platform.cc
