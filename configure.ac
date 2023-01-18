AC_INIT(octetos-core,2.60.1-beta, azael.devel@gmail.com)
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects])
AM_SILENT_RULES([yes])
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX(20)

dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
dnl IT_PROG_INTLTOOL([0.35.0])
dnl GETTEXT_PACKAGE=octetos-core
dnl AC_SUBST(GETTEXT_PACKAGE)
dnl AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
dnl AM_GLIB_GNU_GETTEXT
dnl AM_GNU_GETTEXT([external])
dnl AM_GNU_GETTEXT_VERSION([0.17])
dnl OCTETOS_CORE_LOCALEDIR=[${datadir}/locale]
dnl AC_SUBST(OCTETOS_CORE_LOCALEDIR)
dnl AC_DEFINE(OCTETOS_CORE_LOCALEDIR,"$OCTETOS_CORE_LOCALEDIR", [Gettex directory])

LT_INIT
dnl dreprecated>>>>>
PKG_CHECK_MODULES([OCTETOS_CORE_BASE], [libconfig++ openssl])

AM_CONDITIONAL(OCTETOS_CORE_ENABLE_TDD, false)
AM_CONDITIONAL(OCTETOS_CORE_ENABLE_DEV, false)
AM_CONDITIONAL(WITH_TESTS, test x"$with_tests" = "xyes")
AC_ARG_WITH([tests], AS_HELP_STRING([--with-tests], [Compilando con soporte para Testing]))
if test "x$with_tests" = "xyes"; then 
	AM_CONDITIONAL(OCTETOS_CORE_ENABLE_TDD, true)
	AM_CONDITIONAL(OCTETOS_CORE_ENABLE_DEV, true)
	PKG_CHECK_MODULES(CUNIT,cunit)
fi


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
tests/Makefile])
