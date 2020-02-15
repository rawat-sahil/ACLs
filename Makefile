flags=-g
depends=setacl_dependency.h ACL.h
all: setacl getacl
	touch testfile
%.o: %.cpp $(depends)
	g++  $(flags) -c -o $@ $<

setacl: setacl.o setacl_dependency.o ACL.o
	g++ $(flags) -o $@ $^


getacl: getacl.o setacl_dependency.o ACL.o
	g++ $(flags) -o $@ $^


clean:
	-rm *o setacl getacl testfile
