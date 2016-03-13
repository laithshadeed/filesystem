   CXX		= g++
CFILES		= main.cpp node.cpp directory.cpp file.cpp link.cpp
OFILES		= main.o node.o directory.o file.o link.o
CFLAGS		= -Wall -g -std=c++0x
.cpp.o:
	$(CXX) $(CFLAGS) -c $<
mount: $(OFILES)
	$(CXX) $(CFLAGS) -o $@ $(OFILES)
clean:
	/bin/rm -f *.o *.out core mount
