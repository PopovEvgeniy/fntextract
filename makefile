install:
	@echo Installation in progress. Please wait
	@gcc fntextract.c -g0 -O0 -o fntextract
	@chmod ugo+rx fntextract
	@cp -f -p fntextract /bin/
	@echo Installation was successfuly complete
uninstall:
	@rm -f /bin/fntextract
	@echo Uninstallation was successfuly complete