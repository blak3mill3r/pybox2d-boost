#!/usr/bin/env python

"""\
PyBox2D - An (incomplete) Boost.Python wrapper around Box2D

Might be useful for 2D physics in games or such.
I have to admit, it's getting better,
a little better all the time.
"""

DOCLINES = __doc__.split("\n")

import __builtin__
import os
import sys
from distutils.core import setup, Extension

CLASSIFIERS = """\
Development Status :: 2 - Chuzwazzer
Programming Language :: C++
Programming Language :: Python
Operating System :: POSIX
Operating System :: Unix
"""

WRAPPER_FILES = """\
pybox2d/ext/box2d_wrap.cpp
pybox2d/ext/wrap_body.cpp
pybox2d/ext/wrap_collision.cpp
pybox2d/ext/wrap_joints.cpp
pybox2d/ext/wrap_math.cpp
pybox2d/ext/wrap_shapes.cpp
pybox2d/ext/wrap_world.cpp\
""".split("\n")

def setup_package():

    old_path = os.getcwd()
    local_path = os.path.dirname(os.path.abspath(sys.argv[0]))
    os.chdir(local_path)
    sys.path.insert(0,local_path)

    try:
        setup(
            name = 'pybox2d',
            maintainer = "Blake Miller",
            maintainer_email = "blak3mill3r@gmail.com",
            description = DOCLINES[0],
            long_description = "\n".join(DOCLINES[2:]),
            url = "http://nowhere",
            download_url = "http://nowhere",
            license = 'BSD',
            classifiers=filter(None, CLASSIFIERS.split('\n')),
            author = "Blake Miller",
            author_email = "blak3mill3r@gmail.com",
            platforms = ["Linux", "Unix"],
            ext_modules=[ Extension("pybox2d_ext", WRAPPER_FILES, \
            library_dirs=["/usr/local/boost_1_37_0/libs/python/build", "/usr/local/lib"], \
            include_dirs=["/usr/local/boost_1_37_0", "/home/blake/src/Box2D/Source"], \
            libraries=["boost_python", "box2d"]) ],
            packages = ['pybox2d']
            )
    finally:
        del sys.path[0]
        os.chdir(old_path)
    return

if __name__ == '__main__':
    setup_package()
