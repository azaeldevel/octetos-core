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


semver-100.tab.c semver-100.h : $(top_srcdir)/src/semver-100.y
	bison -d -o $@ $<
semver-100.c : $(top_srcdir)/src/semver-100.l
	flex -o $@ $<

semver-200.tab.c semver-200.h : $(top_srcdir)/src/semver-200.y
	bison -d -o $@ $<
semver-200.c : $(top_srcdir)/src/semver-100.l
	flex -o $@ $<

noinst_PROGRAMS =

noinst_PROGRAMS += v0
v0_LDADD = $(CUNIT_LIBS) -ldl
v0_CPPFLAGS = -I$(top_srcdir)/src 
v0_SOURCES = v0.cc  \
	$(top_srcdir)/src/version-semver-100.cc\
	$(top_srcdir)/src/version-semver-200.cc\
	$(top_srcdir)/src/version-semver.cc\
	$(top_srcdir)/src/Version.cc\
	$(top_srcdir)/src/common-c.c \
	$(top_srcdir)/src/common.cc \
	$(top_srcdir)/src/Error.cc \
	$(top_srcdir)/src/Message.cc \
	$(top_srcdir)/src/Object.cc \
	$(top_srcdir)/src/Licence.cc
