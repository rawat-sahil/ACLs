setacl:setacl.cpp
	g++ -g -o $@ $<

ACL.o: ACL.cpp ACL.h
	g++ -c -g -o $@ $<

clean:
	rm *o 
