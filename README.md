clang-tools
===========

Tools for proper C++ usage with clang

Installation
------------

Check out the latest llvm and clang using the installation guide here

http://clang.llvm.org/get_started.html

Put the clang-tools repository inside llvm/tools/clang/examples and edit the CMakeLists.txt in llvm/tools/clang/ to include the clang-tools subdirectory, then rebuild llvm (using cmake, of course).

Usage
-----

There's a "run" script inside the repository that depends on a "run_configuration" file. Run the script without any arguments to get information on what to put in this configuration file.

To check a cpp file with the tools, run: ./run file.cpp
