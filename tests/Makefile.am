
check_PROGRAMS = v2
TESTS= $(check_PROGRAMS)


v2_LDFLAGS =
v2_LDADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS) $(top_builddir)/src/liboctetos-core.la
v2_CPPFLAGS = $(CUNIT_CFLAGS) $(LIBCONFIG_CFLAGS) -I$(top_srcdir)/src -I$(top_builddir)/src -DSRCDIRTEST='"$(top_srcdir)/tests"'
v2_SOURCES = v2.cc  
		 