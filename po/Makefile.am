DOMAINS = @PACKAGE@

all:
	

install:
	for file in `ls *.po` ; do \
		fn=`echo $$file | cut -d '.' -f 1`; \
		msgfmt -c -v -o $$fn.mo $$file; \
		mkdir -p $(DESTDIR)@localedir@/$$fn/LC_MESSAGES ; \
		cp -rf $$fn.mo  $(DESTDIR)@localedir@/$$fn/LC_MESSAGES/@PACKAGE@.mo; \
	done

uninstall:
	for file in `ls *.po` ; do \
		fn=`echo $$file | cut -d '.' -f 1`; \
		rm -f $(DESTDIR)@localedir@/$$fn/LC_MESSAGES/@PACKAGE@.mo; \
	done
