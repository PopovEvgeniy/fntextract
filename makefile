install:
	@echo Installation in progress. Please wait
	@gcc fntextract.c -g0 -O0 -o /bin/fntextract
	@chmod ugo+rx /bin/fntextract
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/fntextract
	@echo Uninstallation was successfuly complete