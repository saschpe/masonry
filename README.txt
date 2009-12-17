Masonry
=======

A graphical tool to visualize and compute Mason-graphs written in C++ with Qt.

----


Prerequisites
-------------

The following software is necessary to build this application:

 - CMake_ 2.6 or later
 - Qt_ 4.6 or later

Additionally, one of the following software packages is needed to run the
application (only one required):

 - GNU Octave_ 3.2 or later
 - Matlab_ r2008a or later (commercial)


Installation
------------

How to build masonry depends on your platform. Generally you use CMake_ to
generate a platform-dependent build-environment. Generally this is done like
this (in a terminal)::

    $ mkdir build/
    $ cd build/
    $ cmake ..

If you want to specify an installation target and an optimised build, the
following commands could be used instead:

    $ mkdir build/ dist/
    $ cd build/
    $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../dist ..

You should now have either a Makefile on Unix-like operating systems or a
Visual Studio project on Windows. You can now build the project by using Visual
Studio (on Windows) or by issuing the following (on Unix)::

    $ make

The exact build procedure may differ slightly on your platform. Have a look at
the `CMake documentation`__ for help.


License
-------

Please see the file LICENSE.txt for details.


Notes
-----

This file is written in reStructuredText_ and can be converted to HTML with
Python docutils_. Use the following command::

    $ rst2html README.txt > README.html


.. _CMake: http://www.cmake.org/
.. _Qt: http://qt.nokia.com/
.. _Octave: http://www.gnu.org/software/octave/
.. _Matlab: http://www.mathworks.com/products/matlab/
.. _reStructuredText: http://en.wikipedia.org/wiki/Restructured_text
.. _docutils: http://docutils.sourceforge.net/

__ http://cmake.org/cmake/help/help.html
