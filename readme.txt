                                 FNT EXTRACT

               Mugen font decompiler by Popov Evgeniy Alekseyevich

                               Version 2.3.3

System requirement

64 kilobytes free space on storage media.

Description and usage

This program let you decompile a font files for games that built on MUGEN game engine.
This program takes a target file name as command line argument.

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create output file.
3 - Can't jump to target offset.
4 - Can't allocate memory.
5 - Invalid format.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Source code

The source code compiled under Open Watcom.
But you can compile it under any modern C compiler.
Source code can be compiled for wide range of operating systems, but you need to create makefile or build script by yourself.
I provide only two things: compiled the binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run as root for install: make install
Run as root for uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

1.0 — Initial version.
1.1 — 2.1.4 - Stable branch builds.
2.1.5 — 2.1.8 - Small changes.
2.1.9 - Source code improved. Linux support added.
2.1.9.0.1 – Documentation updated.
2.2 - 2.2.3 - Small changes.
2.2.3.1 - Makefile updated.
2.2.4 - 2.2.5 - Small changes.
2.2.6 - 2.2.7 - Small bug fixed.
2.2.8 - 2.2.9 - Small changes.
2.2.9.1 - 2.2.9.2 - Makefile updated.
2.2.9.3 - Documentation updated.
2.3 - 2.3.2 - Small changes.
2.3.3 - Visual C++ support improved.