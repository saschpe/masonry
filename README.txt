Masonry
=======

tbd.


Prerequisites
-------------

The following software is necessary to build this application:

 - CMake_-2.6
 - Qt_-4.6


Installation
------------

How to build masonry depends on your platform. Generally you use CMake_ to
generate a platform-dependent build-environment. Generally this is done like
this (in a terminal):

 $ mkdir build/
 $ cd build/
 $ cmake ..

You should now have either a Makefile on Unix-like operating systems or a
Visual Studio project on Windows. You can now build the project by using Visual
Studio (on Windows) or by issuing the following (on Unix):

 $ make


Todo
----

 - Implement Ocatave integration


Notes
-----

This file is written in reStructuredText_ and can be converted to HTML with 
docutils_:

 $ rst2html README.txt > README.html


.. _CMake: http://www.cmake.org/
.. _Qt: http://qt.nokia.com/
.. _reStructuredText: http://en.wikipedia.org/wiki/Restructured_text
.. _docutils: http://docutils.sourceforge.net/
