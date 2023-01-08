
check_PROGRAMS = v2 v3 v2-v3
TESTS= $(check_PROGRAMS)

LIBS = $(OCTETOS_CORE_BASE_LIBS) 
FLAGS = $(OCTETOS_CORE_BASE_FLAGS) -I$(top_builddir) -I/usr/include/glibmm-2.4 -I/usr/lib/glibmm-2.4/include -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include



v2_LDFLAGS =
v2_LDADD = $(CUNIT_LIBS) $(LIBS) $(top_builddir)/src/liboctetos-core.la 
v2_CPPFLAGS = $(CUNIT_CFLAGS) $(FLAGS) -DOCTETOS_CORE_V2 -I$(top_srcdir)/src
v2_SOURCES = main.cc v2.cc
		 

v3_LDFLAGS =
v3_LDADD = $(CUNIT_LIBS) $(LIBS) $(top_builddir)/src/liboctetos-core.la 
v3_CPPFLAGS = $(CUNIT_CFLAGS) $(FLAGS) -DOCTETOS_CORE_V3 -I$(top_srcdir)/src
v3_SOURCES = main.cc v3.cc

v2_v3_LDFLAGS =
v2_v3_LDADD = $(CUNIT_LIBS) $(LIBS) $(top_builddir)/src/liboctetos-core.la 
v2_v3_CPPFLAGS = $(CUNIT_CFLAGS) $(FLAGS) -DOCTETOS_CORE_V2 -DOCTETOS_CORE_V3 -I$(top_srcdir)/src
v2_v3_SOURCES = main.cc v2.cc v3.cc