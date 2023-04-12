
SUBDIRS = src

if WITH_DOCS
SUBDIRS +=  docs
endif
if WITH_EXAMPLES
SUBDIRS += examples
endif
if WITH_TESTS
SUBDIRS += tests
endif

# SUBDIRS += po
dist_doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS

INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)
