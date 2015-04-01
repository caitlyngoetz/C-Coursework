

all: library testcode buildself


library:	
	cd libsrc; make install

testcode:
	cd testsuite; make
	
buildself:
	cd self-organizing-list; make

dox:
	echo "Generating documentation using doxygen..."
	doxygen doxygen-config >& doxygen.log
	echo "Use konqueror docs/html/index.html to see docs (or any other browser)"

clean:
	cd libsrc; make installclean
	cd testsuite; make clean
	cd self-organizing-list; make clean
	/bin/rm -fr docs doxygen.log

