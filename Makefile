PYTHON=pypy3

all:
	rm -rf build *.so
	$(PYTHON) setup.py build_ext -i -g
	$(PYTHON) cpyextcrash1.py

clean:
	rm -rf build *.so

.PHONY: all
