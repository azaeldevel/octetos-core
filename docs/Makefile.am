

if HAVE_DOXYGEN
directory = $(top_srcdir)/docs/man/man3

man_MANS = $(directory)

$(directory): doxyfile.stamp

doxyfile.stamp: $(top_builddir)/docs/Doxyfile
	$(DOXYGEN) $^
#	cd $(top_builddir)/docs/latex && $(MAKE)
	echo Timestamp > $@

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	-rm -rf $(top_srcdir)/docs/man

endif 
