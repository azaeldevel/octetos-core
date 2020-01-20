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

noinst_PROGRAMS = v0 v1

v0_LDFLAGS =
v0_LDADD = $(CUNIT_LIBS) $(top_builddir)/src/liboctetos-core.la -ldl
v0_CFLAGS = -I$(top_srcdir)/src 
v0_CPPFLAGS = -I$(top_srcdir)/src 
v0_SOURCES = v0.cc 

v1_LDFLAGS =
v1_LDADD = $(CUNIT_LIBS) $(top_builddir)/src/liboctetos-core.la -ldl
v1_CFLAGS = -I$(top_srcdir)/src 
v1_CPPFLAGS = -I$(top_srcdir)/src 
if WITH_SANDBOX
v1_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
v1_SOURCES = v1.cc 