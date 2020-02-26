AUTOMAKE_OPTIONS=foreign 1.4


lib_LTLIBRARIES = liboctetos-semver-100.la liboctetos-semver-200.la liboctetos-core.la

bin_SCRIPTS =

semver-100.tab.c : semver-100.y
	bison -d -o $@ $<

semver-200.tab.c semver-200.h : semver-200.y
	bison -d -o $@ $<
semver-200.c : semver-200.l
	flex -o $@ $<

semver-parser-java.c semver-parser-java.h : semver-parser.h 
	javah -jni Tray.java
	
liboctetos_semver_100_la_CFLAGS = -fPIC $(AM_CFLAGS)
liboctetos_semver_100_la_CPPFLAGS = -fPIC $(AM_CPPFLAGS)
liboctetos_semver_100_la_CXXFLAGS = -fPIC $(AM_CPPFLAGS)
if WITH_SANDBOX
liboctetos_semver_100_la_CFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_semver_100_la_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_semver_100_la_CXXFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
liboctetos_semver_100_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_semver_100_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_semver_100_la_LDFLAGS += -export-dynamic
endif
liboctetos_semver_100_la_LIBADD = -ldl
liboctetos_semver_100_la_SOURCES = \
	semver-100.tab.c \
	semver-100.cc \
	common.c \
	Buffer.cc

liboctetos_semver_java_100_la_CFLAGS = -fPIC $(AM_CFLAGS) -I/usr/lib/jvm/java-8-openjdk-amd64/include -I/usr/lib/jvm/java-8-openjdk-amd64/include/linux
liboctetos_semver_java_100_la_CPPFLAGS = -fPIC $(AM_CPPFLAGS)
liboctetos_semver_java_100_la_CXXFLAGS = -fPIC $(AM_CPPFLAGS)
if WITH_SANDBOX
liboctetos_semver_java_100_la_CFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_semver_java_100_la_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_semver_java_100_la_CXXFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
liboctetos_semver_java_100_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_semver_java_100_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_semver_100_la_LDFLAGS += -export-dynamic 
endif
liboctetos_semver_java_100_la_LIBADD = -ldl 
liboctetos_semver_java_100_la_SOURCES = \
	semver-100.tab.c \
	semver-100.c \
	common.c \
	semver-parser-java.c

liboctetos_semver_200_la_CFLAGS = -fPIC $(AM_CFLAGS)
liboctetos_semver_200_la_CPPFLAGS = -fPIC $(AM_CPPFLAGS)
liboctetos_semver_200_la_CXXFLAGS = -fPIC $(AM_CPPFLAGS)
if WITH_SANDBOX
liboctetos_semver_200_la_CFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_semver_200_la_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_semver_200_la_CXXFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
liboctetos_semver_200_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_semver_200_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_semver_200_la_LDFLAGS += -export-dynamic
endif
liboctetos_semver_200_la_LIBADD = -ldl
liboctetos_semver_200_la_SOURCES = \
	semver-200.tab.c \
	semver-200.c \
	common.c

liboctetos_core_la_CFLAGS = -fPIC  $(AM_CFLAGS)
liboctetos_core_la_CPPFLAGS = -fPIC $(AM_CPPFLAGS)
liboctetos_core_la_CXXFLAGS = -fPIC $(AM_CPPFLAGS)
if WITH_SANDBOX
liboctetos_core_la_CFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_core_la_CPPFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
liboctetos_core_la_CXXFLAGS += -DDEBUG -DOCTETOS_CORE_SANDBOX -DCOLLETION_ASSISTANT
endif
liboctetos_core_la_LDFLAGS = -shared -fPIC
if PLATFORM_WIN32
liboctetos_core_la_LDFLAGS += -no-undefined
endif
if NATIVE_WIN32
liboctetos_core_la_LDFLAGS += -export-dynamic

liboctetos_core_la_LIBADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS)
endif
liboctetos_core_la_LIBDADD = -ldl
liboctetos_core_la_SOURCES = \
	common.c \
	Artifact.cc \
	Error.cc \
	Message.cc \
	Object.cc \
	Licence.cc \
	Version.cc \
	version-semver.cc \
	version-semver-100.cc \
	version-semver-200.cc

#bin_SCRIPTS += develop

#developdir = $(pythondir)/develop

#develop_PYTHON = common.py

#jsdir = $(pkgdatadir)

#js_DATA = develop.js

#CLASSPATH_ENV = 

## Add classpaths and other flags here
#AM_JAVACFLAGS =

## Directory where .class files will be created.
#JAVAROOT = $(top_builddir)/src

## Directory where .class files will be installed
#developdir = $(libdir)/develop

#develop_JAVA = Tray.java Semver.java Develop.java

octetos_core_includedir = $(includedir)/octetos/core
octetos_core_include_HEADERS = semver-parser.h common.h Version.hh Message.hh Error.hh Object.hh Artifact.hh Licence.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-core.pc

EXTRA_DIST = \
	octetos-core.pc.in
#	$(js_DATA)

uninstall-local:
	-rm -r $(jsdir)