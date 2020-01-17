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

noinst_PROGRAMS = verinfo

verinfo_LDFLAGS =
verinfo_LDADD = $(top_builddir)/src/liboctetos-core.la -ldl
verinfo_CFLAGS = -I$(top_srcdir)/src
verinfo_CPPFLAGS = -I$(top_srcdir)/src
verinfo_CXXFLAGS = -I$(top_srcdir)/src 
verinfo_SOURCES = verinfo.cc 