install:
	@echo Installation in progress. Please wait
	@$(CC) fntextract.c -g0 -O0 -o /bin/fntextract
	@chmod ugo+rx /bin/fntextract
	@echo Installation successfully complete
uninstall:
	@rm -f /bin/fntextract
	@echo Uninstallation successfully complete