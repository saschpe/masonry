=======
Masonry
=======

A graphical tool to visualize and compute signal-flow graphs (or Mason graphs)
written in C++ with Qt which uses either Matlab or Octave as the computational
backend. It serves as a fully interactive Mason-graph editor and allows you to
run additional custom Matlab/Octave scripts as well as loading/saving your
graph files and results.

----


Prerequisites
-------------

This project uses Git_ as the revision-control system. Git_ is optional if you
retrieved this project as a source tarball and is only useful if you plan to
further develop the project or to send patches. The following software is
necessary to build this application:

 - CMake_ 2.6 or later
 - Qt_ 4.6 or later

Additionally, one of the following software packages is needed to run the
application (only one required):

 - Matlab_ r2008a or later (preferred, commercial)
 - GNU Octave_ 3.2 or later (default, free)


Installation
------------

How to build masonry depends on your platform. Generally you use CMake_ to
generate a platform-dependent build-environment. Generally this is done like
this (in a terminal)::

    $ mkdir build/
    $ cd build/
    $ cmake -DCMAKE_INSTALL_PREFIX=../dist ..

If you want to specify an optimised build, the following commands could be used
instead::

    $ mkdir build/ dist/
    $ cd build/
    $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../dist ..

You should now have either a Makefile on Unix-like operating systems or a
Visual Studio project on Windows. You can now build and install the project by
using Visual Studio (on Windows) or by issuing the following (on Unix)::

    $ make
    $ make install

The exact build procedure may differ slightly on your platform. Have a look at
the `CMake documentation`__ for detailed help. The install step is mandatory
to correctly setup translations and other stuff. The folder _dist_ now contains
the ready-to-use application.


License
-------

Please see the file LICENSE.txt for details.


Authors
-------

Please see the file AUTHORS.txt for details.


Notes
-----

This file is written in reStructuredText_ and can be converted to HTML with
Python docutils_. Use the following command::

    $ rst2html README.txt > README.html


.. _Git: http://git.or.cz/index.html
.. _CMake: http://www.cmake.org/
.. _Qt: http://qt.nokia.com/
.. _Octave: http://www.gnu.org/software/octave/
.. _Matlab: http://www.mathworks.com/products/matlab/
.. _reStructuredText: http://en.wikipedia.org/wiki/Restructured_text
.. _docutils: http://docutils.sourceforge.net/

__ http://cmake.org/cmake/help/help.html
