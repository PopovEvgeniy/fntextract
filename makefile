install:
	@echo Compiling the program source code. Please wait
	@gcc fntextract.c -g0 -O0 -o fntextract
	@echo Compilation successfuly complete
	@chmod ugo+rx fntextract
	@echo Enter you user password for do last installation step
	@sudo cp -f -p fntextract /bin/
	@echo Installation complete
uninstall:
	@echo Enter you user password for uninstall this software
	@sudo rm -f /bin/fntextract
	@echo Uninstallation complete