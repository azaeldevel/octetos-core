AUTOMAKE_OPTIONS=foreign 1.4

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(CUNIT_CFLAGS) \
	$(all_includes)

AM_CFLAGS = \
	 -Wall \
	 -g

noinst_PROGRAMS = v2

v2_LDFLAGS =
v2_LDADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS) $(top_builddir)/src/liboctetos-core.la  $(LIBCONFIG_LIBS)
v2_CFLAGS = -I$(top_srcdir)/src 
v2_CPPFLAGS = -I$(top_srcdir)/src 
v2_CXXFLAGS = -I$(top_srcdir)/src 
v2_SOURCES = v2.cc 