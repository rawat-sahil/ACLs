flags=-g
depends=setacl_dependency.h getacl_dependency.h
all: setacl

%.o: %.cpp $(depends)
	g++  $(flags) -c -o $@ $<

setacl: setacl.o setacl_dependency.o ACL.o
	g++ $(flags) -o $@ $^


getacl: getacl.o getacl_dependency.o ACL.o
	g++ $(flags) -o $@ $^


clean:
	-rm *o setacl getacl
