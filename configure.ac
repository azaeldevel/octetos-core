AC_INIT(octetos-core,2.19.0-beta, azael.devel@gmail.com)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign gnu subdir-objects])
AM_SILENT_RULES([yes])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_YACC
AM_PATH_PYTHON


dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
#IT_PROG_INTLTOOL([0.35.0])

#GETTEXT_PACKAGE=octetos-core
#AC_SUBST(GETTEXT_PACKAGE)
#AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
#AM_GLIB_GNU_GETTEXT



dnl ***************************************************************************
dnl Check for Windows
dnl ***************************************************************************
AC_CANONICAL_HOST

case $host_os in
  *mingw*)
    platform_win32=yes
    native_win32=yes
    ;;
  pw32* | *cygwin*)
    platform_win32=yes
    native_win32=no
    ;;
  *)
    platform_win32=no
    native_win32=no
    ;;
esac
AM_CONDITIONAL(PLATFORM_WIN32, test x"$platform_win32" = "xyes")
AM_CONDITIONAL(NATIVE_WIN32, test x"$native_win32" = "xyes")


LT_INIT([win32-dll])

PKG_CHECK_MODULES(LIBCONFIG,libconfig++)

PKG_CHECK_MODULES(CUNIT,cunit)

PKG_CHECK_MODULES(OPENSSL,openssl)

AM_CONDITIONAL(WITH_DOCS, test x"$with_docs" = "xyes")
AC_ARG_WITH([docs], AS_HELP_STRING([--with-docs], [Compilando con soporte para Documentación.]))
if test "x$with_docs" = "xyes"; then 
	AC_CHECK_PROG([DOXYGEN], [doxygen])
	if test -z "$DOXYGEN"; then
	   AC_MSG_ERROR([Es necesario instalar Doxygen para continuar])
	fi
	AC_CHECK_PROGS([DOT], [dot])
	if test -z "$DOT"; then
	   AC_MSG_ERROR([Doxygen necesita dot, porfavor instalelo primero])
	fi
	AC_CHECK_PROGS([PDFLATEX], [pdflatex])
	if test -z "$PDFLATEX"; then
	   AC_MSG_ERROR([Doxygen necesita pdflatex, es parte de TeX http://www.tug.org/texlive/acquire-netinstall.html])
	fi
fi
AM_CONDITIONAL([CHECK_DOXYGEN], [test -n "$DOXYGEN"])
AM_COND_IF([CHECK_DOXYGEN], [AC_CONFIG_FILES([docs/Doxyfile])])
AM_COND_IF([CHECK_DOXYGEN], [AC_CONFIG_FILES([docs/Makefile])])

AM_CONDITIONAL(WITH_EXAMPLES, test x"$with_examples" = "xyes")
AC_ARG_WITH([examples], AS_HELP_STRING([--with-examples], [Compilando con soporte para Ejemplos.]))





AC_OUTPUT([
Makefile
src/octetos-core.pc
src/Makefile
tests/Makefile
examples/Makefile])
