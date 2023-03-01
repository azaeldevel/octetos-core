AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir). \
	$(OCTETOS_CORE_BASE_CFLAGS). "\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-DOCTETOS_CORE_LOCALEDIR=\"${OCTETOS_CORE_LOCALEDIR}\"

AM_YFLAGS = -d	

AM_CFLAGS =\
	 -Wall\
	 -g 

uninstall-local:
	-rm -r $(jsdir)

noinst_PROGRAMS = develop-lexer-flex-c90 develop-lexer-occ-c90 occ-c90

develop_lexer_occ_c90_SOURCES = develop-lexer-occ-c90.cc
develop_lexer_occ_c90_LDADD = 
develop_lexer_occ_c90_CXXFLAGS = $(OCTETOS_CC_CFLGAS) 

develop_lexer_flex_c90_SOURCES = lexer-c90.l
develop_lexer_flex_c90_LDADD = -lfl
develop_lexer_flex_c90_CXXFLAGS = $(OCTETOS_CC_CFLGAS)

occ_c90_SOURCES = main-occ-c90.cc
occ_c90_LDADD = 
occ_c90_CXXFLAGS = $(OCTETOS_CC_CFLGAS) 
