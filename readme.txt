                                 FNT EXTRACT

               Mugen font decompiler by Popov Evgeniy Alekseyevich

                               Version 2.3.9

The program description.

This program lets you decompile font files for games that are built on the MUGEN game engine.
This program takes a target file name as the command-line argument.

Exit codes.

0: The operation was successfully completed.
1: Can't open the input file.
2: Can't create the output file.
3: Can't jump to the target offset.
4: Can't allocate memory.
5: The invalid format.

License.

This program is distributed under the GNU GENERAL PUBLIC LICENSE.

The source code.

The code was compiled under Open Watcom.
But you can compile it with any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux.

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Version history.

1.0: The initial version.
1.1-2.1.4: The stable branch builds.
2.1.5-2.1.8: The small changes.
2.1.9: The source code has improved. Linux support has been added.
2.1.9.0.1: The documentation has been updated.
2.2-2.2.3: The small changes.
2.2.3.1: The makefile has been updated.
2.2.4-2.2.5: The small changes.
2.2.6-2.2.7: A small bug has been fixed.
2.2.8-2.2.9: The small changes.
2.2.9.1-2.2.9.2: The makefile has been updated.
2.2.9.3: The documentation has been updated.
2.3-2.3.2: The small changes.
2.3.3: Visual C++ support has improved.
2.3.3.1: The documentation has been updated.
2.3.4: The small changes.
2.3.4.1-2.3.4.2: The documentation has been updated.
2.3.5: The source code was recompiled under Tiny C Compiler.
2.3.6-2.3.7: The small changes.
2.3.7.1: The documentation has been updated.
2.3.8: The small changes.
2.3.8.1: The documentation has been updated.
2.3.9: The decompilation process has improved.