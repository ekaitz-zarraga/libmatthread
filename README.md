LIBMATTHREAD
===============================================================================

C Library for Matrix, Vector, and Discrete Signal operation.

The main idea is to make a C library for matrix, vector and signal operation based on multithreading. The aim is to learn stuff, not to make the ultimate library.

**CONTENT**

* libmatthread.so:
    * C library for custom programs.

* binaries:
    * Simple standalones for standard functionalities.

* tests:
    * Simple test programs.

**COMPILATION**

All the .o files are stored in "build" directory, interesting stuff is kept in root directory.

* Library and binaries:
    * $ make

* Test files:
    * $ make tests

**INSTALLATION**

There's no installation rule in the makefile. TODO ;)

**LIST OF AVAILABLE FUNCTIONALITIES**

* OctaveIO: Read/write matrixes, vectors and signals from/to .mat files.

**TODO LIST**

* [ ] Improve error handling.
* [ ] General function list:
    * [X] Compare.
    * [X] Automatic allocation.
    * [X] Automatic print.
    * [X] Automatic copy.
    * [X] Add rows/columns.
    * [X] Initialize matrix to "uninitialized state" (NULL pointer and Zeros).
    * [ ] Initialize N positions to X value.
* [ ] Signal related function list:
    * [ ] Convolution: Not multithreaded yet.
    * [ ] Correlation.
* [ ] Matrix related function list:
    * [ ] Multiply matrices.
* [ ] General purpose function list:
    * [X] Octave .mat files input/output.
