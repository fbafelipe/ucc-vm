# ucc-vm

<p>ucc-vm is a very simple virtual machine for running programs (built for this VM). It interprets and run a very simple assembly.</p>
<p>This repository is part of a project I developed in 2009 when building a C compiler for my Compiler class at college. To run it you will need all three repositories: ucc, ucc-vm, and libparser.</p>

# Building ucc-vm

To build ucc-vm you will need CMake (http://www.cmake.org) building system
and libparser (https://github.com/fbafelipe/libparser) (ucc-vm and libparser
must be in the same folder).

ucc-vm binaries will be placed in folder build.

To build ucc-vm run these commands:

	$ cd build
	$ cmake ..
	$ make


# Using ucc-vm

To use ucc-vm you just need to add the include folder in your compiler's
includes search directories (usually -I flag), and link your executable with
ucc-vm binary.
