
check_PROGRAMS = v2 v3 v2-v3
TESTS= $(check_PROGRAMS)

LIBS = $(OCTETOS_CORE_BASE_LIBS) $(CUNIT_LIBS) 
FLAGS = $(OCTETOS_CORE_BASE_FLAGS) $(CUNIT_CFLAGS)  -I$(top_builddir)

v2_LDFLAGS =
v2_LDADD = $(LIBS) $(top_builddir)/src/liboctetos-core.la 
v2_CPPFLAGS = $(FLAGS) -DOCTETOS_CORE_V2 -I$(top_srcdir)/src
v2_SOURCES = main.cc v2.cc

v3_LDFLAGS =
v3_LDADD = $(LIBS) $(top_builddir)/src/liboctetos-core.la 
v3_CPPFLAGS = $(FLAGS) -DOCTETOS_CORE_V3 -I$(top_srcdir)/src
v3_SOURCES = main.cc v3.cc

v2_v3_LDFLAGS =
v2_v3_LDADD = $(LIBS) $(top_builddir)/src/liboctetos-core.la 
v2_v3_CPPFLAGS = $(FLAGS) -DOCTETOS_CORE_V2 -DOCTETOS_CORE_V3 -I$(top_srcdir)/src
v2_v3_SOURCES = main.cc v2.cc v3.cc