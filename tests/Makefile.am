AUTOMAKE_OPTIONS=foreign 1.4

if DEBUG
AM_CFLAGS = -g3 -O0
AM_CXXFLAGS = -g3 -O0
endif

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(CUNIT_CFLAGS) \
	$(all_includes)

AM_CFLAGS = \
	 -Wall \
	 -g


check_PROGRAMS = v2
TESTS= $(check_PROGRAMS)


v2_LDFLAGS =
v2_LDADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS) $(LIBCONFIG_LIBS)
v2_CFLAGS = -I$(top_srcdir)/src -I$(top_builddir)/src
v2_CPPFLAGS = -I$(top_srcdir)/src -I$(top_builddir)/src
v2_CXXFLAGS = -I$(top_srcdir)/src -I$(top_builddir)/src
v2_SOURCES = v2.cc $(top_srcdir)/src/  $(top_srcdir)/src/common.c \
		$(top_srcdir)/src/Artifact.cc $(top_srcdir)/src/Error.cc \
		$(top_srcdir)/src/Message.cc $(top_srcdir)/src/Object.cc \
		$(top_srcdir)/src/Licence.cc $(top_srcdir)/src/Version.cc $(top_srcdir)/src/version-semver.cc \
		$(top_srcdir)/src/semver.tab.c $(top_srcdir)/src/semver-lexer.cc $(top_srcdir)/src/Buffer.cc 
		 