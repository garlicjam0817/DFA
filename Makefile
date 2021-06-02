

proj1: proj1.o FSA.o
	g++ -o proj1 $(CXXFLAGS) proj1.o FSA.o

proj1.o: proj1.cc

FSA.o: FSA.cc FSA.h

clean:
	@/bin/rm -f *~ \#*\# core* proj1 *.o
