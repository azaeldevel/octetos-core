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

noinst_PROGRAMS = v0

v0_LDFLAGS =
v0_LDADD = -ldl $(CUNIT_LIBS) $(top_builddir)/src/liboctetos-semver-100.la $(top_builddir)/src/liboctetos-semver-200.la $(top_builddir)/src/liboctetos-core.la
v0_CPPFLAGS = -I$(top_srcdir)/src 
v0_SOURCES = v0.cc 