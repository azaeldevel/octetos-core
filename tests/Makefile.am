AUTOMAKE_OPTIONS=foreign 1.4

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(CUNIT_CFLAGS) \
	$(all_includes)

AM_CFLAGS =\
	 -Wall\
	 -g


bin_PROGRAMS =

if HAVE_VERSION
bin_PROGRAMS += v0
majorVersion = $(version $(PACKAGE_VERSION) --major)
v$(majorVersion)_LDADD = $(CUNIT_LIBS)  $(top_builddir)/src/liboctetos-core.la
v$(majorVersion)_CPPFLAGS = -I$(top_srcdir)/src
v$(majorVersion)_SOURCES = v$(majorVersion).cc
endif