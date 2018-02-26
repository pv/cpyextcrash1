#!/usr/bin/env pypy3
from distutils.core import setup, Extension
setup(name="cpyextcrash1",
      ext_modules=[Extension("testmodule",
                             sources=["testmodule.c"],
                             depends=["testmodule.c"])])
