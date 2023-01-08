AC_INIT(octetos-core,2.57.2-alpha, azael.devel@gmail.com)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign gnu subdir-objects])
AM_SILENT_RULES([yes])

AC_PROG_CC
AC_PROG_CXX


AX_CXX_COMPILE_STDCXX(20)

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
#IT_PROG_INTLTOOL([0.35.0])

#GETTEXT_PACKAGE=octetos-core
#AC_SUBST(GETTEXT_PACKAGE)
#AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
#AM_GLIB_GNU_GETTEXT

LT_INIT

PKG_CHECK_MODULES(LIBCONFIG,libconfig++)

AM_CONDITIONAL(WITH_TESTS, test x"$with_tests" = "xyes")
AC_ARG_WITH([tests], AS_HELP_STRING([--with-tests], [Compilando con soporte para Tests]))
if test "x$with_tests" = "xyes"; then 
	PKG_CHECK_MODULES(CUNIT,cunit)
fi

dnl dreprecated>>>>>
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
